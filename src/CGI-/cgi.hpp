/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:29:18 by mrafik            #+#    #+#             */
/*   Updated: 2023/05/27 20:34:13 by mrafik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include<string>
#include<iostream>
#include<map>
#include <fcntl.h>
#include <unistd.h>
#include"../../includes/Request.hpp"
#include"../../includes/parsing.hpp"

class Cgi {
    private:
		std::vector<pid_t>					childPids;
		void								_initEnv(Request &request, Config &config ,Location &location);
		char								**_getEnvAsCstrArray() const;
		int									_getSocket(unsigned int port);
		int									_connectSocket(unsigned int port);
		std::map<std::string, std::string>	_env;
		std::string							_body;
	public:
        Cgi(void);
		Cgi(Request &request, Config &config,Location &location);
		Cgi(Cgi const &src);
		virtual ~Cgi(void);

		Cgi   	&operator=(Cgi const &src);
		void executeMultipleCgis(const std::vector<std::string>& scripts);
		std::string		executeCgi(const std::string &scriptName);
};
