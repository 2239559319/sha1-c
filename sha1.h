#pragma once
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHA1CircularShift(bits, word)                                          \
    (((word) << (bits)) | ((word) >> (32 - (bits))))

#ifdef __cplusplus
extern "C"
{
#endif
    void sha1(uint8_t *, size_t, uint8_t *);
#ifdef __cplusplus
}
#endif