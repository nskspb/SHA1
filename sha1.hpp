#pragma once

#include <string>
#include <iostream>

// можно использовать -exec set output-radix 16 в консоли отладки,
// чтобы в отладчике были 16-ричные значения

class SHA1
{
public:
    SHA1();
    SHA1(const std::string &s);

private:
    uint32_t digest[5];
    std::string block512;
};