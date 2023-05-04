# ifndef PARSING_HPP
#define PARSING_HPP
#include "../includes/Utils.hpp"

class Location
{
    private :
		std::string 				_locationPath;
    	std::string 				_root;
		std::string 				_cgiPath;//
    	std::string 				_autoindex;
    	std::string 				_index;
    	std::vector<std::string> 	_allowMethods;
		std::string					_upload;
		std::string					_redirect;
	public :
		Location(void);
		Location(const Location& other);
		Location& operator=(const Location& other);
		~Location();
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
		void readLocation(std::string line);
		// bool isKeyValid(std::string str);
		// std::string get_value(const std::string& str, const std::string& key);
};

class Config
{
	private :
		std::string 					_serverName;
		std::string						_listen;
		std::string 					_root;
		std::map<int,std::string> 		_errorPages;
		std::string						_clientMaxBodySize;
		std::string						_clientBodyTempPath;
		std::vector<Location>			_locations;
	public :
		Config(void);
		Config(const Config &copy);
		Config& operator= (const Config& obj);
		~Config(void);
		void	check_config(char *file);
		std::string	getServerName(void)const;
		std::string getListen(void)const;
		std::string getRoot(void)const;
		std::string	getClientMaxBodySize(void)const;
		std::string	getClientBodyTempPath(void)const;
		std::vector<Location>	getLocations(void)const;


};
std::string removeLeadingWhitespace(std::string input);
#endif