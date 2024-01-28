#include <iostream>
#include <string>
#include "sha1.hpp"

int main()
{
    std::string stroka = "abc";

    SHA1 sum(stroka);

    std::cout << "SHA1 digest of:" << sum.hash() << " is: " << std::endl;
    return 0;
}