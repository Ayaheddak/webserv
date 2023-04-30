# ifndef CLIENT_HPP
#define CLIENT_HPP
#include "Utils.hpp"
class Client
{
    private:
		int					_clientFd;
		// std::pair<std::string , std::string> _info;
		// struct sockaddr_in	_clientAddress;
	public:
		// Client(int client, std::pair<std::string , std::string> info);
		Client(int client);//, std::pair<std::string , std::string> info);
		~Client();
		// struct sockaddr_in	&getClientAddress ();
		int					&getClientFd ();

};
#endif