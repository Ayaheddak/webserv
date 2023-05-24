#include "../../includes/Response.hpp"
#include "../../includes/Request.hpp"
#include "../../includes/parsing.hpp"
#include <ftw.h>
#include <iostream>
#include <sys/stat.h>

void Request::handle_get(Config &config, Location location)
{
    (void) config;
    struct stat sb;

    std::string targetPath = location.getRoot() + getPath().substr(location.getLocationPath().size());

    if (stat(targetPath.c_str(), &sb) == 0) {
        if (S_ISDIR(sb.st_mode)) {
            if (getPath()[getPath().size() - 1] != '/') {
                status_value = 301;
                fullpath = getPath() + '/';
                return;
            }
            else if (location.getAutoindex() == "on")
                fullpath = targetPath;  // For auto-indexing
            else {
                fullpath = targetPath + "/" + location.getIndex();
                if (access(fullpath.c_str(), F_OK) == -1)
                    status_value = 403;  // No index file and autoindex is off
                else
                    status_value = 200;
            }
        } else {
            fullpath = targetPath;
            status_value = (access(fullpath.c_str(), F_OK) != -1) ? 200 : 404;
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
        if (getPath().find(location.getLocationPath()) != std::string::npos)
            break;
    }

    if(it == locations.end())
    {
        std::string root = _host.getRoot();
        std::string targetPath = root + getPath();
        struct stat sb;

        if (stat(targetPath.c_str(), &sb) == 0) {
        if (S_ISDIR(sb.st_mode)) {
            std::string indexPath = targetPath +'/'+ _host.getIndex();
            // std::cout << indexPath << std::endl;
            if (access(indexPath.c_str(), F_OK) != -1) {
                status_value = 200;
                fullpath = indexPath;
                // std::cout << targetPath << std::endl;
            } else {
                status_value = 404;
            }
        } else {
            if (access(targetPath.c_str(), F_OK) != -1) {
                status_value = 200;
                fullpath = targetPath;
                // << fullpath << std::endl;
            } else {
                status_value = 404;
            }
        }
        } else {
            status_value = 404;
        }
    }
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
    // std::cout << status_value << std::endl;
}

int delete_file(const char* fpath, const struct stat* sb, int typeflag, struct FTW* ftwbuf)
{
    (void) sb;
    (void) typeflag;
    (void) ftwbuf;
    if (remove(fpath) == 0) {
        std::cout << "Deleted file: " << fpath << std::endl;
        return 0;
    } else {
        std::cerr << "Failed to delete file: " << fpath << std::endl;
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

    // Delete the directory itself
    if (rmdir(directoryPath.c_str()) == 0) {
        return 204;
    } else {
        return 500;
    }
}

void Request::handle_delete(Config &config,Location location)
{
    (void) config;
    (void) location;
    struct stat sb;
    std::string targetPath;

    if(fullpath.empty())
        targetPath = location.getRoot() + getPath().substr(location.getLocationPath().size());

    else
        targetPath = fullpath;
    if (stat(targetPath.c_str(), &sb) == 0) {
        if (S_ISDIR(sb.st_mode)) {
            if (getPath()[getPath().size() - 1] != '/') {
                status_value = 409;
                return;
            }
            if(!location.getCgiPath().empty())
            {
                if(location.getIndex().empty())
                {
                    status_value = 409;
                    return;
                }
                // cgi code
            }
            else {
                status_value = delete_directory_recursive(targetPath.c_str());
            }
        } else {
            fullpath = targetPath;
             if(!location.getCgiPath().empty())
             {
                // cgi code
             }
             else
             {
                 if (remove(targetPath.c_str()) == 0)
                    status_value =  204;
                else
                    status_value =  403;     
             }
        }
    } else {
        status_value = 404;
    }
}
void Request::handle_post(Config &config,Location location)
{
    (void) config;
    (void) location;

    if(!location.getUpload().empty()) // la kan fih upload sf rah good  201
    {
        status_value = 201;
        fullpath = location.getUpload() + '/';
        return;
    }

    struct stat sb;

    std::string targetPath = location.getRoot() + getPath().substr(location.getLocationPath().size());

    if (stat(targetPath.c_str(), &sb) == 0) {
        if (S_ISDIR(sb.st_mode)) {
            if (getPath()[getPath().size() - 1] != '/') {
                status_value = 301;
                fullpath = getPath() + '/';
                return;
            }
            else {
                fullpath = targetPath + "/" + location.getIndex();
                if (access(fullpath.c_str(), F_OK) == -1)
                    status_value = 403;  // No index file and autoindex is off
                else
                {
                    if(location.getCgiPath().empty())
                        status_value = 403;
                    else
                         status_value = 201; // Cgi location
                }
            }
        } else {
            fullpath = targetPath;
             if(location.getCgiPath().empty())
                status_value = 403;
            else
                 status_value = 201;
        }
    } else {
        status_value = 404;
    }
}
