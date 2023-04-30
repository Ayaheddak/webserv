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
    response << "HTTP/1.1 200 OK\r\n";
    response << "Content-Type: text/html; charset=UTF-8\r\n";
    response << "Content-Length: " << response_body.length() << "\r\n";
    response << "\r\n";
    response << response_body;
    std::string response_str = response.str();
    char* response_buf = new char[response_str.size() + 1];
    std::copy(response_str.begin(), response_str.end(), response_buf);
    response_buf[response_str.size()] = '\0';
    r_data.response_buf = response_buf;

}
void pars::res_location(std::vector<loc>::iterator it)
{
    respons_200(it->index);
}
void pars::check_location()
{
    int c = 0;
    if(!r_data.url.empty())
    {
        std::vector<loc>::iterator it;
        for (it = s_data[0].location.begin(); it != s_data[0].location.end(); it++)
        {
            std::cout << it->s_return << std::endl;
            if(it->path == r_data.url || r_data.url == it->s_return)
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
    r_data.response_buf = response_buf;

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
    r_data.response_buf = response_buf;

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
    r_data.response_buf = response_buf;

}
void pars::respons(int client_sock)
{
    if(r_data.url == s_data[0].location[0].path && !s_data[0].location[0].s_return.empty())
    {
        std::cout << "hhh" << std::endl;
        respons_301();
    }
    if(count == 0)
        respons_405();
    else if(r_data.method == "GET")
        check_location();
    else if(r_data.method == "POST")
        respons_201("index1.html");
    else if(r_data.method == "DELETE")
        respons_204();
    send(client_sock, r_data.response_buf ,strlen(r_data.response_buf), 0);
    r_data.response_buf = 0;
    r_data.url = "";
}