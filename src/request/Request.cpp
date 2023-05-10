#include "../../includes/Request.hpp"
Request::Request()
{
	status = false;
	k = 1;
	read = false;
}
/*
		===================== getter & setter =====================
*/
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
