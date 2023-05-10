#include "request_test.hpp"
int main ()
{
	request_test test;
	std::string str = "GET /software/htp/cics/index.html HTTP/1.1";
	std::cout << test.checkFirstLine(str) << std::endl;

	return (0);
}