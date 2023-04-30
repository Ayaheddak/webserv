#include <iostream>
#include "../../includes/parsing.hpp"
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
void check_arguments(int argc,char **argv)
{
    if(argc > 2)
    {
        std::cerr<<"Too many arguments" << std::endl;
        exit(1);
    }
    (void)argv;
}
int main(int argc,char **argv)
{
    check_arguments(argc,argv);
    pars parsing(argv[1]);
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(8888);
    bind(sock, (struct sockaddr *)&addr, sizeof(addr));
    listen(sock, 1);
    std::vector<loc>::iterator it;
    while(true)
    {
        
        int client_sock = accept(sock, NULL, NULL);

        char buf[4096];
        ssize_t nread = recv(client_sock, buf, sizeof(buf), 0);
        if (nread < 0) {
            std::cerr << "Error reading from client" << std::endl;
        } else {
            std::string request(buf, nread);
            std::cout << request << std::endl;
            parsing.fill_request(request);
            parsing.respons(client_sock);
        }
        close(client_sock);
    }
    return 0;

}
       if (nread < 0) {
            std::cerr << "Error reading from client" << std::endl;
        } else {
            std::string request(buf, nread);
            std::cout << request << std::endl;
            parsing.fill_request(request);
            parsing.respons(client_sock);
        }