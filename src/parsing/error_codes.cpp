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
    std::ostringstream response;
    response << "HTTP/1.1 404 Not Found\r\n";
    response << "Content-Type: text/html; charset=UTF-8\r\n";
    response << "Content-Length: " << 6 << "\r\n";
    response << "\r\n";
    response<<"SORRYe";
    std::string response_str = response.str();
    char* response_buf = new char[response_str.size() + 1];
    std::copy(response_str.begin(), response_str.end(), response_buf);
    response_buf[response_str.size()] = '\0';
    response_buf1 = response_buf;
}

void Response::respons_400()
{
    std::ostringstream response;
    response << "HTTP/1.1 400 Bad Request\r\n";
    response << "Content-Type: text/plain\r\n";
    response << "Content-Length: " << 13 << "\r\n";
    response << "\r\n";
    response<<"Bad Request\r\n";
    std::string response_str = response.str();
    char* response_buf = new char[response_str.size() + 1];
    std::copy(response_str.begin(), response_str.end(), response_buf);
    response_buf[response_str.size()] = '\0';
    response_buf1 = response_buf;
}
void Response::respons_403()
{
    std::ostringstream response;
    response << "HTTP/1.1 403 Forbidden\r\n";
    response << "Content-Type: text/plain\r\n";
    response << "Content-Length: " << 9 << "\r\n";
    response << "\r\n";
    response<<"Forbidden\r\n";
    std::string response_str = response.str();
    char* response_buf = new char[response_str.size() + 1];
    std::copy(response_str.begin(), response_str.end(), response_buf);
    response_buf[response_str.size()] = '\0';
    response_buf1 = response_buf;
}
void Response::respons_405()
{
    std::ostringstream response;
    response << "HTTP/1.1 405 Method Not Allowed\r\n";
    response << "Content-Type: text/plain\r\n";
    response << "Content-Length: " << 17 << "\r\n";
    response << "Allow:" <<s_data[0].allow_methods<<"\r\n";
    response << "\r\n";
    response<<"Method Not Allowed\r\n";
    std::string response_str = response.str();
    char* response_buf = new char[response_str.size() + 1];
    std::copy(response_str.begin(), response_str.end(), response_buf);
    response_buf[response_str.size()] = '\0';
    response_buf1 = response_buf;
}

void Response::respons_413()
{
    std::ostringstream response;
    response << "HTTP/1.1 413 Request Entity Too Large\r\n";
    response << "Content-Type: text/plain\r\n";
    response << "Content-Length: " << 24 << "\r\n";
    response << "\r\n";
    response <<"Request Entity Too Large\r\n";
    std::string response_str = response.str();
    char* response_buf = new char[response_str.size() + 1];
    std::copy(response_str.begin(), response_str.end(), response_buf);
    response_buf[response_str.size()] = '\0';
    response_buf1 = response_buf;
}
void Response::respons_500()
{
    std::ostringstream response;
    response << "HTTP/1.1 500 Internal Server Error\r\n";
    response << "Content-Type: text/plain\r\n";
    response << "Content-Length: " << 21 << "\r\n";
    response << "\r\n";
    response << "Internal Server Error\r\n";
    std::string response_str = response.str();
    char* response_buf = new char[response_str.size() + 1];
    std::copy(response_str.begin(), response_str.end(), response_buf);
    response_buf[response_str.size()] = '\0';
    response_buf1 = response_buf;
}
void Response::respons_504()
{
    std::ostringstream response;
    response << "HTTP/1.1 504 Gateway Timeout\r\n";
    response << "Content-Type: text/plain\r\n";
    response << "Content-Length: " << 17 << "\r\n";
    response << "\r\n";
    response << "Gateway Timeout\r\n";
    std::string response_str = response.str();
    char* response_buf = new char[response_str.size() + 1];
    std::copy(response_str.begin(), response_str.end(), response_buf);
    response_buf[response_str.size()] = '\0';
    response_buf1 = response_buf;
}