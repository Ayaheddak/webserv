/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_files.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:55:00 by aheddak           #+#    #+#             */
/*   Updated: 2023/05/14 13:20:15 by aheddak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.hpp"
bool isDuplicateServer(std::vector<Config>& servers)
{
    for (std::vector<Config>::iterator it1 = servers.begin(); it1 != servers.end(); ++it1)
    {
        for (std::vector<Config>::iterator it2 = it1 + 1; it2 != servers.end(); ++it2)
        {
            if (it1->getHost() == it2->getHost() && it1->getListen() == it2->getListen())
                return true;
        }
    }
    return false;
}

void Config::check_servers(char *inputfile, std::vector<Config>& servers)
{
	std::ifstream infile(inputfile);
	std::string		line;
	std::string		str;

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

std::vector<Config> Servers(char *file)
{
	std::vector<Config> servers;
	Config newServer;
	newServer.check_servers(file, servers);
	for (std::vector<Config>::iterator it = servers.begin(); it != servers.end(); ++it)
		;
	if (isDuplicateServer(servers) == true )
	{
		std::cerr << "Error: duplicate server" << std::endl;
		exit(0);
	}
	std::cout << "everything is ok" << std::endl;
	return servers;
}