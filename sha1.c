#include "sha1.h"

void sha1(uint8_t *input, size_t length, uint8_t *output)
{
    size_t padding_bytes = 56 - (length % 56);
    size_t new_length = length + padding_bytes + 8;

    uint64_t length_bits = length * 8;

    uint8_t *new_arr = (uint8_t *)malloc(sizeof(uint8_t) * new_length);
    memcpy(new_arr, input, length);
    for (size_t i = length; i < length + padding_bytes; i++)
    {
        *(new_arr + i) = i == length ? 0b10000000 : 0;
    }
    for (size_t i = 0; i < 8; i++)
    {
        *(new_arr + i + padding_bytes + length) =
            (length_bits >> ((7 - i) * 8)) & 0xff;
    }

    uint32_t w[80];
    for (size_t t = 0; t < 16; t++)
    {
        w[t] = new_arr[t * 4] << 24;
        w[t] |= new_arr[t * 4 + 1] << 16;
        w[t] |= new_arr[t * 4 + 2] << 8;
        w[t] |= new_arr[t * 4 + 3];
    }
    free(new_arr);
    for (size_t t = 16; t < 80; t++)
    {
        w[t] =
            SHA1CircularShift(1, w[t - 3] ^ w[t - 8] ^ w[t - 14] ^ w[t - 16]);
    }

    const uint32_t k[] = {0x5A827999, 0x6ED9EBA1, 0x8F1BBCDC, 0xCA62C1D6};
    uint32_t h[5] = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476,
                     0xC3D2E1F0};

    for (size_t i = 0; i < new_length; i += 64)
    {
        uint32_t a = h[0], b = h[1], c = h[2], d = h[3], e = h[4];
        uint32_t temp;

        for (size_t t = 0; t < 20; t++)
        {
            temp = SHA1CircularShift(5, a) + ((b & c) | ((~b) & d)) + e + w[t] +
                   k[0];
            e = d;
            d = c;
            c = SHA1CircularShift(30, b);

            b = a;
            a = temp;
        }

        for (size_t t = 20; t < 40; t++)
        {
            temp = SHA1CircularShift(5, a) + (b ^ c ^ d) + e + w[t] + k[1];
            e = d;
            d = c;
            c = SHA1CircularShift(30, b);
            b = a;
            a = temp;
        }

        for (size_t t = 40; t < 60; t++)
        {
            temp = SHA1CircularShift(5, a) + ((b & c) | (b & d) | (c & d)) + e +
                   w[t] + k[2];
            e = d;
            d = c;
            c = SHA1CircularShift(30, b);
            b = a;
            a = temp;
        }

        for (size_t t = 60; t < 80; t++)
        {
            temp = SHA1CircularShift(5, a) + (b ^ c ^ d) + e + w[t] + k[3];
            e = d;
            d = c;
            c = SHA1CircularShift(30, b);
            b = a;
            a = temp;
        }

        h[0] += a;
        h[1] += b;
        h[2] += c;
        h[3] += d;
        h[4] += e;
    }

    for (size_t i = 0, index = 0; i < 5; i++)
    {
        output[index++] = (h[i] >> (3 * 8)) & 0xff;
        output[index++] = (h[i] >> (2 * 8)) & 0xff;
        output[index++] = (h[i] >> (1 * 8)) & 0xff;
        output[index++] = h[i] & 0xff;
    }
}
