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
    check_arguments(argc);
    pars parsing(argv[1]);
    std::vector<data>::iterator it;
    for (it = parsing.s_data.begin(); it != parsing.s_data.end(); it++)
    {
        _port.push_back(std::make_pair(it->listen, "127.0.0.1"));
    }
    Server server(_port);
    server.start(parsing);
    return 0;
}