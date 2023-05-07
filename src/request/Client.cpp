#include "../../includes/Client.hpp"
Client::Client(int clientfd)
{
	_clientFd = clientfd;
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