# ifndef REQUEST_HPP
#define REQUEST_HPP
#include "Utils.hpp"
class Request
{
    private :
        std::string                 _method;
        std::string                 _path;
        std::string                 _version;
        std::map<string, string>    _headers;
        std::string                 _body;
        void parse_request_line(const string& request_line);
        std::map<string, string> parse_headers(const string& headers);
        std::vector<string> parse_request(const string& request);
    public :
        Request(const string& request);
        std::string getMethod() const;
        std::string getPath() const;
        std::string getVersion() const;
        std::map<string, string> getHeaders() const;
        std::string getBody() const;
};
#endif