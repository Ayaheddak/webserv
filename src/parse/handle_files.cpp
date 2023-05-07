#include "parsing.hpp"
// bool duplicate_server(std::vector<Config>& servers, Config& s)
// {
// 	std::vector<Config>::iterator it;
// 	for (it = servers.begin(); it != servers.end(); it++)
// 		if (it->getServerName() == s.getServerName() && it->getListen() == s.getListen() && it->getServerName() == s.getServerName())
// 			return (true);
// 	return (false);
// }

void Config::check_servers(char *inputfile, std::vector<Config>& servers)
{
	std::ifstream infile(inputfile);
	std::string		line;
	std::string		str;
	// Config			server;

	if (!infile.is_open())
	{
		std::cerr << "Configuration file not found"<< std::endl;
		exit(0);
	}
	while(!infile.eof())
	{
		getline(infile, line);
		str = removeLeadingWhitespace(line);
		if (str.empty())
		{
			std::cerr << "Error : empty line is not alloweeeeeeeeeeeeeeeeeeed"  << std::endl;
			exit(0);
		}
		if (str.find("server") != std::string::npos)
		{
			if (str != "server")
			{
				std::cerr << "Error: server error idk" << std::endl;
				exit (0);
			}
			else
			{
				Config			server;
				getline(infile, line);
				server.check_config(infile, line);
				if(server.getHost().empty() || server.getServerName().empty() || server.getListen().empty() || server.getLocations().empty())
				{
					std::cerr << "Error : waa khsnaa host,servername and listen ... " << std::endl;
					exit(0);
				}
				if (isDuplicateServer(servers,server) == true )
        		{
        		    std::cerr << "Error: duplicate server" << std::endl;
        		    exit(0);
        		}
				servers.push_back(server);
			}
		}
		else
		{
			std::cerr << "Error : in config file" << std::endl;
			exit (0);
		}
	}
}