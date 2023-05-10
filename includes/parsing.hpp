#ifndef PARSING_HPP
#define PARSING_HPP

#include "Request.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>          
#include <cstring>
#include <algorithm>
#include <signal.h>

#include <cstdlib>
#include <netinet/in.h>

class loc
{
    public:
    std::string path;//yes
    std::string autoindex;//yes
    std::string s_return;
    std::string alias;
    std::string allow_methods;//yes
    std::string root;//yes
    std::string index;//yes
};

class data
{
    public:
    std::string server_name;
    std::string listen;
    std::vector<std::string> error_page;
    std::string body_size;
    std::string root;
    std::string index;
    std::string allow_methods;
    std::vector<std::string> methods;
    std::vector<loc> location;
};

class pars
{
    public:
    std::string f_data;
    std::ifstream inputfile;
    std::vector<data> s_data;
    
    pars(const pars& other)
        : f_data(other.f_data),
          s_data(other.s_data)
    {
    }
    pars& operator=(const pars& other)
    {
        if (this == &other)
            return *this;

        f_data = other.f_data;
        s_data = other.s_data;

        return *this;
    }
    pars(){}
    pars(char *str);
    void check_data();
    size_t location(size_t n,data &server);
    size_t which_one(size_t n,data &server);
    void reading_file();
    size_t server_name(std::string &src,size_t n,std::string &str);
    size_t listen(std::string &src,size_t n,std::string &str);
    size_t root(std::string &src,size_t n,std::string &str);
    size_t index(std::string &src,size_t n,std::string &str);
    size_t body_size(std::string &src,size_t n,std::string &str);
    size_t error_page(std::string &src,size_t n,data &server);
    size_t allow_methods(std::string &src,size_t n,std::string &str);
    size_t check_between(size_t start,size_t end);
    size_t check_server_data(size_t n);
    size_t which_one1(size_t n,std::string data,loc &location);
    size_t s_return(std::string &src,size_t n,std::string &str);
    size_t alias(std::string &src,size_t n,std::string &str);
    size_t autoindex(std::string &src,size_t n,std::string &str);
    void check_syntax(size_t i);
};  
size_t whitespaces(std::string str,size_t n);
size_t fill_data(std::string str,std::string dest,size_t n , std::string &data);
#endif