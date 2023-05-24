# ifndef CLIENT_HPP
#define CLIENT_HPP
#include "Utils.hpp"
#include "Response.hpp"
class Client
{
   public :
		int										_clientFd; // private
		Response								res_data;
		std::pair<std::string, std::string>		_clientInfo; // private 
	
		Client(int clientfd , std::pair<std::string, std::string> clientInfo);
		std::pair<std::string, std::string> getClientInfo(void)const;
		int			getClientFd(void)const;
		void		setClientFd(int clientfd);
		~Client();
};
#endif