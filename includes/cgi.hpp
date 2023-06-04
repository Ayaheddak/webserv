#pragma once
#include "Utils.hpp"
#include"Request.hpp"
#include"parsing.hpp"
#include "Response.hpp"

class Cgi {
    private:
		void								_initEnv(Request &request, Config &config ,Location &location);
		char								**_getEnvAsCstrArray() const;
		int									_getSocket(unsigned int port);
		int									_connectSocket(unsigned int port);
		void								_initEnv2(Request &request,Location &location,Config &confi);
		std::map<std::string, std::string>	_env;
		std::string							_body;
	public:
        Cgi(void);
		Cgi(Request &request, Config &config,Location &location);
		Cgi(Cgi const &src);
		virtual ~Cgi(void);

		Cgi   	&operator=(Cgi const &src);
		std::string		executeCgi(const std::string &scriptName);
};
