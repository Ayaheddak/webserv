#include"cgi.hpp"

Cgi::Cgi(Request &request, config &config)
{
    _body = request.get_body;
	this->_initEnv(request, config);
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

void		Cgi::_initEnv(Request &request, config &config) 
{

	std::map<std::string, std::string>	headers = request.get_headers();
	if (headers.find("Auth-Scheme") != headers.end() && headers["Auth-Scheme"] != "")
		this->_env["AUTH_TYPE"] = headers["Authorization"];

	this->_env["REDIRECT_STATUS"] = "200"; //ela qbl secruti to execute php-cgi
	this->_env["GATEWAY_INTERFACE"] = "CGI/1.1";
	this->_env["SCRIPT_NAME"] = config.get_path(); //path dyql cgi
	this->_env["SCRIPT_FILENAME"] = config.get_path(); // same
	this->_env["REQUEST_METHOD"] = request.getMethod(); // http used    get ola post
	this->_env["CONTENT_LENGTH"] = std :: to_string(this->_body.length()); // lenght dyql body
	this->_env["CONTENT_TYPE"] = headers["Content-Type"];
	this->_env["PATH_INFO"] = request.get_path(); // path dyal request source
	this->_env["PATH_TRANSLATED"] = request.get_path(); // same
	this->_env["QUERY_STRING"] = request.get_query();
	this->_env["REMOTEaddr"] = std:: to_string(config.get_host_port().host); // ip dyal client
	this->_env["REMOTE_IDENT"] = headers["Authorization"];
	this->_env["REMOTE_USER"] = headers["Authorization"];
	this->_env["REQUEST_URI"] = request.get_path() + request.get_query();
	if (headers.find("Hostname") != headers.end())
		this->_env["SERVER_NAME"] = headers["Hostname"];
	else
		this->_env["SERVER_NAME"] = this->_env["REMOTEaddr"];
	this->_env["SERVER_PORT"] = std:: to_string(config.get_host_port().port);
	this->_env["SERVER_PROTOCOL"] = "HTTP/1.1";
	this->_env["SERVER_SOFTWARE"] = "Weebserv/1.0";

	this->_env.insert(config.get_cgi_pram().begin(), config.get_cgi_pram().end());
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
	lseek(fdIn, 0, SEEK_SET);

	pid = fork();

	if (pid == -1)
	{
		std::cerr << "Fork Faild."<< std::endl;
		return ("Status: 500\r\n\r\n");
	}
	else if (!pid)
	{
		char * const * nll = NULL;

		dup2(fdIn, 0);
		dup2(fdOut, 1);
		execve(script.c_str(), nll, env);
		std::cerr << "Execve Faild." << std::endl;
		write(1, "Status: 500\r\n\r\n", 15);
	}
	else
	{
		char	buffer[1024] = {0};

		waitpid(-1, NULL, 0);
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

	for (size_t i = 0; env[i]; i++)
		delete[] env[i];
	delete[] env;

	if (!pid)
		exit(0);

	return (newBody);
}
