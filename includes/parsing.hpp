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
    int sockfd;
    std::fstream html_file;
    std::string f_data;
    long glen;
    long length;
    std::ifstream inputfile;
    char response_buf2[65536];
    char *response_buf1;
    long len;

    std::vector<data> s_data;
    Request r_data;
    int c;
    int count;
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
    void split_methods(std::string str,data &server);
    void fill_request(std::string str);
    void respons(int client_sock);
    void respons_200(std::string index);
    void res_location(std::vector<loc>::iterator it);
    void check_location(void);
    void respons_404(void);
    void respons_201(std::string index);
    void respons_204(void);
    void respons_301(void);
    void respons_400(void);
    void respons_403(void);
    void respons_405(void);
    void respons_413(void);
    void respons_500(void);
    void respons_504(void);
};  
size_t whitespaces(std::string str,size_t n);
size_t fill_data(std::string str,std::string dest,size_t n , std::string &data);
#endif