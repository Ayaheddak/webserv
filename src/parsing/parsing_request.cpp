#include "../../includes/parsing.hpp"
#include "../../includes/Request.hpp"
#include"../../includes/cgi.hpp"

void Request::open_and_check(std::string appendedData)
{

    if(!_host.getClientMaxBodySize().empty())
    {
      size_t nb;
      std::istringstream iss(_host.getClientMaxBodySize());
      iss >> nb;
          if( nb < appendedData.size())
          {
              status_value = 413;
              read = true;
              return;
          }
    }
    cgi_body = appendedData;
    if(status_value == 201)
    {  
        std::map<std::string, std::string>::iterator ite = header.find("Content-Type");
        if(ite != header.end())
        {
            size_t start = ite->second.find("/") + 1;
            size_t end = ite->second.find_first_of("\r\n");
            std::string type = ite->second.substr(start, end - start);
            std::string name = fullpath+ "3ar.";
            name += type;
            body.open(name.c_str(), std::ios::in | std::ios::out | std::ios::trunc |std::ios::binary); 
            if(!body.is_open())
            {
				std::cout << "Error open file" << std::endl;
                status_value = 404;
				return;
            }
            body.write(appendedData.c_str(), appendedData.size());
        }
        else
            status_value = 400;
    }
}
void Request::pars_chunked_body(size_t size) {
    if(size == 0)
        size = 0;
    size_t bodyStart = request.find("\r\n\r\n");
    bodyStart += 4;
    std::string data = request.substr(bodyStart);
   
    std::string appendedData;
    while (!data.empty()) {
        std::string chunkSizeStr;
        size_t i = 0;
        for (; i < data.size(); ++i) {
            if (data[i] == '\r') {
                break;
            }
            chunkSizeStr += data[i];
        }

        unsigned int len;
        std::stringstream ss;
        ss << std::hex << chunkSizeStr;
        ss >> len;

        if (len == 0) {
            break;
        }
        data = data.substr(chunkSizeStr.size() + 2);
        if (data.size() >= len) {
            std::string chunk_data = data.substr(0, len);
            data = data.substr(len + 2);
            appendedData.append(chunk_data);
        } else {
            break;
        }
    }
    open_and_check(appendedData);
    read = true;
}



void Request::request_append(const char *str,int length,size_t size,std::vector<Config>& parsing, std::pair<std::string, std::string> infoconfig)
{
        if(k > 0 && length > 0)
        {
            request.append(str,length);
        }
        if(k == 2)
        {
            if(request.find("0\r\n\r\n") != std::string::npos)
            {
                pars_chunked_body(size);
                return;
            }
        }
        else if(request.find("\r\n\r\n") && k > 0)
        {
            k = 0;
            fill_header(size);
            if(status_value == 400 || status_value == 501)
            {
                read = true;
                return;
            }
			matching(parsing, infoconfig);
            if(status_value == 0)
                check_request(parsing);
            if(k == 2 && request.find("0\r\n\r\n") != std::string::npos)
            {
                pars_chunked_body(size);
                return;
            }
        }
        else if(k < 0 && length > 0)
        {
            len = len + length;
            a_body.append(str,length);
        }
        if(k == -4 && len >= content_length)
        {
           open_and_check(a_body);
           read = true;
        }
        else if(request.find("0\r\n\r\n") != std::string::npos)
        {
                pars_chunked_body(size);
                return;
        }
}
void Request::parse_header(size_t size)
{
    if(size == 0)
        size = 0;
    std::istringstream header_stream(request);
    std::string line;
    std::getline(header_stream, line);
    while (std::getline(header_stream, line)) {
        if (line == "\r" || line.empty()) {
            break;
        }
        std::size_t colon_pos = line.find(':');
        if (colon_pos != std::string::npos) {
            std::string key = line.substr(0, colon_pos);
            std::string value = line.substr(colon_pos + 1);
            header[key] = value;
        }
    }
    std::map<std::string, std::string>::iterator it = header.find("Transfer-Encoding");
        if(it != header.end())
        {
            if(header["Transfer-Encoding"] == " chunked\r")
                k = 2;
            else
            {
                status_value = 501;
                read = true;
                return ;
            }
        }
    else
    {
        std::map<std::string, std::string> ::iterator it = header.find("Content-Length");
        if(it != header.end())
        {
            content_length = std::atoi(header["Content-Length"].c_str());
            k = -4;
        }
        else
        {
            if(getMethod() == "POST")
                status_value = 400;
            read = true;
            return;
        }
    }
    if(k == -4)
    {
        std::string body_content((std::istreambuf_iterator<char>(header_stream)), std::istreambuf_iterator<char>());   
        a_body = body_content;
        len = a_body.size();
        if(len == content_length)
            read  = true;
    }
}

