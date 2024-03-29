#pragma once

#include <string>
#include <iostream>
#include <iomanip>
#include <vector>

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
    std::string buffer;
    std::vector<uint32_t> M_blocks;
};

uint32_t K[] = {0x5a827999, 0x6ed9eba1, 0x8f1bbcdc, 0xca62c1d6};

const size_t number_block32 = 16; // number of 32-bit blocks in 512-bit block
const size_t number_bytes = 64;   // number of bytes in 512-bit block

void reset(uint32_t digest[], std::string &buffer)
{
    digest[0] = 0x67452301;
    digest[1] = 0xefcdab89;
    digest[2] = 0x98badcfe;
    digest[3] = 0x10325476;
    digest[4] = 0xc3d2e1f0;

    buffer = "";
}

SHA1 ::SHA1()
{
    reset(digest, buffer);
}

SHA1 ::SHA1(const std::string &s)
{
    reset(digest, buffer);
    buffer = s;
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

std::vector<uint32_t> M(uint32_t block[number_block32])
{
    std::vector<uint32_t> M_blocks;
    M_blocks.resize(80);

    for (size_t i = 0; i < 16; ++i)
    {
        M_blocks[i] = block[i];
    }

    for (size_t i = 16; i < 80; ++i)
    {
        M_blocks[i] = cirshleft(M_blocks[i - 16] ^ M_blocks[i - 14] ^ M_blocks[i - 8] ^ M_blocks[i - 3], 1);
    }
    return M_blocks;
}

// В случае, если важна экономия памяти, используем данную функцию
/*uint32_t M(uint32_t block[number_block32], const size_t i)
{
    return cirshleft(block[(i + 13) & 15] ^ block[(i + 8) & 15] ^ block[(i + 2) & 15] ^ block[i], 1);
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

void Round0(std::vector<uint32_t> M_blocks, uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d, uint32_t &e, size_t i)
{
    uint32_t temp = cirshleft(a, 5) + F0(b, c, d) + e + M_blocks[i] + K[0];
    e = d;
    d = c;
    c = cirshleft(b, 30);
    b = a;
    a = temp;
}

void Round1(std::vector<uint32_t> M_blocks, uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d, uint32_t &e, size_t i)
{
    uint32_t temp = cirshleft(a, 5) + F1(b, c, d) + e + M_blocks[i] + K[1];
    e = d;
    d = c;
    c = cirshleft(b, 30);
    b = a;
    a = temp;
}

void Round2(std::vector<uint32_t> M_blocks, uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d, uint32_t &e, size_t i)
{
    uint32_t temp = cirshleft(a, 5) + F2(b, c, d) + e + M_blocks[i] + K[2];
    e = d;
    d = c;
    c = cirshleft(b, 30);
    b = a;
    a = temp;
}

void Round3(std::vector<uint32_t> M_blocks, uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d, uint32_t &e, size_t i)
{
    uint32_t temp = cirshleft(a, 5) + F1(b, c, d) + e + M_blocks[i] + K[3];
    e = d;
    d = c;
    c = cirshleft(b, 30);
    b = a;
    a = temp;
}

void Rounds(uint32_t digest[], std::vector<uint32_t> M_blocks)
{
    // 80 rounds of algorithm
    uint32_t a0 = digest[0];
    uint32_t b0 = digest[1];
    uint32_t c0 = digest[2];
    uint32_t d0 = digest[3];
    uint32_t e0 = digest[4];

    uint32_t a = a0;
    uint32_t b = b0;
    uint32_t c = c0;
    uint32_t d = d0;
    uint32_t e = e0;

    for (size_t i = 0; i <= 19; ++i)
    {
        Round0(M_blocks, a, b, c, d, e, i);
    }

    for (size_t i = 20; i <= 39; ++i)
    {
        Round1(M_blocks, a, b, c, d, e, i);
    }

    for (size_t i = 40; i <= 59; ++i)
    {
        Round2(M_blocks, a, b, c, d, e, i);
    }

    for (size_t i = 60; i <= 79; ++i)
    {
        Round3(M_blocks, a, b, c, d, e, i);
    }

    digest[0] = a + a0;
    digest[1] = b + b0;
    digest[2] = c + c0;
    digest[3] = d + d0;
    digest[4] = e + e0;
}

std::string SHA1 ::hash()
{
    uint64_t message_length = buffer.size() * 8;

    // buffer initialization
    buffer += (char)0x80;
    while (buffer.size() != number_bytes)
    {
        buffer += (char)0x00;
    }

    uint32_t block[number_block32];
    buffer_to_block(buffer, block);
    block[number_block32 - 1] = (uint32_t)(message_length);

    M_blocks.resize(80);
    M_blocks = M(block);

    Rounds(digest, M_blocks);
    std::ostringstream result;

    result << std::setfill('0') << std::setw(8) << std::hex;
    result << digest[0] << digest[1] << digest[2] << digest[3] << digest[4] << '\n';
    return result.str();
}