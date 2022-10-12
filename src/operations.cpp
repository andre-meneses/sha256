#include "../include/operations.hpp"
#include <iostream>
#include <math.h>
#include <stdint.h>   // for uint32_t
#define INT_BITS 32

uint32_t sum(uint32_t a, uint32_t b)
{
    uint32_t s = a + b;
    long int m = 4294967296;
    return s % m;
}

uint32_t right_rotate(uint32_t n,  unsigned int d)
{
    return (n >> d)|(n << (INT_BITS - d));
}

uint32_t ch(uint32_t x, uint32_t y, uint32_t z)
{
    uint32_t not_x = ~x;
    return (x & y) ^ (not_x & z);
}

uint32_t maj(uint32_t x, uint32_t y, uint32_t z)
{
    return (x & y) ^ (x & z) ^ (y & z);
}

uint32_t sigmazao_0(uint32_t x)
{
    uint32_t a = right_rotate(x,2);
    uint32_t b = right_rotate(x,13);
    uint32_t c = right_rotate(x,22);

    return a ^ b ^ c;
}

uint32_t sigmazao_1(uint32_t x)
{
    uint32_t a = right_rotate(x,6);
    uint32_t b = right_rotate(x,11);
    uint32_t c = right_rotate(x,25);

    return a ^ b ^ c;
}

uint32_t sigma_0(uint32_t x)
{
    uint32_t a = right_rotate(x,7);
    uint32_t b = right_rotate(x,18);
    uint32_t c = x >> 3;

    return a ^ b ^ c;
}

uint32_t sigma_1(uint32_t x)
{
    uint32_t a = right_rotate(x,17);
    uint32_t b = right_rotate(x,19);
    uint32_t c = x >> 10;

    return a ^ b ^ c;
}
