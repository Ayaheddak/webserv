#include "../../includes/parsing.hpp"
#include "../../includes/Request.hpp"

void Request::fill_request(std::string str)
{
    std::string data = str.substr(0,str.find("\r\n"));
    std::cout << data<< std::endl;
    std::stringstream s(data);
    // for(int i = 0;data[i];i++)
    // {
    //     if(data[i] == ' ')
    //         count++;
    // }
    if(data[data.find("/")+1] != ' ' && data.find("/cover.css") == std::string::npos)
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
    if(str.find("Accept:") != std::string::npos)
    {
        type = str.substr(str.find("Accept:"),str.find(",",str.find("Accept:")) - str.find("Accept:"));
        type = type.erase(0,type.find(" ") + 1);
        std::cout <<type <<std::endl;
    }
    if(str.find("\r\n\r\n") + 1 != std::string::npos)
    {
        body = str.substr(str.find("\r\n\r\n") + 1,str.length());
    }
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
std::string Request::getBody() const
{
    return(body);
}
std::string Request::gettype()const
{
    return(type);
}
