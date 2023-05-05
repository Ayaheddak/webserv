#include "../../includes/parsing.hpp"

std::string get_f_type(std::string str)
{
    std::string type = str.erase(0,str.find("."));
    if (!type.empty())
	{
		if (type == ".html") return "text/html";
		else if (type == ".htm") return "text/html";
		else if (type == ".shtml") return "text/html";
		else if (type == ".css") return "text/css";
		else if (type == ".xml") return "text/xml";
		else if (type == ".csv") return "text/csv";
		else if (type == ".gif") return "image/gif";
		else if (type == ".ico") return "image/x-icon";
		else if (type == ".jpeg") return "image/jpeg";
		else if (type == ".jpg") return "image/jpeg";
		else if (type == ".js") return "application/javascript";
		else if (type == ".json") return "application/json";
		else if (type == ".png") return "image/png";
		else if (type == ".pdf") return "application/pdf";
		else if (type == ".svg") return "image/svg+xml";
		else if (type == ".txt") return "text/plain";
		else if (type == ".atom") return "application/atom+xml";
		else if (type == ".rss") return "application/rss+xml";
		else if (type == ".webp") return "image/webp";
		else if (type == ".3gpp") return	"video/3gpp";
		else if (type == ".3gp") return "video/3gpp";
		else if (type == ".ts") return "video/mp2t";
		else if (type == ".mp4") return "video/mp4";
		else if (type == ".mpeg") return "video/mpeg";
		else if (type == ".mpg") return "video/mpeg";
		else if (type == ".mov") return "video/quicktime";
		else if (type == ".webm") return "video/webm";
		else if (type == ".flv") return "video/x-flv";
		else if (type == ".m4v") return "video/x-m4v";
		else if (type == ".mng") return "video/x-mng";
		else if (type == ".asx") return "video/x-ms-asf";
		else if (type == ".asf") return "video/x-ms-asf";
		else if (type == ".wmv") return "video/x-ms-wmv";
		else if (type == ".avi") return "video/x-msvideo";
		else if (type == ".mml") return "text/mathml";
		else if (type == ".txt") return "text/plain";
		else if (type == ".jad") return "text/vnd.sun.j2me.app-descriptor";
		else if (type == ".wml") return "text/vnd.wap.wml";
		else if (type == ".htc") return "text/x-component";
		else if (type == ".png") return "image/png";
		else if (type == ".tif") return "image/tiff";
		else if (type == ".tiff") return "image/tiff";
		else if (type == ".wbmp") return "image/vnd.wap.wbmp";
		else if (type == ".ico") return "image/x-icon";
		else if (type == ".jng") return "image/x-jng";
		else if (type == ".bmp") return "image/x-ms-bmp";
		else if (type == ".svg") return "image/svg+xml";
		else if (type == ".svgz") return "image/svg+xml";
		else if (type == ".mid") return "audio/midi";
		else if (type == ".midi") return "audio/midi";
		else if (type == ".kar") return "audio/midi";
		else if (type == ".mp3") return "audio/mpeg";
		else if (type == ".ogg") return "audio/ogg";
		else if (type == ".m4a") return "audio/x-m4a";
		else if (type == ".ra"	) return "audio/x-realaudio";
		else if (type == ".pl"	) return "application/x-perl";
		else if (type == ".py"	) return "application/x-python";
		else if (type == ".php"	) return "application/x-php";
		else if (type == ".cpp"	) return "application/x-c++";
		else if (type == ".c"	) return "application/x-c";
        else if (type == "*/*"    ) return "*/*";
	}
    return "application/octet-stream";

}
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
    response << "Content-Type: "<< get_f_type(index) <<"\r\n";
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
    //if(count == 0)
    //    respons_405();
    if(r_data.getMethod() == "GET")
        check_location();
    else if(r_data.getMethod() == "POST")
        respons_201("index1.html");
    else if(r_data.getMethod() == "DELETE")
        respons_204();
    send(client_sock, response_buf1 ,strlen(response_buf1), 0);
}