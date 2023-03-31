# ifndef TCPSERVER_HPP
#define TCPSERVER_HPP

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <cstring>
#define PORT 8080


class TcpServer
{
    private :
        int                     _server_fd;
        int                     _new_socket;
        int                     _port;
        int                     _addrlen;
        // int                     _valread;//incomingmessage
        std::string             _host;
        struct sockaddr_in      _address;
    public :
        /* 
            =============================== canonical form ===================================== 
        */

            TcpServer(void);
            TcpServer(std::string host, int port);
            // TcpServer(TcpServer const & src );
            // TcpServer & operator=(TcpServer const & rhs);
            ~TcpServer();

        /* 
            =============================== methods ===================================== 
        */

            void    createSocket();//std::string host, int port);
            void    Bind();//std::string host ,int port);
            void    Listen();
            void    Accept();
       
        /* 
            =============================== getters && setters ===================================== 
        */
            void                setSocketAdd(std::string host, int port);
            int                 getFdServer();
            struct sockaddr_in	getSocketAddress();
            int                 getNewSocket();
    
        /*
            =============================== exceptions ===================================== 
        */

            struct SocketException : public std::exception
            {
                public :
                    const char * what () const throw ();
            };
            struct BindException : public std::exception 
            {
                public :
                    const char * what () const throw ();
            };
            struct ListenException : public std::exception 
            {
                public :
                    const char * what () const throw ();
            };
};
#endif