/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_codes.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 05:00:59 by aainhaja          #+#    #+#             */
/*   Updated: 2023/05/27 23:24:54 by aheddak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Response.hpp"

void Response::respons_501()
{
    std::stringstream response;
    response << "HTTP/1.1 501 Not Implemented\r\n";
    response << "Content-Type: text/html\r\n";
    response << "Content-Length: " << 0 << "\r\n";
    response << "\r\n";
    std::string str = response.str();
    str.copy(response_buf2, str.length());
    response_buf2[str.length()] = '\0';
    len = strlen(response_buf2);
}
void Response::error_generetor(std::string str)
{
    std::stringstream response;
    std::string line;
    int i = 0;
    
    bool check = false;
    if (!html_file.is_open())
    {
        glen = 0;
        if (!r_data._host.getErrorPage().empty() && !r_data._host.getErrorPage()[r_data.status_value].empty()) // original
		//if (!r_data._host.getErrorPage().at(r_data.status_value).empty()) // modifier here
        {
           
            std::string index = r_data._host.getErrorPage()[r_data.status_value]; // original
			//std::string index = r_data._host.getErrorPage().at(r_data.status_value); // modifier here
            if (index[i] == '.')
            {
                while (index[i] == '.' || index[i] == '/')
                    i++;
            }
            
            index = index.substr(i);
            if (access(index.c_str(), F_OK) == 0 && access(index.c_str(), R_OK) == 0)
            {
                html_file.open(index.c_str(), std::ios::in | std::ios::binary);
                if(html_file.is_open())
                {
                    html_file.seekg(0, html_file.end);
                    length = html_file.tellg();
                    html_file.seekg(0, html_file.beg);
                    check = true;
                    response << "HTTP/1.1 " << r_data.status_value << " " << str << "\r\n";
                    response << "Content-Type: " << get_f_type(index) << "\r\n";
                    response << "Content-Length: " << length << "\r\n";
                    response << "\r\n";
                }
            }
        }
        if(check == false)
        {
            length = 0;
            response << "HTTP/1.1 " << r_data.status_value << " " << str << "\r\n";
            response << "Content-Type: text/html\r\n";
            response << "Content-Length: " << 0 << "\r\n";
            response << "\r\n";
        }
        
        std::string str = response.str();
        str.copy(response_buf2, str.length());
        response_buf2[str.length()] = '\0';
        len = strlen(response_buf2);
    }
    else
    {
        if(remaining.size() == 0)
        {
            html_file.read(response_buf2, 6000);
            len = html_file.gcount();
        }
    }
}
void Response::respons_403()
{
    std::stringstream response;
    response << "HTTP/1.1 403 Forbidden\r\n";
    response << "Content-Type: text/html\r\n";
    response << "Content-Length: " << 0 << "\r\n";
    response << "\r\n";
    std::string str = response.str();
    str.copy(response_buf2, str.length());
    response_buf2[str.length()] = '\0';
    len = strlen(response_buf2);
}
void Response::respons_400()
{
    std::stringstream response;
    response << "HTTP/1.1 400 Bad Request\r\n";
    response << "Content-Type: text/html\r\n";
    response << "Content-Length: " << 0 << "\r\n";
    response << "\r\n";
    std::string str = response.str();
    str.copy(response_buf2, str.length());
    response_buf2[str.length()] = '\0';
    len = strlen(response_buf2);
}

void Response::respons_405()
{
    std::stringstream response;
    response << "HTTP/1.1 405 Method Not Allowed\r\n";
    response << "Content-Type: text/html\r\n";
    response << "Content-Length: " << 0 << "\r\n";
    response << "\r\n";
    std::string str = response.str();
    str.copy(response_buf2, str.length());
    response_buf2[str.length()] = '\0';
    len = strlen(response_buf2);
}

void Response::respons_413()
{
    std::stringstream response;
    response << "HTTP/1.1 413 Payload Too Large\r\n";
    response << "Content-Type: text/html\r\n";
    response << "Content-Length: " << 0 << "\r\n";
    response << "\r\n";
    std::string str = response.str();
    str.copy(response_buf2, str.length());
    response_buf2[str.length()] = '\0';
    len = strlen(response_buf2);
}

void Response::respons_500()
{
    std::stringstream response;
    response << "HTTP/1.1 500 Internal Server Error\r\n";
    response << "Content-Type: text/html\r\n";
    response << "Content-Length: " << 0 << "\r\n";
    response << "\r\n";
    std::string str = response.str();
    str.copy(response_buf2, str.length());
    response_buf2[str.length()] = '\0';
    len = strlen(response_buf2);
}

void Response::respons_504()
{
    std::stringstream response;
    response << "HTTP/1.1 504 Gateway Timeout\r\n";
    response << "Content-Type: text/html\r\n";
    response << "Content-Length: " << 0 << "\r\n";
    response << "\r\n";
    std::string str = response.str();
    str.copy(response_buf2, str.length());
    response_buf2[str.length()] = '\0';
    len = strlen(response_buf2);
}
