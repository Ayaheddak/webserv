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
	try {
    std::list<std::pair<std::string, std::string> > _port;
    std::vector<Config> servers;
    check_arguments(argc);
 	servers = Servers(argv[1]);
	//loop through servers and create a list of ip and port
	for(size_t i = 0; i < servers.size(); i++)
		_port.push_back(std::make_pair(servers[i].getHost(), servers[i].getListen()));
    // _port.push_back(std::make_pair(servers[0].getHost(), servers[0].getListen()));
    Server server(_port, servers);
    server.start(servers);
	}
	catch (std::exception &e) 
	{
		std::cerr << e.what() << std::endl;
	}
    return 0;
}