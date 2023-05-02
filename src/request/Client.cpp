#include "../../includes/Client.hpp"

// Client::Client(int client): _clientFd(client), _bufferSize(0)
// {
//     memset(_buffer, 0, sizeof(_buffer)); // initialize buffer to all zeros
// }
// Client::~Client(){}

// int					Client::getClientFd(void)const 
// {
//      return (_clientFd);
// }
// char *Client::getBuffer(void)const
// {
// 	return const_cast<char*>(_buffer);

// }

// void Client::setBuffer(char *buffer)
// {
// 	if (buffer != NULL)
// 	{
//         strncpy(_buffer, buffer, sizeof(_buffer) - 1); // copy at most sizeof(_buffer) - 1 bytes
//         _buffer[sizeof(_buffer) - 1] = '\0'; // null-terminate the buffer
//         _bufferSize = strlen(_buffer);
//     }
// 	else 
// 	{
//         _buffer[0] = '\0'; // set buffer to empty string
//         _bufferSize = 0;
//     }
// }

// void Client::setBufferSize(int buffersize)
// {
// 	_bufferSize = buffersize;
// }

// int Client::getBufferSize(void)const
// {
// 	return (_bufferSize);
// }