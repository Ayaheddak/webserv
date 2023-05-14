/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:54:44 by aheddak           #+#    #+#             */
/*   Updated: 2023/05/14 13:28:07 by aheddak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.hpp"
#include "../../includes/Server.hpp"
#include "../parse/parsing.hpp"
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
    check_arguments(argc);
    std::list<std::pair<std::string, std::string> > _port;
	std::vector<Config> servers;
	servers = Servers(avgv[1]);
    for (std::vector<Config> it = servers.begin(); it != servers.end(); it++)
    {
        _port.push_back(it->getListen(), it->getHost());
		std::cout << it->getHost() << std::endl;
		std::cout << it->getListen() << std::endl;
    }
    Server server(_port);
    server.start(parsing);
    return 0;
}