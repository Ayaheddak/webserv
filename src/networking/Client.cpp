#include "../../includes/Client.hpp"

Client::Client(int client)
{
    _clientFd = client;
    // _info = info;

}
Client::~Client(){ }

int					&Client::getClientFd () 
{
     return (_clientFd);
}

// struct sockaddr_in	&Client::getClientAddress () 
// { 
//     return (_clientAddress); 
// }