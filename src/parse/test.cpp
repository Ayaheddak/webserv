/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:55:58 by aheddak           #+#    #+#             */
/*   Updated: 2023/05/14 13:00:44 by aheddak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.hpp"
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
int main(int ac , char **av) 
{
	(void)ac;
	std::vector<Config> servers;
	servers = Servers(av[1]);
    return 0;
}