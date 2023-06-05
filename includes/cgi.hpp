#pragma once
#include "Utils.hpp"
#include"Request.hpp"
#include"parsing.hpp"
#include "Response.hpp"

class Cgi {
    private:
		void								_initEnv(Request &request,Location &location,Config &confi);
		std::string							_body;
	public:
        Cgi(void);
		Cgi(Request &request, Config &config,Location &location);
		Cgi(Cgi const &src);
		~Cgi(void);

		Cgi   	&operator=(Cgi const &src);
		std::string		executeCgi(const std::string &scriptName);
};
