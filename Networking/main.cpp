#include "TcpServer.hpp"
#include "../parsing/parsing.hpp"
// void check_arguments(int argc,char **argv)
// {
//     if(argc > 2)
//     {
//         std::cerr<<"Too many arguments" << std::endl;
//         exit(1);
//     }
//     (void)argv;
// }

int main (int ac , char **av)
{
    // check_arguments(ac,av);
    // pars parsing(av[1]);
    // data parse;
    // parsing.parse();
    // std::cout << "server_name: " << parsing.check_data.server_name << std::endl;
    
    std::string hello("HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!");
    // TcpServer s(parse, atoi(parse.listen.c_str()));
    TcpServer s("127.0.0.1", PORT);
    s.createSocket();
    s.Bind();
    s.Listen();
    while (1)
    {
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        s.Accept();
        char buffer[30000] = {0};
        long vread ;;
        vread = read( s.getNewSocket() , buffer, 30000);
        printf("buffer ---> %s\n",buffer );
        write(s.getNewSocket() , hello.c_str() , strlen(hello.c_str()));
        printf("------------------Hello message sent-------------------\n");
    }
    return 0;
}