# ifndef CLIENT_HPP
#define CLIENT_HPP
#include "Utils.hpp"
#include "Response.hpp"
class Client
{
   public :
		int					_clientFd;
		Response			res_data;
	
		Client(int clientfd);
		int			getClientFd(void)const;
		void		setClientFd(int clientfd);
		~Client();
};
#endif