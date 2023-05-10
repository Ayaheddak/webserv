/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_test.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:54:13 by aheddak           #+#    #+#             */
/*   Updated: 2023/05/10 17:55:31 by aheddak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	**************************************** Canonical form ****************************************	
*/
request_test::request_test()
{
	_method = "";
	_versionHttp = "";
	_url = "";
	_query = "";
	_request = "";
	_error.clear();
	_headers.clear();
	_check = 0;
}

request_test::request_test(const request_test& copy)
{
	*this = copy;
}

request_test& request_test::operator=(const request_test& copy)
{
	if (this != &copy)
	{
		_method = copy._method;
		_versionHttp = copy._versionHttp;
		_url = copy._url;
		_query = copy._query;
		_request = copy._request;
		_error = copy._error;
		_headers = copy._headers;
	}
	return (*this);
}

request_test::~request_test()
{
	_method.clear();
	_versionHttp.clear();
	_url.clear();
	_query.clear();
	_request.clear();
	_error.clear();
	_headers.clear();
}
/*
	**************************************** Getters && setters ****************************************
*/
 
std::string request_test::getMethod(void)const
{
	return (_method);
}

std::string request_test::getVersionHttp(void)const
{
	return (_versionHttp);
}

std::string request_test::getUrl(void)const
{
	return (_url);
}
/*
 **************************************** m.functions ****************************************
*/
bool request_test::checkFirstLine(std::string& str)// in err check should be change
{
	std::stringstream ss(str);
	std::string method, url, versionHttp, check;

	if (!(ss >> method >> url >> versionHttp))//400 Bad Request
	{
		_error.push_back(std::make_pair(400, "Bad Request"));
		return (false);
	}
	if (method != "GET" && method != "POST" && method != "DELETE")// 501 Not Implemented
	{
		_error.push_back(std::make_pair(501, "Not Implemented"));
		return (false);
	}
	if (url.length() > 2048)//414 Request-URI Too Long
	{
		_error.push_back(std::make_pair(414, "Request-URI Too Long"));
		return (false);
	}
	if (url.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~:/?#[]@!$&'()*+,;=") != std::string::npos)//400 Bad Request
	{
		_error.push_back(std::make_pair(400, "Bad Request"));
		return (false);
	}
	if (versionHttp != "HTTP/1.1" && versionHttp != "HTTP/1.0")//505 HTTP Version Not Supported
	{
		_error.push_back(std::make_pair(505, "HTTP Version Not Supported"));
		return (1);
	}
	_method = method;
	_versionHttp = versionHttp;
	size_t pos = url.find("?");
	if (pos != std::string::npos)
		_query = url.substr(pos + 1);
	_url = url.substr(0, pos);
	ss >> check;
	if (!check.empty())//400 Bad Request
	{
		_error.push_back(std::make_pair(400, "Bad Request"));
		return (false);
	}
	return (true);
}

void request_test::parseHeaders(const std::string& str)
{
    std::istringstream iss(str);
	size_t colon_pos;
	std::string key;
	std::string value;

	colon_pos = str.find(":");
    if (colon_pos != std::string::npos)
	{
        key = line.substr(0, colon_pos);
        value = line.substr(colon_pos + 1);
        if (!value.empty() && value[0] == ' ') 
            value.erase(0, 1);
        _header[key] = value;
    }
}

void request_test::addFirst(std::string& str)
{
	_request += str;
	if (request.find("\r\n\r\n") != std::string::npos)
	{
		_check = 1;
		_request = _request.substr(0, _request.find("\r\n\r\n"));
	}
}