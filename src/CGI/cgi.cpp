#include"../../includes/cgi.hpp"
#include <sys/types.h>
#include <sys/wait.h>
#include<signal.h>
void		Cgi::_initEnv(Request &request, Config &config, Location &location) 
{

	std::map<std::string, std::string>	headers = request.getheader();
	if (headers.find("Auth-Scheme") != headers.end() && headers["Auth-Scheme"] != "")
		this->_env["AUTH_TYPE"] = headers["Authorization"];

	this->_env["REDIRECT_STATUS"] = "200"; //ela qbl secruti to execute php-cgi
	this->_env["GATEWAY_INTERFACE"] = "CGI/1.1";
	this->_env["SCRIPT_NAME"] = location.getCgiExtension(); //path dyql cgi
	// std::cout << location.getCgiExtension() << "sadfasdfasdfsdfsdfsdfd\n";
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
extern char **environ;

Cgi::Cgi(Request &request, Config &config,Location &location)
{
    _body = request.getCgibody();
	this->_initEnv2(request,location);
	//int i = 0;
	//while(environ[i])
	//	std::cout << environ[i++] << std::endl;
	(void) config;
	//this->_initEnv(request, config,location);
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

void Cgi::_initEnv2(Request& request, Location& location) 
{
    std::map<std::string, std::string> headers = request.getheader();

    for (std::map<std::string, std::string>::iterator it = headers.begin(); it != headers.end(); ++it) {
        std::string key = it->first;
        key.insert(0, "HTTP_");
        for (std::string::size_type i = 0; i < key.length(); ++i) {
            key[i] = std::toupper(key[i]);
        }
        std::replace(key.begin(), key.end(), '-', '_');
        std::string value = it->second.substr(1);
        setenv(key.c_str(), value.c_str(), true);
    }
    
    std::string scriptName = location.getCgiExtension();
    setenv("SCRIPT_NAME", scriptName.c_str(), true);
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
	//  char		**env;
	std::string	newBody;

	// try {
	// 	env = this->_getEnvAsCstrArray();
	// }
	// catch (std::bad_alloc &e) {
	// 	std::cerr << e.what() << std::endl;
	// }
	saveStdin = dup(0);
	saveStdout = dup(1);
	FILE	*fIn = tmpfile();
	FILE	*fOut = tmpfile();
	long	fdIn = fileno(fIn);
	long	fdOut = fileno(fOut);
	int		ret = 1;

	write(fdIn, _body.c_str(), _body.size());
	// std::cerr<< "ORIGINAL BODY============>> "<<_body << "\n";
	lseek(fdIn, 0, SEEK_SET);
	pid = fork();

	if (pid == -1)
	{
		std::cerr << "Fork Faild."<< std::endl;
		return ("Status: 500\r\n\r\n");
	}
	else if (!pid)
	{
		dup2(fdIn, 0);
		dup2(fdOut, 1);
		std::string  yy;
		char **str = new char*[3];
		if(script.find(".php") !=  std::string::npos)
			str[0] = strdup("php-cgi");
		else if(script.find(".py") !=  std::string::npos)
			str[0] = strdup("/usr/bin/python");
		str[1]= strdup(script.c_str());
		str[2] =NULL;
		//for(int i = 0; environ[i];i++)
		//	std::cout << environ[i] << std::endl; 
		execve(str[0], str, environ);
		perror("Error:----->");
		std::cerr << "Execve Faild." << std::endl;
		write(1, "Status: 500\r\n\r\n", 15);
	}
	else
	{
		char	buffer[1024] = {0};
		size_t start=time(NULL);
		int status = -1;
		while((time(NULL) - start) < 10)
		{
			if(waitpid(pid, NULL,WNOHANG ) == pid)
			{
				status = 0;
				break;
			}
		}
		if(status == -1)
		{
			kill(pid, SIGKILL);
			return("Timeout");
		}
		lseek(fdOut, 0, SEEK_SET);
		ret = 1;
		while (ret > 0)
		{
			memset(buffer, 0, 1024);
			ret = read(fdOut, buffer, 1024 - 1);
			newBody += buffer;
		}
	}
	dup2(saveStdin, STDIN_FILENO);
	dup2(saveStdout, STDOUT_FILENO);
	fclose(fIn);
	fclose(fOut);
	close(fdIn);
	close(fdOut);
	close(saveStdin);
	close(saveStdout);

	// for (size_t i = 0; env[i]; i++)
	// 	delete[] env[i];
	//delete[] env;

	if (!pid)
		exit(0);

std::cerr<< "new=body===========.>>>>>"<< newBody <<"\n";
	return (newBody);
}
