#pragma once
#include "Utils.hpp"
#include"Request.hpp"
#include"parsing.hpp"

class Cgi {
    private:
		std::vector<pid_t>					childPids;
		void								_initEnv(Request &request, Config &config ,Location &location);
		char								**_getEnvAsCstrArray() const;
		int									_getSocket(unsigned int port);
		int									_connectSocket(unsigned int port);
		std::map<std::string, std::string>	_env;
		std::string							_body;
	public:
        Cgi(void);
		Cgi(Request &request, Config &config,Location &location);
		Cgi(Cgi const &src);
		virtual ~Cgi(void);

		Cgi   	&operator=(Cgi const &src);
		void executeMultipleCgis(const std::vector<std::string>& scripts);
		std::string		executeCgi(const std::string &scriptName);
};
