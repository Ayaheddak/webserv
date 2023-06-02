/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:29:14 by mrafik            #+#    #+#             */
/*   Updated: 2023/06/01 23:56:03 by mrafik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"cgi.hpp"
#include <sys/types.h>
#include <sys/wait.h>

Cgi::Cgi(Request &request, Config &config,Location &location)
{
    _body = request.getCgibody();
	this->_initEnv(request, config,location);
}

Cgi::~Cgi(void) {
	return ;
}

Cgi	&Cgi::operator=(Cgi const &src) {
	if (this != &src) {
		this->_body = src._body;
		this->_env = src._env;
	}
	return *this;
}

void		Cgi::_initEnv(Request &request, Config &config, Location &location) 
{

	std::map<std::string, std::string>	headers = request.getheader();
	if (headers.find("Auth-Scheme") != headers.end() && headers["Auth-Scheme"] != "")
		this->_env["AUTH_TYPE"] = headers["Authorization"];

	this->_env["REDIRECT_STATUS"] = "200"; //ela qbl secruti to execute php-cgi
	this->_env["GATEWAY_INTERFACE"] = "CGI/1.1";
	this->_env["SCRIPT_NAME"] = location.getCgiExtension(); //path dyql cgi
	std::cout << location.getCgiExtension() << "sadfasdfasdfsdfsdfsdfd\n";
	this->_env["SCRIPT_FILENAME"] = location.getCgiExtension() + location.getCgiPath(); //+  request.getPath() ; //the full path
	this->_env["REQUEST_METHOD"] = request.getMethod(); // http used    get ola post
	 std::stringstream ss;
    ss << this->_body.length();
	// this->_env["HTTP_COOKIE"] = 
	this->_env["CONTENT_LENGTH"] = ss.str(); // lenght dyql body
	this->_env["CONTENT_TYPE"] = headers["Content-Type"];
	this->_env["PATH_INFO"] = request.getPath(); // path dyal request source
	this->_env["PATH_TRANSLATED"] = request.getPath(); // same
	this->_env["QUERY_STRING"] = request.getPath().substr(request.getPath().find('?')+1);
	std::cerr<< this->_env["QUERY_STRING"] << "FHDdsfgsdfgdsgds\n";
	this->_env["REMOTEaddr"] = config.getHost(); // ip dyal client
	this->_env["REMOTE_IDENT"] = headers["Authorization"];
	this->_env["REMOTE_USER"] = headers["Authorization"];
	this->_env["REQUEST_URI"] = request.getPath();
	if (headers.find("Hostname") != headers.end())
		this->_env["SERVER_NAME"] = headers["Hostname"];
	else
		this->_env["SERVER_NAME"] = this->_env["REMOTEaddr"];
	this->_env["SERVER_PORT"] = config.getListen();
	this->_env["SERVER_PROTOCOL"] = "HTTP/1.1";
	this->_env["SERVER_SOFTWARE"] = "Weebserv/1.0";

	//this->_env.insert(config.get_cgi_pram().begin(), config.get_cgi_pram().end());
}

char					**Cgi::_getEnvAsCstrArray() const {
	char	**env = new char*[this->_env.size() + 1];
	int	j = 0;
	for (std::map<std::string, std::string>::const_iterator i = this->_env.begin(); i != this->_env.end(); i++) {
		std::string	element = i->first + "=" + i->second;
		env[j] = new char[element.size() + 1];
		env[j] = std:: strcpy(env[j], (const char*)element.c_str());
		j++;
	}
	env[j] = NULL;
	return env;
}

std::string		Cgi::executeCgi(const std::string& script)
{
	pid_t		pid;
	int			saveStdin;
	int			saveStdout;
	char		**env;
	std::string	newBody;

	try {
		env = this->_getEnvAsCstrArray();
	}
	catch (std::bad_alloc &e) {
		std::cerr << e.what() << std::endl;
	}

	saveStdin = dup(0);
	saveStdout = dup(1);
	FILE	*fIn = tmpfile();
	FILE	*fOut = tmpfile();
	long	fdIn = fileno(fIn);
	long	fdOut = fileno(fOut);
	int		ret = 1;

	write(fdIn, _body.c_str(), _body.size());
	std::cerr<< "ORIGINAL BODY============>> "<<_body << "\n";
	lseek(fdIn, 0, SEEK_SET);
	pid = fork();

	if (pid == -1)
	{
		std::cerr << "Fork Faild."<< std::endl;
		return ("Status: 500\r\n\r\n");
	}
	else if (!pid)
	{
		//char * const * nll = NULL;

		dup2(fdIn, 0);
		dup2(fdOut, 1);
		std::string  yy;
		char **str = new char*[3];
		//if(script.find(".php"))
			str[0] = strdup("/usr/bin/php");
		//if(script.find(".py"))
			//str[0] = strdup("/usr/bin/python");
		str[1]= strdup(script.c_str());
		str[2] =NULL;
		execve(str[0], str, env);
		perror("Error:----->");
		std::cerr << "Execve Faild." << std::endl;
		write(1, "Status: 500\r\n\r\n", 15);
	}
	else
	{
		char	buffer[1024] = {0};

		waitpid(-1, NULL, 0);
		lseek(fdOut, 0, SEEK_SET);

		ret = 1;
		std::cerr<< "BEFORE++++++++++new=body===========.>>>>>"<< newBody <<"\n";
		//return (newBody);
		while (ret > 0)
		{
			memset(buffer, 0, 1024);
			ret = read(fdOut, buffer, 1024 - 1);
			newBody += buffer;
		}
		std::cerr<< "AFTER+++++++++new=body===========.>>>>>"<< newBody <<"\n";
	}
	dup2(saveStdin, STDIN_FILENO);
	dup2(saveStdout, STDOUT_FILENO);
	fclose(fIn);
	fclose(fOut);
	close(fdIn);
	close(fdOut);
	close(saveStdin);
	close(saveStdout);

	for (size_t i = 0; env[i]; i++)
		delete[] env[i];
	delete[] env;

	if (!pid)
		exit(0);
std::cerr<< "new=body===========.>>>>>"<< newBody <<"\n";
	return (newBody);
}

// void Cgi :: executeMultipleCgis(const std::vector<std::string>& scripts) 
// {
// 	for (std::vector<std::string>::const_iterator it = scripts.begin(); it != scripts.end(); ++it) 
// 	{
// 		pid_t pid = fork();
// 		if (pid == -1) {
// 			std::cerr << "Fork failed." << std::endl;
// 			exit(EXIT_FAILURE);
// 		} else if (pid == 0) {
// 			char * const * nll = NULL;
// 			char **env = _getEnvAsCstrArray();
// 			execve(it->c_str(), nll, env);
// 			std::cerr << "Execve failed." << std::endl;
// 			write(1, "Status: 500\r\n\r\n", 15);
// 			exit(1);
// 		} 
// 		else {
// 				childPids.push_back(pid);
// 			}
// 	}
// 	for (std::vector<pid_t>::const_iterator it = childPids.begin(); it != childPids.end(); ++it) {
// 		int status;
// 		do {
// 			if (waitpid(*it, &status, WUNTRACED | WCONTINUED) == -1) {
// 				perror("waitpid");
// 				exit(EXIT_FAILURE);
// 			}
// 		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
// 	}
// }