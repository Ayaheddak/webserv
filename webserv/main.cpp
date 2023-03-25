#include <iostream>
#include"parsing.hpp"
void check_arguments(int argc,char **argv)
{
    if(argc > 2)
    {
        std::cerr<<"Too many arguments" << std::endl;
        exit(1);
    }
    (void)argv;
}
int main(int argc,char **argv)
{
    check_arguments(argc,argv);
    pars parsing(argv[1]);

}