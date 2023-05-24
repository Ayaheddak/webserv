#include "../../includes/Client.hpp"
Client::Client(int clientfd , std::pair<std::string, std::string> clientInfo) : _clientInfo(clientInfo)
{
	_clientFd = clientfd;
}

std::pair<std::string, std::string> Client::getClientInfo(void)const
{
	return (_clientInfo);
}

int					Client::getClientFd(void)const 
{
     return (_clientFd);
}
void		Client::setClientFd(int clientfd)
{
	_clientFd = clientfd;
}
Client::~Client(){}