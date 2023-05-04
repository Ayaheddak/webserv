#include "parsing.hpp"
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

Location::~Location() {}

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

std::string Location::getRedirect() const
{
    return _redirect;
}

void Location::setRedirect(const std::string& redirect)
{
    _redirect = redirect;
}

void Location::setUpload(const std::string& upload)
{
	_upload = upload;
}

// std::string Location::get_value(const std::string& str, const std::string& key)
// {
//     std::string result;
//     if (str.find(key) == 0) // Check if key is at the beginning of str
//     {
//         std::string::size_type pos = str.find_first_not_of(" \t", key.length()); // Find the position of the first non-whitespace character after the key
//         if (pos != std::string::npos)
//         {
//             std::string::size_type end_pos = str.find_first_of("\r\n", pos); // Find the position of the end of the line
//             result = str.substr(pos, end_pos - pos); // Extract the rest of the line
//         }
//     }
//     return result;
// }

void Location::readLocation(std::string line)
{
	std::string str;
	std::string tmp;
	std::string value;
	str =  removeLeadingWhitespace(line);
	std::istringstream iss(str);
	iss >> tmp >> value;
	if (value.empty() || value == "" || tmp != "root" || tmp != "cgi_path" 
		|| tmp != "autoindex" || tmp != "index" || tmp != "allow_Methods" || tmp != "upload" || tmp != "redirect")
	{
		std::cerr <<  "Error : location block " << std::endl;
		exit (0);
	}
	if (tmp == "root")
		_root = value;
	else if (tmp == "cgi_path")
		_cgiPath = value;
	else if (tmp == "autoindex")
		_autoindex = value;
	else if (tmp == "index")
		_index = value;
	else if (tmp == "allow_Methods")
	{
		while (!value.empty()) 
		{
			if (value != "GET" && value != "POST"  && value != "DELETE")
			{
				std::cerr << "Error: allow_method" << std::endl;
				exit(0);
			}
			_allowMethods.push_back(value);
			value.clear();
			iss >> value;
		}
	}
	else if (tmp == "upload")
		_upload = value;
	else if (tmp == "redirect")
		_redirect = value;
	value.clear();
	iss >> value;
	if (!value.empty())
	{
		std::cerr << "Error: args more than 2 " << std::endl;
		exit(0);
	}
}

std::string removeLeadingWhitespace(std::string input)
{
    size_t i = 0;
    while (i < input.length() && std::isspace(input[i])) 
        ++i;
    return input.substr(i);
}