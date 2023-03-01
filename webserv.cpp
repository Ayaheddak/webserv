
// int server_fd = socket(domain, type, protocol);//call creates a socket in the specified domain and of the specified type.
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        std::cout << "Error creating socket: " << errno << std::endl;
    } else {
        std::cout << "Socket created successfully" << std::endl;
    }
    return 0;
}
