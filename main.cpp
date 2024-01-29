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

/*Round0(block, a, b, c, d, e, 0);
    Round0(block, a, b, c, d, e, 1);
    Round0(block, a, b, c, d, e, 2);
    Round0(block, a, b, c, d, e, 3);
    Round0(block, a, b, c, d, e, 4);
    Round0(block, a, b, c, d, e, 5);
    Round0(block, a, b, c, d, e, 6);
    Round0(block, a, b, c, d, e, 7);
    Round0(block, a, b, c, d, e, 8);
    Round0(block, a, b, c, d, e, 9);
    Round0(block, a, b, c, d, e, 10);
    Round0(block, a, b, c, d, e, 11);
    Round0(block, a, b, c, d, e, 12);
    Round0(block, a, b, c, d, e, 13);
    Round0(block, a, b, c, d, e, 14);
    Round0(block, a, b, c, d, e, 15);
    Round1(block, a, b, c, d, e, 16);
    Round1(block, a, b, c, d, e, 17);
    Round1(block, a, b, c, d, e, 18);
    Round1(block, a, b, c, d, e, 19);
    Round2(block, a, b, c, d, e, 20);
    Round2(block, a, b, c, d, e, 21);
    Round2(block, a, b, c, d, e, 22);
    Round2(block, a, b, c, d, e, 23);
    Round2(block, a, b, c, d, e, 24);
    Round2(block, a, b, c, d, e, 25);
    Round2(block, a, b, c, d, e, 26);
    Round2(block, a, b, c, d, e, 27);
    Round2(block, a, b, c, d, e, 28);
    Round2(block, a, b, c, d, e, 29);
    Round2(block, a, b, c, d, e, 30);
    Round2(block, a, b, c, d, e, 31);
    Round2(block, a, b, c, d, e, 32);
    Round2(block, a, b, c, d, e, 33);
    Round2(block, a, b, c, d, e, 34);
    Round2(block, a, b, c, d, e, 35);
    Round2(block, a, b, c, d, e, 36);
    Round2(block, a, b, c, d, e, 37);
    Round2(block, a, b, c, d, e, 38);
    Round2(block, a, b, c, d, e, 39);
    Round3(block, a, b, c, d, e, 40);
    Round3(block, a, b, c, d, e, 41);
    Round3(block, a, b, c, d, e, 42);
    Round3(block, a, b, c, d, e, 43);
    Round3(block, a, b, c, d, e, 44);
    Round3(block, a, b, c, d, e, 45);
    Round3(block, a, b, c, d, e, 46);
    Round3(block, a, b, c, d, e, 47);
    Round3(block, a, b, c, d, e, 48);
    Round3(block, a, b, c, d, e, 49);
    Round3(block, a, b, c, d, e, 50);
    Round3(block, a, b, c, d, e, 51);
    Round3(block, a, b, c, d, e, 52);
    Round3(block, a, b, c, d, e, 53);
    Round3(block, a, b, c, d, e, 54);
    Round3(block, a, b, c, d, e, 55);
    Round3(block, a, b, c, d, e, 56);
    Round3(block, a, b, c, d, e, 57);
    Round3(block, a, b, c, d, e, 58);
    Round3(block, a, b, c, d, e, 59);
    Round4(block, a, b, c, d, e, 60);
    Round4(block, a, b, c, d, e, 61);
    Round4(block, a, b, c, d, e, 62);
    Round4(block, a, b, c, d, e, 63);
    Round4(block, a, b, c, d, e, 64);
    Round4(block, a, b, c, d, e, 65);
    Round4(block, a, b, c, d, e, 66);
    Round4(block, a, b, c, d, e, 67);
    Round4(block, a, b, c, d, e, 68);
    Round4(block, a, b, c, d, e, 69);
    Round4(block, a, b, c, d, e, 70);
    Round4(block, a, b, c, d, e, 71);
    Round4(block, a, b, c, d, e, 72);
    Round4(block, a, b, c, d, e, 73);
    Round4(block, a, b, c, d, e, 74);
    Round4(block, a, b, c, d, e, 75);
    Round4(block, a, b, c, d, e, 76);
    Round4(block, a, b, c, d, e, 77);
    Round4(block, a, b, c, d, e, 78);
    Round4(block, a, b, c, d, e, 79);*/

/*uint32_t a = a0;
    uint32_t b = b0;
    uint32_t c = c0;
    uint32_t d = d0;
    uint32_t e = e0;*/