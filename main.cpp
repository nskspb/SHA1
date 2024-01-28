#include <iostream>
#include "sha1.hpp"

int main()
{
    const char *stroka = "abc";

    std::cout << "SHA1 digest of:" << stroka << " is: " << std::endl;
    return 0;
}