#include "../../includes/parsing.hpp"
/*
	=========================================== canonical form  ===============================================
*/
Location::Location()
{
	_locationPath = "";
    _root = "";
    _cgiPath = "";
    _autoindex = "";
    _index = "";
    _upload = "";
	_redirect = "";
    _allowMethods.clear();
}
Location::Location(const Location& other)
{
    *this = other;
}

Location& Location::operator=(const Location& other)
{
    if (this != &other)
	{
        _locationPath = other._locationPath;
        _root = other._root;
        _cgiPath = other._cgiPath;
        _autoindex = other._autoindex;
        _index = other._index;
        _allowMethods = other._allowMethods;
        _upload = other._upload;
		_redirect = other._redirect;
    }
    return *this;
}

Location::~Location(){}
/*
	=========================================== Get && Set ===============================================
*/
std::string Location::getLocationPath() const
{
    return _locationPath;
}

void Location::setLocationPath(const std::string& locationPath) 
{
    _locationPath = locationPath;
    
}

std::string Location::getRoot() const
{
    return _root;
}

void Location::setRoot(const std::string& root)
{
    _root = root;
}

std::string Location::getCgiPath() const
{
    return _cgiPath;
}

void Location::setCgiPath(const std::string& cgiPath)
{
    _cgiPath = cgiPath;
}

std::string Location::getAutoindex() const
{
    return _autoindex;
}

void Location::setAutoindex(const std::string& autoindex)
{
    _autoindex = autoindex;
}

std::string Location::getIndex() const
{
    return _index;
}

void Location::setIndex(const std::string& index) 
{
    _index = index;
}

std::vector<std::string> Location::getAllowMethods() const 
{
    return _allowMethods;
}

void Location::setAllowMethods(const std::vector<std::string>& allowMethods)
{
    _allowMethods = allowMethods;
}

std::string Location::getUpload() const 
{
    return _upload;
}

void Location::setUpload(const std::string& upload)
{
	_upload = upload;
}

std::string Location::getRedirect() const 
{
    return _redirect;
}
void Location::setRedirect(const std::string& redirect )
{
	_redirect = redirect;
}
/*
	=========================================== member func  ===============================================
*/
void Location::readLocation(std::ifstream	&file,std::string value, std::string check, std::string line)
{
	std::string str;
	std::string tmp;
	std::string l1;
	std::string cheeck;
	while (!file.eof())
	{
		str =  removeLeadingWhitespace(line);
		std::istringstream iss(str);
		if (str == "}") 
			return ;
		iss >> tmp >> l1;
		if (str.find("#") != std::string::npos || str.find(";") != std::string::npos)
		{
			std::cerr <<  "Error : location block " << std::endl;
			exit (0);
		}
		if ((l1.empty() && l1 == "" && tmp != "root" && tmp != "cgi_path" && tmp != "autoindex" && tmp != "index" && tmp != "allow_Methods" && tmp != "upload" && tmp != "location" && tmp != "redirect"))
		{
			std::cerr <<  "Error : location block   2 " << std::endl;
			exit (0);
		}
		else if (tmp == "location")
		{
			_redirect = value;
			if (check != "{")
			{
				std::cerr <<  "Error : location block 4 " << std::endl;
				exit (0);
			}
		}
		else if (tmp == "root")
			_root = l1;
		else if (tmp == "cgi_path")
			_cgiPath = l1;
		else if (tmp == "autoindex")
			_autoindex = l1;
		else if (tmp == "index")
			_index = l1;
		else if (tmp == "allow_methods")
		{
			while (!l1.empty()) 
			{
				if (l1 != "GET" && l1 != "POST"  && l1 != "DELETE")
				{
					std::cerr << "Error: allow_method" << std::endl;
					exit(0);
				}
				_allowMethods.push_back(l1);
				l1.clear();
				iss >> l1;
			}
		}
		else if (tmp == "upload")
			_upload = l1;
		iss >>cheeck;
		if (cheeck.empty())
		{
			std::cerr << "Error: args loc" << std::endl;
			exit(0);
		}
		getline(file, line);
		l1.clear();
	}
}

std::string removeLeadingWhitespace(std::string input)
{
    size_t i = 0;
    while (i < input.length() && std::isspace(input[i])) 
        ++i;
    return input.substr(i);
}