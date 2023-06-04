#include "../../includes/Response.hpp"
#include "../../includes/Request.hpp"
#include "../../includes/parsing.hpp"
#include <ftw.h>
#include"../../includes/cgi.hpp"
#include <iostream>
#include <sys/stat.h>
std::string trim_leading_chars(const std::string& input, const std::string& chars) {
    size_t pos = input.find_first_not_of(chars);
    if (pos != std::string::npos)
        return input.substr(pos);
    else
        return ""; // all characters were trimmed, return an empty string
}
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
    //text/plain rah ki downloeda kolchi 
    // content lenght ki kon -1

}


void Response::check_location(std::vector<Config> &parsing)
{
    respons_200(parsing[0].getIndex());
}
void Response::respons_201(std::string index)
{       index = "";
        std::stringstream response;
        response << "HTTP/1.1 201 OK\r\n";
        response << "Content-Type: text/html; charset=UTF-8\r\n";
        response << "Content-Length: " << 9 << "\r\n";
        response << "\r\n";
        response << "File Sent";
        std::string str = response.str();
        str.copy(response_buf2, str.length());
        response_buf2[str.length()] = '\0';
        len = strlen(response_buf2);

}
void Response::respons_204()
{
    std::ostringstream response;

    response << "HTTP/1.1 204 OK\r\n";
    response << "Content-Type: text/html; charset=UTF-8\r\n";
    response << "Content-Length: " << 7 << "\r\n";
    response << "\r\n";
    response << "DELETED";
    std::string str = response.str();
    str.copy(response_buf2, str.length());
    response_buf2[str.length()] = '\0';
    len = strlen(response_buf2);

}
void Response::respons_301()
{
    std::ostringstream response;

    response << "HTTP/1.1 301 Moved Permanently\r\n";
    response << "Location: "<< r_data.fullpath <<"\r\n";
    response << "Content-Type: text/html; charset=UTF-8\r\n";
    response << "Content-Length: 0\r\n";
    response << "Connection: close\r\n";
    response << "\r\n";
    std::string str = response.str();
    str.copy(response_buf2, str.length());
    response_buf2[str.length()] = '\0';
    len = strlen(response_buf2);
}
void Response::respons_ai()
{
    if (!status)
    {
        std::stringstream response;
        length = r_data.a_body.length();

        response << "HTTP/1.1 200 OK\r\n";
        response << "Content-Type: text/html\r\n";
        response << "Content-Length: " << length << "\r\n";
        response << "\r\n";
        std::string str = response.str();
        str.copy(response_buf2, str.length());
        response_buf2[str.length()] = '\0';
        len = str.length();
        length += len;
        status = true;
        glen = 0;
    }
    else
    {
        len = std::min(r_data.a_body.length(), static_cast<size_t>(6000));
        r_data.a_body.copy(response_buf2, len);
        response_buf2[len] = '\0';
        r_data.a_body.erase(0, len);
    }
}



void Response::respons_200(std::string index)
{
    std::stringstream response;
    std::string line;
    int i = 0;

    if(!html_file.is_open())
    {
        glen = 0;
        index = trim_leading_chars(index, "./");
        index = index.substr(i);

        html_file.open(index.c_str(), std::ios::in | std::ios::binary);
        if (!html_file.is_open()) {
            r_data.status_value = 500;
            error_generetor("Internal Server Error");
            return;
        }
        html_file.seekg (0, html_file.end);
        length = html_file.tellg();
        html_file.seekg (0, html_file.beg);
        response << "HTTP/1.1 200 OK\r\n";
        response << "Content-Type: "<< get_f_type(index) <<"\r\n";
        response << "Content-Length: " << length << "\r\n";
        response << "\r\n";
        std::string str = response.str();
        str.copy(response_buf2,str.length());
        response_buf2[str.length()] = '\0';
        len = strlen(response_buf2);
        length += len;
    }
    else
    {
        html_file.read(response_buf2, 6000);
        len = html_file.gcount();
    }
}

