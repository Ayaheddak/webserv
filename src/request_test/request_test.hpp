# ifndef REQUEST_TEST_HPP
#define REQUEST_TEST_HPP
#include "../../includes/Utils.hpp"
class request_test
{
	private :
		std::string									_method;
		std::string 								_versionHttp;
		std::string 								_url;
		std::ifstream 								_fileTmp;
		std::string 								_request;
		std::string 								_query;//for cgi
		std::vector<std::pair<int, std::string> > 	_error;
		std::map<std::string, std::string> 			_header;

	public :
	/*
		**************************************** Canonical form ****************************************	
	*/
		request_test();
		~request_test();
		request_test(const request_test& copy);
		request_test& operator=(const request_test& copy);
	/*
		**************************************** Getters && setters ****************************************
	*/
		std::string				getMethod(void)const;
		std::string				getVersionHttp(void)const;
		std::string				getUrl(void)const;
		std::string				getQuery(void)const;
	/*
 		**************************************** m.functions ****************************************
	*/
		int 					_check;
		bool					checkFirstLine(std::string& str);
		void					parseHeader(std::string& str);
		void					addFirst(std::string& str);
};
#endif