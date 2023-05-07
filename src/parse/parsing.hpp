# ifndef PARSING_HPP
#define PARSING_HPP
#include "../../includes/Utils.hpp"
class Location
{
    private :
		std::string 				_locationPath;//done
    	std::string 				_root;//done
		std::string 				_cgiPath;//done
    	std::string 				_autoindex;//done
    	std::string 				_index;//done
		std::string					_upload;//done
		std::string 				_redirect;//done
    	std::vector<std::string> 	_allowMethods;//done
	public :
		Location(void);
		Location(const Location& other);
		Location& operator=(const Location& other);
		~Location();
		/*
			============================================================
		*/
		std::string getLocationPath() const;
		void setLocationPath(const std::string& locationPath);
		std::string getRoot() const;
		void setRoot(const std::string& root);
		std::string getCgiPath() const;
		void setCgiPath(const std::string& cgiPath);
		std::string getAutoindex() const;
		void setAutoindex(const std::string& autoindex);
		std::string getIndex() const;
		void setIndex(const std::string& index);
		std::vector<std::string> getAllowMethods() const;
		void setAllowMethods(const std::vector<std::string>& allowMethods);
		std::string getUpload() const;
		void setUpload(const std::string& upload);
		std::string getRedirect() const;
		void setRedirect(const std::string& redirect);
		/*
			============================= m func ===============================
		*/
		void readLocation(std::ifstream &file,std::string value, std::string check, std::string line);
};

class Config
{
	private :
		std::vector<std::string> 		_serverName; // to be changed to vector<string>  (multiple server name)
		std::string						_host;
		std::string						_listen;
		std::string 					_root;
		std::map<int,std::string> 		_errorPages;
		std::string						_clientMaxBodySize;
		std::string						_clientBodyTempPath;
		std::vector<Location>			_locations;
		std::map<int,std::string> 		_redirect;
		std::string						_index;
	public :
		/*
			===============================================================
		*/
		Config(void);
		Config(const Config &copy);
		Config& operator= (const Config& obj);
		~Config(void);
		/*
			===============================================================
		*/
		void setErrorPage(int code, const std::string& value);
		std::map<int,std::string> getErrorPage(void);
		void setServerName(const std::vector<std::string>& serverName);
		std::vector<std::string> getServerName(void);
		void setHost(std::string host);
		std::string getHost(void) const;
		std::string getListen(void) const;
		void setListen(std::string listen);
		std::string getRoot(void) const;
		void setRoot(std::string root);
		std::string getClientMaxBodySize(void) const;
		void setClientMaxBodySize(std::string clientsize);
		std::string getClientBodyTempPath(void) const;
		void setClientBodyTempPath(std::string clientbody);
		void setRedirect(int code, const std::string& value);
		std::map<int, std::string> getRedirect() const;
		void setIndex(const std::string& index);
		void setLocations(const std::vector<Location>& locations);
		const std::vector<Location>& getLocations() const;
		std::string getIndex() const;
		/*
			===============================================================
		*/
		void check_config(std::ifstream &file, std::string line);
		void check_servers(char *inputfile, std::vector<Config>& servers);

};
std::string removeLeadingWhitespace(std::string input);
bool isDuplicateServer(std::vector<Config>& servers, Config server);
#endif