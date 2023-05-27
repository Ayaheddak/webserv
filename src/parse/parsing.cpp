/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 04:46:14 by aheddak           #+#    #+#             */
/*   Updated: 2023/05/26 22:24:50 by aheddak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.hpp"
/*
	===================================================================================================
*/

Config::Config(void)
{
	_serverName.clear();
	_host = "";
	_listen="";
	_root="";
	_errorPages.clear();
	_clientMaxBodySize = "";
	_clientBodyTempPath = "";
	_locations.clear();
	_redirect.clear();
	_index = "";
}

Config::Config(const Config &copy) 
{
    *this = copy;
}

Config& Config::operator= (const Config& obj) 
{
    if (this != &obj)
	{
    	_serverName = obj._serverName;
		_host = obj._host;
    	_listen = obj._listen;
    	_root = obj._root;
    	_errorPages = obj._errorPages;
    	_clientMaxBodySize = obj._clientMaxBodySize;
    	_clientBodyTempPath = obj._clientBodyTempPath;
		_redirect = obj._redirect;
		_index = obj._index;
		for (size_t i = 0; i < obj._locations.size(); i++)
			_locations.push_back(obj._locations[i]);
    }
    return (*this);
}

Config::~Config(void){}
/*
	===================================================================================================
*/
std::string Config::getListen(void) const
{
	return (this->_listen);
}

void Config::setListen(std::string listen)
{
	_listen = listen;
}

void Config::setHost(std::string host)
{
	_host = host;
}

std::string Config::getHost(void) const
{
	return (_host);
}

void Config::setRoot(std::string root)
{
	_root = root;
}

std::string Config::getRoot(void) const
{
	return (_root);
}

std::string Config::getClientMaxBodySize(void) const
{
	return (this->_clientMaxBodySize);
}

void Config::setClientMaxBodySize(std::string clientsize) 
{
	_clientMaxBodySize = clientsize;
}

std::string Config::getClientBodyTempPath(void) const
{
	return (this->_clientBodyTempPath);
}

void Config::setClientBodyTempPath(std::string clientbody)
{
	_clientBodyTempPath = clientbody;
}

std::string Config::getIndex() const
{
    return _index;
}

void Config::setIndex(const std::string& index) 
{
    _index = index;
}

void Config::setRedirect(int code, const std::string& value)
{
    _redirect[code] = value;
}

std::map<int, std::string> Config::getRedirect() const 
{
    return _redirect;
}

void Config::setErrorPage(int code, const std::string& value)
{
    _errorPages[code] = value;
}

void Config::setServerName(std::string serverName)
{
    _serverName = serverName;
}

std::map<int,std::string> Config::getErrorPage(void)
{
    return (_errorPages);
}

std::string Config::getServerName(void)
{
    return (_serverName);
}

std::vector<Location>& Config::getLocations() 
{
    return _locations;
}
void Config::setLocations(std::vector<Location> locations) 
{
    _locations = locations;
}

/*
	===================================================================================================
*/

void Config::check_config(std::ifstream &file, std::string line)
{
	std::string str;
	while (!file.eof())
	{
		str = removeLeadingWhitespace(line);
		if (str.find("#") != std::string::npos || str.find(";") != std::string::npos)
		{
			std::cerr << "Error: invalid character in the file" << std::endl;
			return ;
		}
		std::istringstream 	iss(str);
		std::string 		tmp;
		std::string 		value;
		std::string 		check;
		iss >> tmp >> value;
		if (tmp == "}")
			return ;
		if (tmp == "{")
		{
			getline(file, line);
			continue;
		}
		if ((value.empty() && value == "") || (tmp != "root" && tmp != "server_name" && tmp != "listen" && 
			tmp != "index" && tmp != "error_page" && tmp != "client_max_body_size" && tmp != "client_body_temp_path" && tmp != "location" && tmp != "redirect" && tmp != "{" && tmp != "host"))
		{
			std::cerr <<  "Error : in server sad" << std::endl;
			exit (0);
		}
		if (tmp == "server_name")
			_serverName = value;
		else if (tmp == "listen")
			_listen = value;
		else if (tmp == "host")
		{
			if (value == "localhost")
				value = "127.0.0.1";
			_host = value;
		}
		else if (tmp == "root")
			_root = value;
		else if (tmp == "error_page")
		{
			int keeey;
			keeey = atoi(value.c_str());
			std::string	code;
			iss >> code;
			if (iss.fail() && iss.bad() && keeey < 300 && keeey > 599)
			{
				std::cerr << "Error in error Pages directive "<< std::endl;
				exit(0);
			}
			_errorPages[keeey] = code;
		}
		else if (tmp == "redirect")
		{
			
			std::string	statuscode;
			iss >> statuscode;
			_redirect[atoi(value.c_str())] = statuscode;
			statuscode.clear();
		}
		else if (tmp == "client_max_body_size")
			_clientMaxBodySize = value;
		else if (tmp == "client_body_temp_path")
			_clientBodyTempPath = value;
		else if (tmp == "index")
			_index = value;
		else if (tmp == "location")
        {
            Location loc;
            // std::vector<std::string> locMethods;
            iss >> check;
            loc.readLocation(file,value, check, str);
            if (loc.getIndex().empty())
            {
                if (!getIndex().empty())
                    loc.setIndex(getIndex());
                else 
                {
                    std::cerr << "Error : no index !!!" << std::endl;
                    exit(0);
                }
            }
			if (loc.getAllowMethods().empty())
			{
				std::cerr << "Error : no allowed methods in loc block!!!" << std::endl;
                exit(0);
			}
            // for(size_t i = 0 ; i < loc.getAllowMethods().size(); i++)
            //     locMethods.push_back(loc.getAllowMethods()[i]);
            _locations.push_back(loc);
            // _locations.back().setAllowMethods(locMethods);
            // locMethods.clear();
            check.clear();
        }
		iss >> check;
		if (!check.empty())
		{
			std::cerr << "Error : args more than twoooooo" << std::endl;
			exit(0);
		}
		getline(file, line);
		value.clear();
	}
}
void Config::printServer() const 
{
    std::cout << "Server Name: " << _serverName << std::endl;
    std::cout << "Host: " << _host << std::endl;
    std::cout << "Listen: " << _listen << std::endl;
    std::cout << "Root: " << _root << std::endl;

    std::cout << "Error Pages:" << std::endl;
    std::map<int, std::string>::const_iterator errorIter;
    for (errorIter = _errorPages.begin(); errorIter != _errorPages.end(); ++errorIter) 
	{
        std::cout << "    Error " << errorIter->first << ": " << errorIter->second << std::endl;
    }

    std::cout << "Client Max Body Size: " << _clientMaxBodySize << std::endl;
    std::cout << "Client Body Temp Path: " << _clientBodyTempPath << std::endl;

    std::cout << "Redirects:" << std::endl;
    std::map<int, std::string>::const_iterator redirectIter;
    for (redirectIter = _redirect.begin(); redirectIter != _redirect.end(); ++redirectIter) 
	{
        std::cout << "redirect " << redirectIter->first << ": " << redirectIter->second << std::endl;
    }
    std::cout << "Index: " << _index << std::endl;
	std::cout << "Locations: " << std::endl;
	for (size_t i = 0; i < _locations.size(); i++)
	{
		_locations[i].printLocation();
	}
}