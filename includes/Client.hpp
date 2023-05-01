# ifndef CLIENT_HPP
#define CLIENT_HPP
#include "Utils.hpp"
class Client
{
    private :
		int					_clientFd;
		int					_bufferSize;
		char 				_buffer[1024];
	public :
		Client(int client);
		// Client(int client , char *buffer, int bufferSize);
		void	setBuffer(char *buffer);
		void	setBufferSize(int bufferSize);
		int		getClientFd(void)const;
		char	*getBuffer(void)const;
		int		getBufferSize(void)const;
		~Client();
};
#endif