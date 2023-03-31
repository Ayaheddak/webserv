#include "TcpServer.hpp"
/* 
    =============================== canonical form =====================================
*/
    TcpServer::TcpServer()
    {
    }

    TcpServer::TcpServer(std::string host, int port) : _host(host),_port(port)//,_addrlen(sizeof(_address))
    {
        setSocketAdd(_host, _port);
        createSocket();
    }

    TcpServer::~TcpServer()
    {
        close(_server_fd);
        close(_new_socket);
    }
// TcpServer::TcpServer(TcpServer const & src)
// {
//     *this = src;
// }

// TcpServer& TcpServer::operator=(TcpServer const & rhs)
// {  
//     if (this != &rhs)
//     {
//         _server_fd = rhs.getServerFd();
//         _new_socket = rhs.getNewSocket();
//         _addrlen = rhs.getAddrlen();
//         _valread = rhs.getValread();
//         _address = rhs.getAddress();
//     }
//     return (*this);
// }
// {

/*
=============================== setters && getters =====================================
*/

    void    TcpServer::setSocketAdd(std::string host, int port)
    {
        _address.sin_family = AF_INET;
        if (host.compare("") == 0)
            _address.sin_addr.s_addr =INADDR_ANY;
        else
            _address.sin_addr.s_addr = inet_addr(host.c_str());
        _address.sin_port = htons(port);
    }
    int					TcpServer::getFdServer()
    {
	    return (this->_server_fd);
    }
    struct sockaddr_in	TcpServer::getSocketAddress() 
    {
	    return (this->_address);
    }
    int TcpServer::getNewSocket()
    {
        return (_new_socket);
    }
    
/*
  =============================== methods =====================================
*/

    void    TcpServer::createSocket()
    {
    //using the IPv4 Internet protocols defined by the AF_INET domain, using SOCK_STREAM - to allow for reliable, full-duplex byte streams.
        if ((_server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
            throw SocketException();
        else
            std::cout << "sc\n";
    }

    void    TcpServer::Bind()//std::string host ,int port)
    {
        int tmp;

        tmp = 1;
        setsockopt(_server_fd, SOL_SOCKET, SO_REUSEADDR , &tmp, sizeof(tmp));
        if (bind(_server_fd, (struct sockaddr * ) &_address, sizeof(_address)) < 0)
            throw BindException();
        else
            std::cout << "Bind succ" << std::endl;
    }

    void    TcpServer::Accept()
    {
        _addrlen = sizeof(_address);
        if ((_new_socket = accept(_server_fd, (struct sockaddr *)&_address, (socklen_t*)&_addrlen)) < 0)
            std::cerr << "err" <<std::endl;
        else
            std::cout << "Connection accepted" << std::endl;
    }

    void    TcpServer::Listen()
    {
        if (listen(_server_fd, 10000) < 0)
            throw ListenException();
        else
            std::cout << "Listening..." << std::endl;
    }

/* 
 =============================== exceptions ===================================== 
*/

    const char * TcpServer::SocketException::what () const throw ()
    {
        return ("Socket creation error");
    }
    const char * TcpServer::BindException::what () const throw ()
    {
        return ("Bind failed");
    }
    const char * TcpServer::ListenException::what () const throw ()
    {
        return ("Listen failed");
    }