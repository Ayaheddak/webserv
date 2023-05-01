#include "../../includes/Server.hpp"
#include "../../includes/parsing.hpp"
Server::Server()
{
}

Server::Server(std::list<std::pair<std::string, std::string> > infoconfig)
{
	for (std::list<std::pair<std::string, std::string> >::iterator it = infoconfig.begin(); it != infoconfig.end(); it++)
		_infoconfig.push_back(*it);
}

int Server::createSocket(std::string port, std::string ip) // function to create a socket
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

void Server::start(pars &parsing)
{
	int maxFds;
	fd_set writeFds;
	fd_set readFds;
	fd_set backupRead;
	fd_set backupWrite;
	struct timeval timeout;
	// char buff[30000] = {0};

	signal(SIGPIPE, SIG_IGN);
	FD_ZERO(&backupRead);
	FD_ZERO(&backupWrite);
	FD_ZERO(&readFds);
	FD_ZERO(&writeFds);
	for (std::list<std::pair<std::string, std::string> >::iterator it = _infoconfig.begin(); it != _infoconfig.end(); it++)
		_listners.push_back(create(*it));
	// maxFds = _listners.size();
	maxFds = std::numeric_limits<int>::min(); 
	for (std::list<std::pair<std::pair<std::string, std::string>, int> >::iterator it = _listners.begin(); it != _listners.end(); it++)
		{
			FD_SET(it->second, &backupRead);
			if (it->second > maxFds)
				maxFds = it->second; // Update the maximum value
		}
	while (true)
	{
		std::cout << "+++++++ Waiting for new connection ++++++++    " << maxFds << std::endl;

		timeout.tv_sec = 1;
		timeout.tv_usec = 0;
		FD_ZERO(&readFds);
		FD_ZERO(&writeFds);

		readFds = backupRead; // cuz select is destructive
		writeFds = backupWrite;
		if (select(maxFds + 1, &readFds, &writeFds, NULL, NULL) < 0)
		{
			std::cout << "Error in select line 97 " << std::endl;
			// exit(0);
		}
		for (int i = 0; i <= maxFds; i++)
		{
			if (FD_ISSET(i, &readFds) || FD_ISSET(i, &writeFds))
			{
				if (isListener(i)) // if i is between servers fds accept new connection
				{
					struct sockaddr_storage addr;
					int clientSocket;
					socklen_t clientAddrLen;

					clientAddrLen = sizeof(addr);
					clientSocket = accept(i, (struct sockaddr *)(&addr), &clientAddrLen);
					if (clientSocket == -1)
					{
						std::cout << "accept failed  " << std::endl;
						continue;
					}
					std::cout << "accept okey ^^  and new socket -> " << clientSocket << std::endl;
					// Add the new client socket to the file descriptor set for select()
					fcntl(clientSocket, F_SETFL, O_NONBLOCK); // Set the new socket to non-blocking mode
					// FD_SET(clientSocket, &backupRead);
					FD_SET(clientSocket, &backupRead);
					if (clientSocket > maxFds)
						maxFds = clientSocket;
					Client client(clientSocket);
					_clients.push_back(client);
					break;
				}
				else if (FD_ISSET(i, &readFds))
				{
					char buff[1025] = {0};
					int rec = read(i, buff, 1024);
					// std::cout << "rec --> "<< rec << std::endl;
					// std::cout << "buffer --> "<< buff << std::endl;
					if (rec <= 0)
					{
						//std::cout << "connection closed " << std::endl;
						FD_CLR(i, &backupRead);
						if (rec == 0)
						{
							FD_SET(i, &backupWrite);
							continue;
						}
						close(i);
						break;
						// _clients.erase();
					}
					else
					{
						// std::cout << "rec --> "<< rec << std::endl;
						// std::cout << "buffer --> "<< buff << std::endl;
						
						std::string request(buff, rec);
						std::cout << request << std::endl;
						parsing.fill_request(request);
						parsing.respons(i);
						//client.lenght += rec; 
					}
				}
				else if (FD_ISSET(i, &writeFds))
				{
					// std::cout << "write" << std::endl;
					// 
					char *buff; // generated response string
					int contentLenght = 1000; // calculated content leght 
					int ret = write(i, buff,  contentLenght);
					if (ret <= 0){
						FD_CLR(i, &backupWrite);
						close(i);
						//client remove from list;
					}
				}
			}
		}
		// for (std::list<Client>::iterator it = _clients.begin() ; it != _clients.end(); it++)
		// {
		// 	std::cout << "client --> " << it->getClientFd() << std::endl;
		// }
		// for (std::list<Client>::iterator it = _clients.begin(); it != _clients.end(); it++)
		// {
		// 	if (FD_ISSET(it->getClientFd(), &backupRead))
		// 	{
		// 	}
		// 	// else if (FD_ISSET(it->getClientFd(), &backupWrite))
		// 	// {
		// 	// 	std::cout << "hello"<< std::endl;
		// 	// }
		// }
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
/*
 ================================================================================================
*/
Server::~Server()
{
	for (std::list<std::pair<std::pair<std::string, std::string>, int> >::iterator it = _listners.begin(); it != _listners.end(); it++)
		close(it->second);
}