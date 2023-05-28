/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locationconf.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 04:46:25 by aheddak           #+#    #+#             */
/*   Updated: 2023/05/27 23:32:46 by aheddak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	_redirect.clear();
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
        _upload = other._upload;
		_redirect = other._redirect;
		for (size_t i = 0; i < other._allowMethods.size(); i++)
			_allowMethods.push_back(other._allowMethods[i]);
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

const std::vector<std::string>& Location::getAllowMethods() const 
{
    return _allowMethods;
}

void Location::setAllowMethods(const std::vector<std::string> allowMethods)
{
	for (size_t i = 0; i < allowMethods.size(); i++)
		_allowMethods.push_back(allowMethods[i]);
}

std::string Location::getUpload() const 
{
    return _upload;
}

void Location::setUpload(const std::string& upload)
{
	_upload = upload;
}

void Location::setRedirect(int code, const std::string& value)
{
    _redirect[code] = value;
}

std::map<int, std::string> Location::getRedirect() const 
{
    return _redirect;
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
	_locationPath = value;
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
		if ((l1.empty() && l1 == "" )|| (tmp != "root" && tmp != "cgi_path" && tmp != "cgi_name" && tmp != "autoindex" && tmp != "index" && tmp != "allow_methods" && tmp != "upload" && tmp != "location" && tmp != "redirect"))
		{
			std::cout << "l1 " << l1 << std::endl;
			std::cout << "tmp " << tmp << std::endl;
			std::cerr <<  "Error : location block   2 " << std::endl;
			exit (0);
		}
		else if (tmp == "location")
		{
			_locationPath = value;
			if (check != "{")
			{
				std::cerr <<  "Error : location block 4 " << std::endl;
				exit (0);
			}
		}
		else if (tmp == "redirect")
		{
			std::string	statuscode;
			iss >> statuscode;
			_redirect[atoi(l1.c_str())] = statuscode;
			statuscode.clear();
		}
		else if (tmp == "root")
			_root = l1;
		else if (tmp == "cgi_path")
		{
			if (!isValidPath(l1))
			{
				std::cerr << "Error: cgi_path not valid" << std::endl;
				exit(0);
			}
			_cgiPath = l1;
		}
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
		else if (tmp == "cgi_name")
		{
			if (!isValidPath(l1))
			{
				std::cerr << "Error: cgi extension not valid" << std::endl;
				exit(0);
			}
			_cgiExtension = l1;
		}
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
std::string Location::getCgiExtension() const
{
	return _cgiExtension;
}

void Location::setCgiExtension(const std::string& cgiExtension)
{
	_cgiExtension = cgiExtension;
}

void Location::printLocation() const 
{
	std::cout << "Location Path: " << getLocationPath() << std::endl;
	std::cout << "Root: " << getRoot() << std::endl;
	std::cout << "CGI Path: " << getCgiPath() << std::endl;
	std::cout << "Autoindex: " << getAutoindex() << std::endl;
	std::cout << "Index: " << getIndex() << std::endl;
	std::cout << "Upload: " << getUpload() << std::endl;
	std::cout << "CGI Extension: " << getCgiExtension() << std::endl;
	std::cout << "Redirects:" << std::endl;
	std::map<int, std::string>::const_iterator redirectIter;
	for (redirectIter = getRedirect().begin(); redirectIter != getRedirect().end(); redirectIter++)
	{
		std::cout << "Status Code: " << redirectIter->first << " Redirect: " << redirectIter->second << std::endl;
	}
	std::cout << "Allow Methods:" << std::endl;
	for (size_t i = 0; i < getAllowMethods().size(); i++)
	{
		std::cout << "    " << getAllowMethods()[i] << std::endl;
	}
}