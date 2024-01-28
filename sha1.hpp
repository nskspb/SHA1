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

    std::string hash();

private:
    uint32_t digest[5];
    std::string block512;
};

uint32_t K[] = {0x5a827999, 0x6ed9eba1, 0x8f1bbcdc, 0x5a827999};

const size_t number_block32 = 16; // number of 32-bit blocks in 512-bit block
const size_t number_bytes = 64;   // number of bytes in 512-bit block

void reset(uint32_t digest[], std::string &block512)
{
    digest[0] = 0x67452301;
    digest[1] = 0xefcdab89;
    digest[2] = 0x98badcfe;
    digest[3] = 0x10325476;
    digest[4] = 0xc3d2e1f0;

    block512 = "";
}

SHA1 ::SHA1()
{
    reset(digest, block512);
}

SHA1 ::SHA1(const std::string &s)
{
    SHA1();
    block512 = s;
}

uint32_t cirshleft(uint32_t value, int bits)
{
    return (value << bits) | (value >> (32 - bits));
}

void buffer_to_block(std::string &buffer, uint32_t block[number_block32])
{
    for (size_t i = 0; i < number_block32; ++i)
    {
        block[i] = (buffer[4 * i + 3] & 0xff) | (buffer[4 * i + 2] & 0xff) << 8 | (buffer[4 * i + 1] & 0xff) << 16 | (buffer[4 * i + 0] & 0xff) << 24;
    }
}

uint32_t M(uint32_t block[number_block32], const size_t i)
{
    return cirshleft(block[i - 16] ^ block[i - 14] ^ block[i - 8] ^ block[i - 3], 1);
}

// В случае, если важна экономия памяти, используем данную функцию
/*uint32_t blk(const uint32_t block[BLOCK_INTS], const size_t i)
{
    return rol(block[(i + 13) & 15] ^ block[(i + 8) & 15] ^ block[(i + 2) & 15] ^ block[i], 1);
}*/

uint32_t F0(uint32_t &b, uint32_t &c, uint32_t &d)
{
    return d ^ (b & (c ^ d));
}

uint32_t F1(uint32_t &b, uint32_t &c, uint32_t &d)
{
    return b ^ c ^ d;
}

uint32_t F2(uint32_t &b, uint32_t &c, uint32_t &d)
{
    return (b & c) | (b & d) | (c & d);
}

void Round0(uint32_t block[number_block32], uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d, uint32_t &e, size_t i)
{
    uint32_t temp = cirshleft(a, 5) + F0(b, c, d) + e + block[i] + K[0];
    e = d;
    d = c;
    c = cirshleft(b, 30);
    a = temp;
}

void Round1(uint32_t block[number_block32], uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d, uint32_t &e, size_t i)
{
    block[i] = M(block, i);
    uint32_t temp = cirshleft(a, 5) + F0(b, c, d) + e + block[i] + K[0];
    e = d;
    d = c;
    c = cirshleft(b, 30);
    a = temp;
}

void Round2(uint32_t block[number_block32], uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d, uint32_t &e, size_t i)
{
    block[i] = M(block, i);
    uint32_t temp = cirshleft(a, 5) + F1(b, c, d) + e + block[i] + K[1];
    e = d;
    d = c;
    c = cirshleft(b, 30);
    a = temp;
}

void Round3(uint32_t block[number_block32], uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d, uint32_t &e, size_t i)
{
    block[i] = M(block, i);
    uint32_t temp = cirshleft(a, 5) + F2(b, c, d) + e + block[i] + K[2];
    e = d;
    d = c;
    c = cirshleft(b, 30);
    a = temp;
}

void Round4(uint32_t block[number_block32], uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d, uint32_t &e, size_t i)
{
    block[i] = M(block, i);
    uint32_t temp = cirshleft(a, 5) + F1(b, c, d) + e + block[i] + K[3];
    e = d;
    d = c;
    c = cirshleft(b, 30);
    a = temp;
}