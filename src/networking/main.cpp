#include "../../includes/parsing.hpp"
#include "../../includes/Server.hpp"
char* check_arguments(int argc, char** argv) 
{
    if (argc > 2) {
        std::cerr << "Too many arguments" << std::endl;
        exit(1);
    } else if (argc == 2) {
        std::string str = argv[1];
        if (str.find(".conf") == std::string::npos) {
            std::cerr << "Invalid file extension" << std::endl;
            exit(1);
        }
        char* file = new char[str.length() + 1]; 
        std::strcpy(file, str.c_str()); 
        return file;
    } else {
        std::ifstream infile("default.conf");
        if (!infile.is_open()) {
            std::cerr << "Configuration file not found" << std::endl;
            exit(0);
        }
        char* file = new char[13];
        std::strcpy(file, "default.conf");
        return file;
    }
}
int main(int argc,char **argv) 
{
	try
	{
    	std::list<std::pair<std::string, std::string> > _port;
    	std::vector<Config> servers;
		char* result;
		result = check_arguments(argc, argv);
 		servers = Servers(result);
		delete[] result;
		for(size_t i = 0; i < servers.size(); i++)
			_port.push_back(std::make_pair(servers[i].getHost(), servers[i].getListen()));
    	Server server(_port, servers);
    	server.start(servers);
	}
	catch (std::exception &e) 
	{
		std::cerr << e.what() << std::endl;
	}
    return 0;
}