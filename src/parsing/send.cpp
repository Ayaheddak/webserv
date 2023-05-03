#include "../../includes/parsing.hpp"

void pars::respons_200(std::string index)
{
    std::ifstream html_file;
    std::ostringstream response;
    std::string response_body;
    std::string line;

    html_file.open(index.c_str());
    while (getline(html_file, line))
    {
        response_body += line + "\n";
    }
    std::cout << index.c_str() << std::endl;
    response << "HTTP/1.1 200 OK\r\n";
    response << "Content-Type: "<< r_data.gettype() <<"\r\n";
    response << "Content-Length: " << response_body.length() << "\r\n";
    response << "\r\n";
    response << response_body;
    std::string response_str = response.str();
    char* response_buf = new char[response_str.size() + 1];
    std::copy(response_str.begin(), response_str.end(), response_buf);
    response_buf[response_str.size()] = '\0';
    response_buf1 = response_buf;

}
void pars::res_location(std::vector<loc>::iterator it)
{
    respons_200(it->index);
}
void pars::check_location()
{
    int c = 0;
    if(r_data.getPath() != "")
    {
        std::vector<loc>::iterator it;
        for (it = s_data[0].location.begin(); it != s_data[0].location.end(); it++)
        {
            std::cout << it->s_return << std::endl;
            if(it->path == r_data.getPath() || r_data.getPath() == it->s_return)
            {
                c = 1;
                break;
            }
        }
        if(c == 0)
        {
            respons_404();
            return;
        }
        respons_200(it->index);
        return;
    }
     respons_200(s_data[0].index);
}
void pars::respons_201(std::string index)
{
    std::ifstream html_file;
    std::ostringstream response;
    std::string response_body;
    std::string line;

    html_file.open(index.c_str());
    while (getline(html_file, line))
    {
        response_body += line + "\n";
    }
    response << "HTTP/1.1 201 OK\r\n";
    response << "Content-Type: text/html; charset=UTF-8\r\n";
    response << "Content-Length: " << response_body.length() << "\r\n";
    response << "\r\n";
    response << response_body;
    std::string response_str = response.str();
    char* response_buf = new char[response_str.size() + 1];
    std::copy(response_str.begin(), response_str.end(), response_buf);
    response_buf[response_str.size()] = '\0';
    response_buf1 = response_buf;

}
void pars::respons_204()
{
    std::ostringstream response;

    response << "HTTP/1.1 204 OK\r\n";
    response << "Content-Type: text/html; charset=UTF-8\r\n";
    response << "Content-Length: " << 7 << "\r\n";
    response << "\r\n";
    response << "DELETED";
    std::string response_str = response.str();
    char* response_buf = new char[response_str.size() + 1];
    std::copy(response_str.begin(), response_str.end(), response_buf);
    response_buf[response_str.size()] = '\0';
    response_buf1 = response_buf;

}
void pars::respons_301()
{
    std::ostringstream response;

    response << "HTTP/1.1 301 Moved Permanently\r\n";
    response << "Location: " << s_data[0].location[0].s_return << "\r\n";
    response << "Content-Type: text/html; charset=UTF-8\r\n";
    response << "Content-Length: 0\r\n";
    response << "Connection: close\r\n";
    response << "\r\n";
    std::string response_str = response.str();
    char* response_buf = new char[response_str.size() + 1];
    std::copy(response_str.begin(), response_str.end(), response_buf);
    response_buf[response_str.size()] = '\0';
    response_buf1 = response_buf;

}
void pars::respons(int client_sock)
{
    if(r_data.getPath() == s_data[0].location[0].path && !s_data[0].location[0].s_return.empty())
    {
        respons_301();
    }
    if(count == 0)
        respons_405();
    else if(r_data.getMethod() == "GET")
        check_location();
    else if(r_data.getMethod() == "POST")
        respons_201("index1.html");
    else if(r_data.getMethod() == "DELETE")
        respons_204();
    send(client_sock, response_buf1 ,strlen(response_buf1), 0);
    response_buf1 = 0;

}