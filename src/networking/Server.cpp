/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:54:32 by aheddak           #+#    #+#             */
/*   Updated: 2023/05/14 13:02:03 by aheddak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.hpp"
#include <limits>
Server::Server()
{
}

Server::Server(std::list<std::pair<std::string, std::string> > infoconfig)
{
	for (std::list<std::pair<std::string, std::string> >::iterator it = infoconfig.begin(); it != infoconfig.end(); it++)
		_infoconfig.push_back(*it);
}

int Server::createSocket(std::string port, std::string ip)
{
	int option;
	int serverFd;
	struct sockaddr_in serverAddress;

	if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		throw SocketException();
	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = inet_addr(ip.c_str());
	serverAddress.sin_port = htons(atoi(port.c_str()));
	option = 1;
	setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
	if (bind(serverFd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
		throw BindException();
	setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
	fcntl(serverFd, F_SETFL, O_NONBLOCK);
	if (listen(serverFd, 80) < 0)
		throw ListenException();
	return serverFd;
}
std::pair<std::pair<std::string, std::string>, int> Server::create(std::pair<std::string, std::string> infos) // Create a socket and bind it to a port
{
	int serverFd;
	std::pair<std::pair<std::string, std::string>, int> info;

	serverFd = createSocket(infos.first, infos.second);
	info.first.first = infos.first;
	info.first.second = infos.second;
	info.second = serverFd;
	return info;
}

bool Server::isListener(int fd)
{
	std::list<std::pair<std::pair<std::string, std::string>, int> >::iterator it;
	for (it = _listners.begin(); it != _listners.end(); it++)
	{
		if (it->second == fd)
			return (TRUE);
	}
	return (FALSE);
}

bool Server::isClient(int fd)
{
    for(std::list<Client>::iterator it =_clients.begin() ; it != _clients.end(); it++)
    {
        if (it->getClientFd() == fd)
        {
            _clients.erase(it);
            return (TRUE);
        }
    }
    return (FALSE);
}

void Server::removeClient(int i, std::map<int, std::string> &client)
{
	client.erase(i);
	close (i);
}

void Server::start(pars &parsing)
{
	int maxFds;
	fd_set writeFds;
	fd_set readFds;
	fd_set backupRead;
	fd_set backupWrite;
	struct timeval timeout;

	signal(SIGPIPE, SIG_IGN);
	FD_ZERO(&backupRead);
	FD_ZERO(&backupWrite);
	FD_ZERO(&readFds);
	FD_ZERO(&writeFds);
	for (std::list<std::pair<std::string, std::string> >::iterator it = _infoconfig.begin(); it != _infoconfig.end(); it++)
		_listners.push_back(create(*it));
	maxFds = std::numeric_limits<int>::min(); 
	for (std::list<std::pair<std::pair<std::string, std::string>, int> >::iterator it = _listners.begin(); it != _listners.end(); it++)
		{
			FD_SET(it->second, &backupRead);
			if (it->second > maxFds)
				maxFds = it->second;
		}
	while (true)
	{
		std::cout << " +++++++ Waiting for new connection ++++++++ fd = " << maxFds << std::endl;

		timeout.tv_sec = 2;
		timeout.tv_usec = 0;
		FD_ZERO(&readFds);
		FD_ZERO(&writeFds);

		readFds = backupRead; // cuz select is destructive
		writeFds = backupWrite;
		if (select(maxFds + 1, &readFds, &writeFds, NULL, &timeout) < 0)
			throw SelectException();
		for (int i = 0; i <= maxFds; i++)
		{
			if (FD_ISSET(i, &readFds) || FD_ISSET(i, &writeFds))
			{
				if (isListener(i))
				{
					struct sockaddr_storage addr;
					int clientSocket;
					socklen_t clientAddrLen;

					clientAddrLen = sizeof(addr);
					clientSocket = accept(i, (struct sockaddr *)(&addr), &clientAddrLen);
					if (clientSocket == -1)
					{
						std::cout << "accept failed  " << std::endl;
						continue ;
					}
					fcntl(clientSocket, F_SETFL, O_NONBLOCK); // Set the new socket to non-blocking mode
					FD_SET(clientSocket, &backupRead);
					if (clientSocket > maxFds)
						maxFds = clientSocket;
					Client c(clientSocket);
					_clients.push_back(c);
					break ;
				}
				else if (FD_ISSET(i, &readFds))
				{
					std::list<Client>::iterator it;
					for (it = _clients.begin(); it != _clients.end(); ++it)
   					{
   					    if(it->_clientFd == i)
							break;
   					}
					char buffer[RECV_SIZE] = {0};
					int rec = recv(i, buffer, RECV_SIZE - 1, 0);
					std::cout << "buffer -> " << buffer << std::endl;
					std::cout << " ################################# " << std::endl;
					if (rec < 0)
					{
						FD_CLR(i, &backupRead);
						FD_CLR(i, &backupWrite);
						isClient(i)	&& close(i);
					}
					it->res_data.r_data.request_append(buffer,rec);
					if (it->res_data.r_data.getread() == true ||( it->res_data.r_data.getk() == -1 && rec == 0))
					{
						// std::cout << "hello im here in cond " << std::endl;
						FD_CLR(i, &backupRead); 
						FD_SET(i, &backupWrite);
						break ;
					}
				}
				else if (FD_ISSET(i, &writeFds))
				{
					std::list<Client>::iterator it;
					for (it = _clients.begin(); it != _clients.end(); ++it)
   					{
   					    if(it->_clientFd == i)
							break;
   					}
					it->res_data.respons(i,parsing);
					if(it->res_data.c <= 0)
					{
						it->res_data.r_data.clear();
						isClient(i) && close (i);
						FD_CLR(i, &backupWrite);
						break ;
					}
				}
			}
		}
	}
	std::cout << "------------------Hello message sent-------------------" << std::endl;
}

/*
 =============================== exceptions =====================================
*/

const char *Server::SocketException::what() const throw()
{
	return ("Error creating socket");
}
const char *Server::BindException::what() const throw()
{
	return ("Error binding socket to address and port");
}
const char *Server::ListenException::what() const throw()
{
	return ("Error listening for incoming connections");
}
const char *Server::SelectException::what() const throw()
{
	return ("Error Server Couldn't select connection");
}
/*
 ================================================================================================
*/
Server::~Server()
{
	for (std::list<std::pair<std::pair<std::string, std::string>, int> >::iterator it = _listners.begin(); it != _listners.end(); it++)
		close(it->second);
}
