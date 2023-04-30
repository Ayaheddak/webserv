#include "../../includes/parsing.hpp"

size_t whitespaces(std::string str,size_t n)
{
    while(str[n] == ' ' || str[n] == '\t')
        n++;
    return(n);
}
size_t fill_data(std::string str,std::string dest,size_t n , std::string &data)
{
    size_t i = n;
    n = n + dest.length();
    n = whitespaces(str,n);
    if(str.find(';') == std::string::npos||str[n] == '#' || str[n] == '\n' || str.find(';',n) > str.find('\n',n))
    {
        std::cerr << "error" << std::endl;
        exit(1);
    }
    data = str.substr(n,str.find(';',n) - n);
    return(str.find('\n',i) + 1);
}

size_t pars::server_name(std::string &src,size_t n,std::string &str)
{
    n = fill_data(src,"server_name",n,str);
    std::cout<< str << std::endl;
    return(n);
}
size_t pars::listen(std::string &src,size_t n,std::string &str)
{
    n = fill_data(src,"listen",n,str);
    std::cout<< str << std::endl;
    return(n);
}
size_t pars::root(std::string &src,size_t n,std::string &str)
{
    n = fill_data(src,"root",n,str);
    std::cout<< str << std::endl;
    return(n);
}
size_t pars::index(std::string &src,size_t n,std::string &str)
{
    n = fill_data(src,"index",n,str);
    std::cout<< str << std::endl;
    return(n);
}
size_t pars::body_size(std::string &src,size_t n,std::string &str)
{
    n = fill_data(src,"bodysize",n,str);
    std::cout<< str << std::endl;
    return(n);
}
size_t pars::error_page(std::string &src,size_t n,data &server)
{
    std::string str;
    n = fill_data(src,"error_page",n,str);
    server.error_page.push_back(str);
    std::cout<< str << std::endl;
    return(n);
}

size_t pars::allow_methods(std::string &src,size_t n,std::string &str)
{
    n = fill_data(src,"allow_methods",n,str);
    std::cout<< str << std::endl;
    return(n);
}
size_t pars::which_one(size_t n,data &server)
{
    if(f_data.find("server_name",n) == n)
    {
        if(server.server_name.length() > 0)
        {
            std::cerr << "error already filled" << std::endl;
            exit(1);
        } 
        return(server_name(f_data,n,server.server_name));
    }
    else if(f_data.find("listen",n) == n)
    {
        if(server.listen.length() > 0)
        {
            std::cerr << "error already filled" << std::endl;
            exit(1);
        } 
        return(listen(f_data,n,server.listen));
    }
     else if(f_data.find("root",n) == n)
    {
        if(server.root.length() > 0)
        {
            std::cerr << "error already filled" << std::endl;
            exit(1);
        } 
        return(root(f_data,n,server.root));
    }
     else if(f_data.find("index",n) == n)
    {
        if(server.index.length() > 0)
        {
            std::cerr << "error already filled" << std::endl;
            exit(1);
        } 
        return(index(f_data,n,server.index));   
    }
    else if(f_data.find("allow_methods",n) == n)
    {
        if(server.allow_methods.length() > 0)
        {
            std::cerr << "error already filled" << std::endl;
            exit(1);
        }
        return(allow_methods(f_data,n,server.allow_methods));   
    }
    else if(f_data.find("location",n) == n)
    {
        return(location(n,server));
    }
    else if(f_data.find("bodysize",n) == n)
    {
        if(server.body_size.length() > 0)
        {
            std::cerr << "error already filled" << std::endl;
            exit(1);
        } 
        return(body_size(f_data,n,server.body_size));
    }
    else if(f_data.find("error_page",n) == n)
    {
        return(error_page(f_data,n,server));
    }
    //std::cout<< f_data.substr(n) << std::endl;
    return(1000000);
}