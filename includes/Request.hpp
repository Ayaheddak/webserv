# ifndef REQUEST_HPP
#define REQUEST_HPP
#include "Utils.hpp"
#include <cstdlib>
#include "parsing.hpp"
class Request
{
    public:
        int                                 k;
        std::string                         request;
        std::string                         fullpath;
        std::string                         method;
        std::string                         path;
        std::string                         version;
        std::fstream                         body;
        std::map<std::string, std::string>  header;
        bool                                read;
        bool                                status;
        size_t                              content_length;
        size_t                              len;
        int                                 status_value;
		Config                         		_host;//for matching
    public :
        Request(){ status = false; k = 1; read = false; status_value = 0;}
        void  clear();
        void request_append(const char *str,int length,size_t size,std::vector<Config>& parsing);
        void parse_header(size_t size);
        void fill_header(size_t size);
        std::map<std::string, std::string> getheader() const;
        std::string getMethod() const;
        std::string getPath() const;
        std::string getVersion() const;
        std::fstream &getBody();
        void pars_chunked_body(size_t size);
        void handle_get(Config &config, Location location);
        void check_request(std::vector<Config>& parsing);
        void handle_post(Config &config,Location location);
        void handle_delete(Config &config,Location location);
        bool getread();
        int  getk();
		// void matching(std::vector<Config> conf, std::pair<std::string, std::string> infoconfig);
		// std::vector<Config>::iterator findHostByPort(std::vector<Config>& hosts, std::pair<std::string, std::string> infoconfig);
		// std::vector<Config>::iterator findHostByName(std::vector<Config>& conf, const std::string& search);
};
#endif