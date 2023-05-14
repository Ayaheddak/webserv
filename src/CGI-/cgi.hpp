#pragma once
#include<string>
#include<iostream>
#include<map>
#include <fcntl.h>
#include <unistd.h>

class Cgi {
    private:
		void								_initEnv(Request &request, config &config);
		char								**_getEnvAsCstrArray() const;
		int									_getSocket(unsigned int port);
		int									_connectSocket(unsigned int port);
		std::map<std::string, std::string>	_env;
		std::string							_body;
	public:
        Cgi(void);
		Cgi(Request &request, config &config);
		Cgi(Cgi const &src);
		virtual ~Cgi(void);

		Cgi   	&operator=(Cgi const &src);
		std::string		executeCgi(const std::string &scriptName);
};