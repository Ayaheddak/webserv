# ifndef PARSING_HPP
#define PARSING_HPP
#include "Utils.hpp"
class Location
{
    private :
		std::string 				_locationPath;//done
    	std::string 				_root;//done
		std::string 				_cgiPath;//done
		std::string 				_cgiExtension;
    	std::string 				_autoindex;//done
    	std::string 				_index;//done
		std::string					_upload;//done
		std::map<int,std::string> 		_redirect;
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
		
		std::string getAutoindex() const;
		void setAutoindex(const std::string& autoindex);
		std::string getIndex() const;
		void setIndex(const std::string& index);
		std::string getUpload() const;
		void setAllowMethods(const std::vector<std::string> allowMethods);
		void setUpload(const std::string& upload);
		void setRedirect(int code, const std::string& value);
		const std::map<int, std::string>& getRedirect() const;
		const std::vector<std::string>& getAllowMethods() const;
		std::string getCgiPath() const;
		void setCgiPath(const std::string& cgiPath);
		std::string getCgiExtension() const;
		void setCgiExtension(const std::string& cgiExtension);
		/*
			============================= m func ===============================
		*/
		void readLocation(std::ifstream &file,std::string value, std::string check, std::string line);
		void printLocation() const;
};

class Config
{
	private :
		std::string						_serverName; // to be changed to vector<string>  (multiple server name)
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
			void setServerName(std::string serverName);
			std::string getServerName(void)const;
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
			void setIndex(const std::string& index);

			//
			const std::map<int,std::string>& getErrorPage(void)const;
			const std::map<int, std::string>& getRedirect() const;
			const std::vector<Location>& getLocations()const;
			//
			std::string getIndex() const;
			void setLocations(std::vector<Location> locations);//
		/*
			===============================================================
		*/
		void check_config(std::ifstream &file, std::string line);
		void check_servers(char *inputfile, std::vector<Config>& servers);
		void printServer() const ;

};
std::string removeLeadingWhitespace(std::string input);
bool isDuplicateServer(std::vector<Config>& servers);
std::vector<Config> Servers(char *file);
bool isValidPath(const std::string& path);
#endif