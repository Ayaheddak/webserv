#include "../../includes/Request.hpp"
Request::Request(const string& request)
{
    std::vector<string> request_parts = parse_request(request);
    parse_request_line(request_parts[0]);
    _headers = parse_headers(request_parts[0]);
    _body = request_parts[1];
}
std::string  Request::getMethod() const
{
    return _method;
}
std::string Request::getPath() const
{
    return _path;
}
std::string Request::getVersion() const
{
    return _version;
}
std::map<string, string> Request::headers() const
{
        return _headers;
}
std::string Request::body() const
{
    return _body;
}
void Request::parse_request_line(const string& request_line)
{
    istringstream iss(request_line);
    iss >> method_ >> path_ >> version_;
}
std::map<string, string> Request::parse_headers(const string& headers) 
{
    std::map<string, string> headers_map;
    std::istringstream iss(headers);
    std::string line;
    while (getline(iss, line) && line != "\r")
    {
        size_t colon_pos = line.find(":");
        if (colon_pos != string::npos)
        {
            string key = line.substr(0, colon_pos);
            string value = line.substr(colon_pos + 2, line.length() - colon_pos - 3);
            headers_map[key] = value;
        }
    }
    return headers_map;
}

std::vector<string> Request::parse_request(const string& request)
{
    std::vector<string> request_parts;
    size_t pos = request.find("\r\n\r\n");
    if (pos != string::npos)
    {
        request_parts.push_back(request.substr(0, pos));
        request_parts.push_back(request.substr(pos + 4));
    } else 
    {
        request_parts.push_back(request);
        request_parts.push_back("");
    }
    return request_parts;
}
