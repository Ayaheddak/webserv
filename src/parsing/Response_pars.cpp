#include "../../includes/Response.hpp"
#include "../../includes/Request.hpp"
#include "../../includes/parsing.hpp"
#include "../CGI-/cgi.hpp"
#include <ftw.h>
#include <iostream>
#include <sys/stat.h>


#include <dirent.h>
#include <unistd.h>

std::string Request::handle_autoindex(const std::string& directoryPath) {
    DIR *dir;
    struct dirent *entry;
    std::string html = "<html>\n<head><title>Index of " + directoryPath + "</title></head>\n<body>\n<h1>Index of " + directoryPath + "</h1>\n<hr>\n<pre>\n";

    dir = opendir(directoryPath.c_str());
    if (!dir) {
        status_value = 500;
        return "";
    }

    while ((entry = readdir(dir)) != NULL) {
        std::string name = entry->d_name;

        // Ignore the "." and ".." directories
        if (name == "." || name == "..")
            continue;

        html += "<a href=\"" + name + "\">" + name + "</a>\n";
    }

    closedir(dir);

    html += "</pre>\n<hr>\n</body>\n</html>\n";
    return html;
}

void Request::handle_get(Config &config, Location location)
{
    (void) config;
    struct stat sb;

    size_t size = 0;
    if(location.getLocationPath() != "/")
        size = location.getLocationPath().size();
    std::string targetPath = location.getRoot() + getPath().substr(size);
    std::cout << targetPath <<std::endl;
    if (stat(targetPath.c_str(), &sb) == 0) {
        if (access(targetPath.c_str(), R_OK) != 0) {
            status_value = 403;
            return;
        }
        if (S_ISDIR(sb.st_mode)) {
            if (getPath()[getPath().size() - 1] != '/' && location.getLocationPath() != "/") {
                status_value = 301;
                fullpath = getPath() + '/';
                return;
            }
            else if (location.getAutoindex() == "on")
            {
                fullpath = targetPath;  // For auto-indexing
                a_body = handle_autoindex(targetPath);
                status_value = 1;  // For auto-indexing
                return;
            }
            else {
                fullpath = targetPath + "/" + location.getIndex();
                if (access(fullpath.c_str(), F_OK) == -1)
                    status_value = 403;  // No index file and autoindex is off
                else
                    status_value = 200;
            }
        } else {
            fullpath = targetPath;
            status_value = (access(fullpath.c_str(), F_OK) != -1) && access(targetPath.c_str(), R_OK) != 0 ? 200 : 404;
        }
    } else {
        status_value = 404;
    }
}


void Request::check_request(std::vector<Config>& parsing)
{
	(void)parsing;
    std::vector<Location> locations = _host.getLocations();
    std::vector<Location>::iterator it;
    for (it = locations.begin(); it != locations.end(); ++it) {
        Location location = *it;
        if (getPath().find(location.getLocationPath()) == 0 && location.getLocationPath() != "/")
        {
            break;
        }
    }
    if(it == locations.end())
    {
        if(locations[0].getLocationPath()== "/")
        {
            it = locations.begin();
        }
        else
            status_value = 404;
    }
    if(!it->getRedirect().empty())
    {
        if(!it->getRedirect()[301].empty())
        {
            std::cout << it->getRedirect()[301] << std::endl;
            fullpath = it->getRedirect()[301];
            status_value = 301;
            return;
        }
    }
    size_t i;
    i = 0;
    for(i = 0 ; i < it->getAllowMethods().size(); i++)
    {
        if(it->getAllowMethods()[i] == getMethod())
            break;
    }

    if(i == it->getAllowMethods().size())
        status_value = 405;
    if(status_value > 0)
        return;
    if(getMethod() == "GET")
    {
        handle_get(_host,*it);
    }
    else if(getMethod() == "POST")
    {
        handle_post(_host,*it);
    }
    else if(getMethod() == "DELETE")
    {
        handle_delete(_host,*it);
    }
}

int delete_file(const char* fpath, const struct stat* sb, int typeflag, struct FTW* ftwbuf)
{
    (void) sb;
    (void) typeflag;
    (void) ftwbuf;
     if (access(fpath, W_OK) != 0) {
        return -1;
    }
    if (remove(fpath) == 0) {
        return 0;
    } else {
        return -1;
    }
}



int delete_directory_recursive(const std::string& directoryPath)
{
    int flags = FTW_DEPTH | FTW_PHYS;
    int result = nftw(directoryPath.c_str(), delete_file, 20, flags);
    if (result == -1) {
        return 500;
    }
    return 204;
}

void Request::handle_delete(Config &config,Location location)
{
    (void) config;
    (void) location;
    struct stat sb;

    size_t size;
    if(location.getLocationPath() == "/")
        size = 0;
    else
        size = location.getLocationPath().size();
    std::string targetPath = location.getRoot() + getPath().substr(size);

if (access(targetPath.c_str(), R_OK) != 0 || access(targetPath.c_str(), W_OK) != 0) {
            std::cout << "Access denied to " << targetPath << std::endl;
            status_value = 403;
            return;
        }
    if (stat(targetPath.c_str(), &sb) == 0) {
        if (S_ISDIR(sb.st_mode)) {
            if (getPath()[getPath().size() - 1] != '/' && location.getLocationPath() != "/") {
                status_value = 409;
                return;
            }
            else {
                status_value = delete_directory_recursive(targetPath.c_str());
                std::cout << status_value << std::endl;
            }
        } else {
            fullpath = targetPath;
            if (remove(targetPath.c_str()) == 0)
                status_value =  204;
            else
                status_value =  403;
        }
    } else {
        status_value = 404;
    }
}


void Request::handle_post(Config &config,Location location) // need request hna
{
    (void) config;
    (void) location;

    // Cgi Cgi(request,config,location);
    if(!location.getUpload().empty()) // la kan fih upload sf rah good  201
    {
        status_value = 201;
        fullpath = location.getUpload() + '/';
        return;
    }
    
    struct stat sb;

    size_t size;
    if(location.getLocationPath() == "/")
        size = 0;
    else
        size = location.getLocationPath().size();
    std::string targetPath = location.getRoot() + getPath().substr(size);

    if (stat(targetPath.c_str(), &sb) == 0) {
        if (S_ISDIR(sb.st_mode)) {
            if (getPath()[getPath().size() - 1] != '/') {
                status_value = 301;
                fullpath = getPath() + '/';
                return;
            }
            else {
                fullpath = targetPath + "/" + location.getIndex();
                if (access(fullpath.c_str(), R_OK) == -1)
                    status_value = 403;
                else
                {
                    if(location.getCgiPath().empty())
                        status_value = 403;
                    else
                         status_value = 201; // hna fin dir cgi blast had status
                        //  Cgi.executeCgi(script);
                }
            }
        } else {
            fullpath = targetPath;
             if(location.getCgiPath().empty())
                status_value = 403;
            else
                 status_value = 201; // hna fin dir cgi blast had status
                //   Cgi.executeCgi(script);
        }
    } else {
        status_value = 404;
    }
}


