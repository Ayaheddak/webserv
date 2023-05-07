#include "../../includes/Utils.hpp"
#include "parsing.hpp"
bool isDuplicateServer(std::vector<Config>& servers, Config server)
{
    for (std::vector<Config>::iterator it = servers.begin(); it != servers.end(); ++it)
    {
        if (it->getServerName() == server.getServerName() && it->getListen() == server.getListen())
        {
            return true;
        }
    }
    return false;
}


int main(int ac , char **av) 
{
	(void)ac;
	std::vector<Config> servers;
    Config newServer;
    newServer.check_servers(av[1], servers);
    
    for (std::vector<Config>::iterator it = servers.begin(); it != servers.end(); ++it)
    {
		std::cout << "add server" <<std::endl;
    }
    
    return 0;
}