void Response::cgi_response()
{

    if(status == false)
    {
        Cgi cgi(r_data,r_data._host,r_data._location);
        //std::cout<< "QBL++++++++++++++++++>>>> "<<r_data.cgi_body <<'\n';
        r_data.cgi_body = cgi.executeCgi(r_data._location.getCgiPath()+ "/"+ r_data._location.getCgiExtension());
        // if(r_data.cgi_body == "Timeout")
        //     error_generetor("404 Not Found"); hadi ghi testit bih 
        // hna fin t7t cgi , laknti kat9lb 3la script li 3ndk fcgi execute rah makaynch fserver aykhs nta li dbr 3Lih
        std::stringstream response;
        response << "HTTP/1.1 200 OK\r\n";
        std::string headers;
        size_t pos = r_data.cgi_body.find("\r\n\r\n");
        if (pos != std::string::npos)
        {
            headers = r_data.cgi_body.substr(0, pos + 4);  // Extract the headers
            r_data.cgi_body = r_data.cgi_body.substr(pos + 4);
            response << headers;    // Extract the body
        }
       //std::cerr << "Headers: " << headers << std::endl;
       //std::cerr << "Body: " << r_data.cgi_body << std::endl;
        // exit(0);
        std::string str = response.str();
        length = r_data.getCgibody().size() + str.size();
        str.copy(response_buf2,str.length());
        response_buf2[str.length()] = '\0';
        len = strlen(response_buf2);
        // std::cout << response_buf2<<std::endl;
        status = true;
    }
    else
    {
        len = std::min(r_data.cgi_body.length(), static_cast<size_t>(6000));
        r_data.cgi_body.copy(response_buf2, len);
        response_buf2[len] = '\0';
        r_data.cgi_body.erase(0, len);
    }
}
int Response::check_status()
{
    if(r_data.status_value == -1)
        cgi_response();
    else if(r_data.status_value == 301)
        respons_301();
    else if(r_data.status_value == 404)
       error_generetor("404 Not Found");
    else if(r_data.status_value == 501)
        error_generetor("501 Not Implemented");
    else if(r_data.status_value == 400)
    {
        error_generetor("Bad Request");
    }
    else if(r_data.status_value == 403)
        error_generetor("Forbidden");
    else if(r_data.status_value == 405)
    {
        error_generetor("Method Not Allowed");
    }
    else if(r_data.status_value == 413)
        error_generetor("413 Payload Too Large");
    else if(r_data.status_value == 500)
        error_generetor("Internal Server Error");
    else if(r_data.status_value == 409)
       error_generetor("409 Conflict");
        else if(r_data.status_value == 414)
       error_generetor("Request-URI Too Long");
    else if(r_data.status_value == 413)
       error_generetor("404 Not Found");
    else if(r_data.status_value == 1)
        respons_ai();
    else if(r_data.status_value == 204)
        respons_204();
    else
        return 0;
    return 1;
}
void Response::respons(int client_sock,std::vector<Config> &parsing)
{
    (void)parsing;
    len = 0;
    c = 1;
    if(check_status() == 1)
        c = -1;
    else if(r_data.getMethod() == "GET" && c != -4 && remaining.size() == 0)
        respons_200(r_data.fullpath);
    else if(r_data.getMethod() == "POST" && r_data.status_value == 201)
    {
        respons_201("");
    }
    int i;
    if(len > 0 || c == -3)
    {
       char buff[6000];
       if(remaining.size() > 0)
       {
            memcpy(buff,remaining.c_str(), len);
            remaining = "";
       }
       else
       {
            memcpy(buff,response_buf2, len);
       }
       i = send(client_sock, buff ,len, 0);
       if(i == -1)
       {
            c = -1;
       }
       else
       {
           if(i < len)
           {
                remaining = std::string(buff + i, len -i);
               len = len - i;
           }
           glen = i + glen;
           c = 1;
       }
    }
    if(length <= glen)
    {
        c = -1;
        html_file.close();
    }
}
