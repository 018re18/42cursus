#include <iostream>
#include <cctype>
#include <string>

int main(int ac,char *ag[])
{
    if(ac == 1)
    {
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
        return 0;
    }
    for(int i = 1; i < ac; i++)
    {
        std::string str = ag[i];
        for(size_t j = 0; j < str.size(); j++)
            std::cout << (char)std::toupper(str[j]);
    }
    std::cout << std::endl;
    return 0;
}

