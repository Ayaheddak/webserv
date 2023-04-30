#include "../../includes/Server.hpp"
int main() 
{
    std::list<std::pair<std::string, std::string> > _port;
    _port.push_back(std::make_pair("8086", "127.0.0.1"));
    _port.push_back(std::make_pair("8082", "127.0.0.1"));
    _port.push_back(std::make_pair("8083", "127.0.0.1"));
    _port.push_back(std::make_pair("8084", "127.0.0.1"));
    Server server(_port);
    server.start();
    return 0;
}