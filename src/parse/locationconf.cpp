/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locationconf.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 04:46:25 by aheddak           #+#    #+#             */
/*   Updated: 2023/05/26 23:31:42 by aheddak          ###   ########.fr       */
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

std::vector<std::string> Location::getAllowMethods() const 
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
		if ((l1.empty() && l1 == "" && tmp != "root" && tmp != "cgi_path" && tmp != "autoindex" && tmp != "index" && tmp != "allow_Methods" && tmp != "upload" && tmp != "location" && tmp != "redirect"))
		{
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

void Location::printLocation() const 
{
    std::cout << "Location Path: " << _locationPath << std::endl;
    std::cout << "Root: " << _root << std::endl;
    std::cout << "CGI Path: " << _cgiPath << std::endl;
    std::cout << "Autoindex: " << _autoindex << std::endl;
    std::cout << "Index: " << _index << std::endl;
    std::cout << "Upload: " << _upload << std::endl;

    std::cout << "Redirects:" << std::endl;
    std::map<int, std::string>::const_iterator redirectIter;
    for (redirectIter = _redirect.begin(); redirectIter != _redirect.end(); redirectIter++) {
        std::cout << "    Code " << redirectIter->first << ": " << redirectIter->second << std::endl;
    }
	// if(_redirect.find(301) != _redirect.end())
	// 	exit(0);
    std::cout << "Allowed Methods:" << std::endl;
	// std::cout << "size = " << _allowMethods.size() << std::endl;
	for (size_t i = 0; i < _allowMethods.size(); i++)
		std::cout << "    " << _allowMethods[i] << std::endl;
    // for (std::vector<std::string>::const_iterator methodIter = _allowMethods.begin(); methodIter < _allowMethods.end(); methodIter++) 
	// {
    //     std::cout << "    " << *methodIter << std::endl;
    // }
}
