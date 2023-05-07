# ifndef SERVER_HPP
#define SERVER_HPP

#include "Utils.hpp"
#include "parsing.hpp"
#include "Client.hpp"
class Server
{
    private :
		std::list<std::pair<std::string, std::string> > 		                _infoconfig;
        std::list<std::pair <std::pair<std::string, std::string>, int> >  	    _listners;
        std::list<Client>                                              			_clients;
    public :
        Server();
		Server(std::list<std::pair<std::string, std::string> > infoconfig);
        ~Server();

		int createSocket(std::string port, std::string ip);
        std::pair <std::pair<std::string, std::string>, int> create(std::pair <std::string , std::string > infos);
        bool isListener(int fd);
		// bool isClient(int fd);
        void removeClient(int i, std::map<int, std::string> &client);//,fd_set &backupread, fd_set &backupwrite, bool b);
        // void	Socket::remove_client(int i, std::map<int,  Client> &clients, bool rd, bool wr);
		// std::list<Client>::iterator	getClient(int fd);
        void Form();
        void start(pars &parsing);
		bool isClient(int fd);
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
			struct SelectException : public std::exception
            {
                public :
                    const char * what () const throw ();
            };
};

#endif