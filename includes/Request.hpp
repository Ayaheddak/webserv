# ifndef REQUEST_HPP
#define REQUEST_HPP
#include "Utils.hpp"
class Request
{
    private :
        std::string                 method;
        std::string                 path;
        std::string                 version;
        std::string                 body;
        std::string                 type;
    public :
        Request(){}
        void fill_request(std::string str);
        std::string getMethod() const;
        std::string getPath() const;
        std::string getVersion() const;
        std::string getBody() const;
        std::string gettype() const;
};
#endif