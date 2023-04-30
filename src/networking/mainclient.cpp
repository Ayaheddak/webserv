#include "../../includes/Utils.hpp"
int main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in servaddr;
    char buffer[1024];

    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <IP address> <port>" << std::endl;
        return 1;
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);
    servaddr.sin_port = htons(atoi(argv[2]));

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        std::cerr << "Error connecting to server" << std::endl;
        close(sockfd);
        return 1;
    }

    strcpy(buffer, "Hello, server!");
    if (send(sockfd, buffer, strlen(buffer), 0) < 0) {
        std::cerr << "Error sending message to server" << std::endl;
        close(sockfd);
        return 1;
    }

    memset(buffer, 0, sizeof(buffer));
    if (recv(sockfd, buffer, sizeof(buffer), 0) < 0) {
        std::cerr << "Error receiving message from server" << std::endl;
        close(sockfd);
        return 1;
    }
    std::cout << "Received message: " << buffer << std::endl;

    close(sockfd);
    return 0;
}
