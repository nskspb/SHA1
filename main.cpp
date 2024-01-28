#include <iostream>
#include <string>
#include "sha1.hpp"

int main()
{
    std::string stroka = "abc";

    SHA1 sum(stroka);

    std::cout << "SHA1 digest of:" << stroka << " is: " << std::endl;
    return 0;
}