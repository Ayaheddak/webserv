#include "../../includes/parsing.hpp"
#include "../../includes/Request.hpp"

void Request::request_append(const char *str,int length)
{
        if(k == -2 && length == 0)
        {
            read = true;
            return;
        }
        if(k > 0 && length > 0)
        {
            request.append(str,length);
        }
        else if(request.find("\r\n\r\n") && k > 0)
        {
            k = 0;
            if(request.find("POST") || request.find("DELETE"))
            {
                body.open("body", std::ios::binary | std::ios::in | std::ios::out);
                status = true;
            }
            fill_header();
        }
        else if(k > 0 && length > 0)
            body.write(str,length);
        len = len + length;
        if(len == content_length)
            read = true;
}
void        Request::parse_header()
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
        std::map<std::string, std::string> ::iterator it = header.find("Content-Length:");
        if(it != header.end())
            content_length = std::atoi(header["Content-Length:"].c_str());
        else
        {
            std::map<std::string, std::string>::iterator it = header.find("Transfer-Encoding:");
            if(it != header.end())
            {
                if(header["Transfer-Encoding:"] == " chunked")
                    k = -2;
            }
            else
            {
                std::map<std::string, std::string>::iterator it = header.find("Connection:");
                if(it != header.end())
                    if(header["Connection:"]== " close")
                        k = -1;
            }
        }
    }
    if(status == true)
    {
        while(std::getline(header_stream, line))
        {
            len = line.size() + len;
            body.write(line.c_str(),line.size());
        }
    }
}
void Request::fill_header()
{
    std::string data = request.substr(0,request.find("\r\n"));
    std::cout << data<< std::endl;
    std::stringstream s(data);
    // for(int i = 0;data[i];i++)
    // {
    //     if(data[i] == ' ')
    //         count++;
    // }
    if(data[data.find("/")+1] != ' ' )
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
