#include "../../includes/parsing.hpp"

void pars::fill_request(std::string str)
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
        s >> r_data.method;
        s >> r_data.url;
    }
    else
        s >> r_data.method;
    std::stringstream a(s_data[0].allow_methods);
    std::string word;
    count = 0;
    while (a >> word) {
       if(word == r_data.method)
            count = 1;
    }
}