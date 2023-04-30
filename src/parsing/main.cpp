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
    std::vector<data>::iterator it;
    for (it = s_data.begin(); it != s_data.end(); it++)
    {
    }
    return 0;

}