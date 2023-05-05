# ifndef REQUEST_HPP
#define REQUEST_HPP
#include "Utils.hpp"
#include <cstdlib>
class Request
{
    private :
        int                                 k;
        std::string                         request;
        std::string                         method;
        std::string                         path;
        std::string                         version;
        std::fstream                         body;
        std::map<std::string, std::string>  header;
        bool                                read;
        bool                                status;
        size_t                              content_length;
        size_t                              len;
    public :
        Request(){ status = false; k = 1; read = false;}
        void  clear();
        void request_append(const char *str,int length);
        void parse_header();
        void fill_header();
        std::map<std::string, std::string> getheader() const;
        std::string getMethod() const;
        std::string getPath() const;
        std::string getVersion() const;
        std::fstream &getBody();
        bool getread();
        int  getk();
};
#endif