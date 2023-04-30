#include "../../includes/parsing.hpp"

size_t pars::s_return(std::string &src,size_t n,std::string &str)
{
    n = fill_data(src,"return",n,str);
    std::cout<< str << std::endl;
    return(n);
}
size_t pars::alias(std::string &src,size_t n,std::string &str)
{
    n = fill_data(src,"alias",n,str);
    std::cout<< str << std::endl;
    return(n);
}
size_t pars::autoindex(std::string &src,size_t n,std::string &str)
{
    n = fill_data(src,"autoindex",n,str);
    std::cout<< str << std::endl;
    return(n);
}
size_t fill_l_data(std::string str,std::string dest,size_t n , std::string &data)
{
    size_t i = n;
    n = n + dest.length();
    n = whitespaces(str,n);
    if(str[n] == '#' || str[n] == '\n')
    {
        std::cerr << "error" << std::endl;
        exit(1);
    }
    data = str.substr(n,str.find('}',n) + 1);
    if(str.find('}',i) == std::string::npos)
        exit(1);
    return(str.find('}',n) + 1);
}
size_t pars::which_one1(size_t n,std::string data,loc &location)
{
    if(data.find("root",n) == n)
    {
        return(root(data,n,location.root));
    }
     else if(data.find("index",n) == n)
    {
        return(index(data,n,location.index)); 
    }
    else if(data.find("allow_methods",n) == n)
    {
        return(allow_methods(data,n,location.allow_methods));   
    }
    else if(data.find("return",n) == n)
    {
        return(s_return(data,n,location.s_return));   
    }
    else if (data.find("alias",n) == n)
    {
        return(alias(data,n,location.alias));   
    }
    else if (data.find("autoindex",n) == n)
    {
        return(autoindex(data,n,location.autoindex));   
    }
    //std::cout<< f_data.substr(n) << std::endl;
    return(1000000);
}
size_t pars::location(size_t n,data &server)
{
    std::string location;
    loc s_location;
    size_t i;
    i = 0;
    n = fill_l_data(f_data,"location",n,location);
    if(location.find('{') == std::string::npos || location.find('/') == std::string::npos)
        exit(1);
    //std::cout << location[0] << std::endl;
    if(location[i] != '/')
        exit(1);
    while(location[i] != ' ' && location[i] != '\t')
        i++;
    s_location.path = location.substr(location.find('/'),i);
    if(location[i] != ' ' && location[i] != '\t')
        exit(1);
    i = whitespaces(location,i);
    if(location[i] != '{')
        exit(1);
    i++;
    while(location[i] != '}' && location[i])
    {
        if(location[i] == '#')
        {
            while(location[i] && location[i] != '\n')
                i++;
        }
        if(location[i] != ' ' && location[i] != '\0'
            && location[i] != '\n' && location[i] != '{' && location[i] != '\t')
        {
            i = which_one1(i,location,s_location);
            //std::cout << i << std::endl;
        }
        i++;
    }
    server.location.push_back(s_location);
    return(n);
}