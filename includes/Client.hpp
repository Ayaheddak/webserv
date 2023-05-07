# ifndef CLIENT_HPP
#define CLIENT_HPP
#include "Utils.hpp"
class Client
{
    private :
		int					_clientFd;

	public :
		Client(int clientfd);
		int			getClientFd(void)const;
		void		setClientFd(int clientfd);
		~Client();
};
#endif