void Request::fill_header(size_t size)
{
    std::string data = request.substr(0,request.find("\r\n"));
    std::stringstream s(data);
    if(data[data.find("/")+1] != ' ')
    {
        s >> method;
        s >> path;
        s >> version;
    }
    else
    {
        s >> method;
        s >> version;
    }
    if (path.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~:/?#[]@!$&'()*+,;=") != std::string::npos)
    {
        status_value = 400;
        read = true;
        return ;
    }
    if(path.size() > 2048)
    {
        status_value = 414;
        read = true;
        return ;
    }
    parse_header(size);
}
std::string Request::getMethod() const
{
    return(method);
}
std::string Request::getPath() const
{
    return(path);
}
std::string Request::getVersion() const
{
    return(version);
}
std::fstream &Request::getBody()
{
    return(body);
}
std::map<std::string, std::string> Request::getheader() const
{
    return(header);
}
bool Request::getread() 
{
    return read;
}
std::string Request::getCgibody()
{
    return cgi_body;
}
int  Request::getk() 
{
    return k;
}
void Request::clear()
{
    status = false; k = 1; read = false;
    request = "";
    path = "";
    version = "";
}
Config Request::getServer(std::vector<Config> conf, std::pair<std::string, std::string> infoconfig)const
{
	std::vector<Config>::iterator it;
	for (it = conf.begin(); it != conf.end(); it++)
	{
		if (it->getHost() == infoconfig.first && it->getListen() == infoconfig.second)
		{
			std::cout << "server found" << std::endl;
			return *it;
		}
	}
	return *it;
}

void Request::matching(std::vector<Config> conf, std::pair<std::string, std::string> infoconfig)
{
	std::string search = header["Host"];
	std::vector<Config>::iterator s = findMatchingConfig(conf, search, infoconfig);
	if (s == conf.end())
		s = findMatchingConfigWithoutName(conf, infoconfig);
	if (s != conf.end())
		_host = *s;
	else
	{
		std::cout << "no matching server" << std::endl;
		_host = getServer(conf,infoconfig);
	}
   
}
std::string removeCarriageReturn(const std::string& str) {
    std::string result;
    
    for (std::string::size_type i = 0; i < str.length(); ++i) {
        if (str[i] != '\r') {
            result += str[i];
        }
    }
    
    return result;
}
std::vector<Config>::iterator Request::findMatchingConfig(std::vector<Config>& conf, const std::string& search, const std::pair<std::string, std::string>& infoconfig)
{
	std::vector<Config>::iterator s;
	std::string value;
	for (s = conf.begin(); s != conf.end(); s++)
	{
		value = removeCarriageReturn(search);
		value = removeLeadingWhitespace(value);
		std::cout << "value:" << value << std::endl;
		if (s->getServerName() == value && s->getListen() == infoconfig.second && s->getHost() == infoconfig.first)
		{
			std::cout << "server found" << std::endl;
			break;
		}
	}
	return s;
}

std::vector<Config>::iterator Request::findMatchingConfigWithoutName(std::vector<Config>& conf, const std::pair<std::string, std::string>& infoconfig)
{
	std::vector<Config>::iterator s;
	for (s = conf.begin(); s != conf.end(); s++)
	{
		if (s->getListen() == infoconfig.second && s->getHost() == infoconfig.first)
		{
			break;
		}
	}
	return s;
}
