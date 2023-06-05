#include"../../includes/cgi.hpp"
#include <sys/types.h>
#include <sys/wait.h>
#include<signal.h>

extern char **environ;

Cgi::Cgi(Request &request, Config &config,Location &location)
{
    _body = request.getCgibody();
	this->_initEnv(request,location,config);
}

Cgi::~Cgi(void) {
	return ;
}

Cgi	&Cgi::operator=(Cgi const &src) {
	if (this != &src)
		this->_body = src._body;
	return *this;
}

void Cgi::_initEnv(Request& request, Location& location,Config &config) 
{
    std::map<std::string, std::string> headers = request.getheader();
	(void)config;
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
	//std::cerr<<request.getPath().substr(request.getPath().find('?')+1).c_str() << "HANAAAAAAAAAAAAAAAA\n";
	setenv("QUERY_STRING", request.getPath().substr(request.getPath().find('?')+1).c_str(),true);
	setenv("REQUEST_METHOD", request.getMethod().c_str(),true);
	setenv("SCRIPT_FILENAME",(location.getCgiPath()+"/"+location.getCgiExtension()).c_str(),true); 
	setenv("REMOTEaddr", config.getHost().c_str(),true);
	setenv("SERVER_PORT", config.getListen().c_str(),true);
	std::stringstream ss;
    ss << this->_body.length();
	setenv("CONTENT_LENGTH", ss.str().c_str(),true);
	setenv("PATH_TRANSLATED",request.getPath().c_str(),true);
}

std::string		Cgi::executeCgi(const std::string& script)
{
	pid_t		pid;
	int			saveStdin;
	int			saveStdout;
	std::string	newBody;

	if(script.find(".php") ==  std::string::npos && script.find(".py") ==  std::string::npos)
		return("404");
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
		return ("500");
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
			str[0] = strdup("python-cgi");
		str[1]= strdup(script.c_str());
		str[2] =NULL;
		//for(int i = 0; environ[i];i++)
		//	std::cout << environ[i] << std::endl; 
		execve(str[0], str, environ);
 		std::cerr << "Execve Faild." << std::endl;
		write(1, "500", 3);
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
			return("504");
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

//std::cerr<< "new=body===========.>>>>>"<< newBody <<"\n";
	return (newBody);
}
