#include "../../includes/parsing.hpp"
#include "../../includes/Server.hpp"
void check_arguments(int argc)
{
    if(argc > 2)
    {
        std::cerr<<"Too many arguments" << std::endl;
        exit(1);
    }
}

int main(int argc,char **argv) 
{
    std::list<std::pair<std::string, std::string> > _port;
    std::vector<Config> servers;
    check_arguments(argc);
 	servers = Servers(argv[1]);
    _port.push_back(std::make_pair(servers[0].getHost(), servers[0].getListen()));
    Server server(_port);
    server.start(servers);
    return 0;
}