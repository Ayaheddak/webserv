#include "../../includes/parsing.hpp"
#include "../../includes/Request.hpp"


void Request::pars_chunked_body() {
    size_t bodyStart = request.find("\r\n\r\n");
    if (bodyStart == std::string::npos) {
        return;
    }
    bodyStart += 4;

    std::string data = request.substr(bodyStart);
    while (!data.empty()) {
        std::string chunkSizeStr;
        size_t i = 0;
        for (; i < data.size(); ++i) {
            if (data[i] == '\r')
            {
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
            body.write(chunk_data.c_str(), chunk_data.size());
            body.flush(); 
        } else {
            break;
        }
    }
    read = true;
}


void Request::request_append(const char *str,int length)
{
        //std::cout << len <<"ss" << str << std::cout;
        if(k == -2 && length == 0)
        {
            read = true;
            return;
        }
        if(k > 0 && length > 0)
        {
            request.append(str,length);
        }
        if(k == 2 && status == true)
        {
            if(request.find("0\r\n\r\n") != std::string::npos)
            {
                pars_chunked_body();
                return;
            }
        }
        else if(request.find("\r\n\r\n") && k > 0)
        {
            k = 0;
            if(request.find("POST") != std::string::npos|| request.find("DELETE")!=std::string::npos)
            {
                status = true;
            }
            else
            {
                read = true;
            }
            fill_header();
        }
        else if(k < 0 && length > 0)
        {
            body.write(str, length);
            len = len + length;
            std::cout << len << std::endl;
        }
        if(len >= content_length && k < 0)
        {
           read = true;
        }
}
void Request::parse_header()
{
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
    if(status == true)
    {
        std::map<std::string, std::string> ::iterator it = header.find("Content-Length");
        if(it != header.end())
        {
            content_length = std::atoi(header["Content-Length"].c_str());
            k = -4;
        }
        else
        {
            std::map<std::string, std::string>::iterator it = header.find("Transfer-Encoding");
            if(it != header.end())
            {
                //std::cout << header["Transfer-Encoding"]<<" chunked^M"<< " chunked\r\n"<< std::endl;
                if(header["Transfer-Encoding"] == " chunked\r")
                {
                    k = 2;
                }
            }
            else
            {
                std::map<std::string, std::string>::iterator it = header.find("Connection");
                if(it != header.end())
                    if(header["Connection"]== " close")
                        k = -1;
            }
        }
        std::map<std::string, std::string> ::iterator ite = header.find("Content-Type");
        if(ite != header.end())
        {
            std::string type = ite->second.substr(ite->second.find("/") + 1,ite->second.find(";") -1);
            std::string name = "3ar.";
            name += type;
            body.open(name, std::ios::in | std::ios::out | std::ios::trunc |std::ios::binary); 
            if(!body.is_open())
            {
                std::cerr << "Error: Could not open file" << std::endl;
                exit(1);
            }
        }
    }
    if(status == true && k < 0)
    {   
        std::string body_content((std::istreambuf_iterator<char>(header_stream)), std::istreambuf_iterator<char>());
        body << body_content;
        len = body.tellp();

        if(len == content_length)
            read  = true;
    }
}

void Request::fill_header()
{
    std::string data = request.substr(0,request.find("\r\n"));

    std::stringstream s(data);
    // for(int i = 0;data[i];i++)
    // {
    //     if(data[i] == ' ')
    //         count++;
    // }
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
    parse_header();
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