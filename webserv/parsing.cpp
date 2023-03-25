#include"parsing.hpp"

pars::pars(char *str): inputfile(str)
{
    if (!inputfile.is_open()) {
        std::cout << "Error opening file!" << std::endl;
        exit(1);
    }
    reading_file();
}
size_t pars::check_between(size_t start,size_t end)
{
    for(size_t i = start;i < end;i++)
    {
        if(f_data[i] != ' ' && f_data[i] != '\t')
        {
            std::cerr <<"error"<< std::endl;
            exit(1);
        }
    }
    return(end);
}

size_t pars::check_server_data(size_t n)
{
    data server;
    size_t i;
    if(f_data.find("server",n) != n)
    {
        std::cerr << "error server not found" << std::endl;
        exit(1);
    }
    n = n + sizeof("server") - 1;
    for(i = n;f_data[i] && f_data[i] != '}';i++)
    {
        if(f_data[i] == '#')
        {
            while(f_data[i] && f_data[i] != '\n')
                i++;
        }
        if(f_data[i] != ' ' && f_data[i] != '\0'
            && f_data[i] != '\n' && f_data[i] != '{' && f_data[i] != '\t') 
        {
            //std::cout << f_data[i] << std::endl;
            i = which_one(i,server);
        }
    }
    s_data.push_back(server);
    return(i);
}
void pars::check_syntax(size_t i)
{
    size_t a;
    size_t b;

    a = 0;
    b = 0;
    while(f_data[i])
    {
        if(f_data[i] == '#')
        {
            while(f_data[i] && f_data[i] != '\n')
                i++;
        }
        if(f_data[i] != ' ' && f_data[i] != '\0'
            && f_data[i] != '\n')
        {
            if(f_data[i] == '{')
                a++;
            if(f_data[i] == '}')
                b++;
        }
        i++;
    }
    if(a != b || a == 0)
    {
        std::cerr << "error" <<std::endl;
        exit(1);
    }
}
void pars::check_data()
{
    size_t i;

    for(i = 0; f_data[i];i++)
    {
        if(f_data[i] == '#')
        {
            while(f_data[i] && f_data[i] != '\n')
                i++;
        }
        if(f_data[i] != ' ' && f_data[i] != '\0'
            && f_data[i] != '\n')
        {
            i = check_server_data(i);
        }
    }
    //check_syntax(i);
}
void pars::reading_file()
{
    std::string line;
    while(std::getline(inputfile,line))
    {
        f_data = f_data + line + '\n';
    }
    check_data();
    inputfile.close();
}