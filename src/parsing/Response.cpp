#include "../../includes/Response.hpp"
#include "../../includes/Request.hpp"
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

void Response::res_location(std::vector<loc>::iterator it)
{
    respons_200(it->index);
}
void Response::check_location(pars parsing)
{
    int c = 0;
    if(r_data.getPath() != "")
    {
        std::cout <<"adadada"<< std::endl;
        std::vector<loc>::iterator it;
        for (it = parsing.s_data[0].location.begin(); it != parsing.s_data[0].location.end(); it++)
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
    respons_200(parsing.s_data[0].index);
}
void Response::respons_201(std::string index)
{
    index = "";/*
    std::ostringstream response;
    std::string line;
    if(!html_file.is_open())
    {
        std::map<std::string, std::string>  header;
        glen = 0;
        body = r_data.getBody();
        header = r_data.getheader();
        html_file.open(index.c_str(), std::ios::out | std::ios::binary);
        html_file.seekg (0, html_file.end);
        length = 
        html_file.seekg (0, html_file.beg);
    }
    if(glen < length)
    {
        len = 0;
        body.read(response_buf2, 65536);
        html_file.write(response_buf2, 65536);
        glen = length + glen;
    }
    else
    {
        response << "HTTP/1.1 201 OK\r\n";
        response << "Content-Type: text/html\r\n";
        response << "Content-Length: 9\r\n";
        response << "\r\n";
        response<< "File saved";
        std::string str = response.str();
        str.copy(response_buf2,str.length());
        response_buf2[str.length()] = '\0';
        std::cout <<"++++"<<response_buf2 <<"----" <<std::endl;
        len = strlen(response_buf2);
        c = -3;
        html_file.close();
    }
    */
}
void Response::respons_204()
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
void Response::respons_301()
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
void Response::respons_200(std::string index)
{
    std::stringstream response;
    std::string line;
    if(!html_file.is_open())
    {
        glen = 0;
        html_file.open(index.c_str(), std::ios::in | std::ios::binary);
        html_file.seekg (0, html_file.end);
        length = html_file.tellg();
        html_file.seekg (0, html_file.beg);
        response << "HTTP/1.1 200 OK\r\n";
        response << "Content-Type: "<< get_f_type(index) <<"\r\n";
        response << "Content-Length: " << length << "\r\n";
        response << "Connection: close"<< "\r\n";
        response << "\r\n";
        std::string str = response.str();
        str.copy(response_buf2,str.length());
        response_buf2[str.length()] = '\0';
        std::cout <<"++++"<<response_buf2 <<"----" <<std::endl;
        len = strlen(response_buf2);
    }
    else
    {
        html_file.read(response_buf2, 6000);
        len = html_file.gcount();
        std::cout << len << std::endl;
        glen = len + glen;
    }
}
void Response::respons(int client_sock,pars parsing)
{
    //if(count == 0)
    //    respons_405()
    len = 0;
    c = 1;
    std::cout << r_data.getPath() << std::endl;
    if(r_data.getMethod() == "GET")
        check_location(parsing);
    else if(r_data.getMethod() == "POST")
    {
        respons_201("src/parsing/index.html");
    }
    int i;
    if(len > 0 || c == -3)
    {
       i = send(client_sock, response_buf2 ,len, MSG_NOSIGNAL);
       if(i == -1 && (errno == EPIPE || errno == ECONNRESET))
       {
            c = -4;
       }
       else if(i == 0) 
          exit(0);
        else 
             c = 1;
    }
    else if(length == glen)
    {
        c = -1;
        html_file.close();
    }
}