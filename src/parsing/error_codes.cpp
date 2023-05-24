/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_codes.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 05:00:59 by aainhaja          #+#    #+#             */
/*   Updated: 2023/04/15 05:21:14 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Response.hpp"

void Response::respons_404()
{
    std::stringstream response;
    response << "HTTP/1.1 404 Not Found\r\n";
    response << "Content-Type: text/html\r\n";
    response << "Content-Length: " << 0 << "\r\n";
    response << "\r\n";
    std::string str = response.str();
    str.copy(response_buf2, str.length());
    response_buf2[str.length()] = '\0';
    len = strlen(response_buf2);
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
