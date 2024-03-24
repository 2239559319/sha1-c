#include "sha1.h"
#include <string.h>

#define TO_STR(out_str, out)                                                   \
    for (size_t i = 0; i < 20; ++i)                                            \
    {                                                                          \
        sprintf(&out_str[i * 2], "%02x", out[i]);                              \
    }

#define assert(condition)                                                      \
    if (condition)                                                             \
    {                                                                          \
        printf("%s %d passed\n", __FILE__, __LINE__);                          \
    }                                                                          \
    else                                                                       \
    {                                                                          \
        fprintf(stderr, "test error %s %d\n", __FILE__, __LINE__);             \
        abort();                                                               \
    }

void test1()
{
    const char *input = "abc";
    uint8_t out[20];
    sha1(input, strlen(input), out);
    char hex_str[40];
    TO_STR(hex_str, out)
    assert(strcmp(hex_str, "a9993e364706816aba3e25717850c26c9cd0d89d") == 0)
}

void test2()
{
    const char *input = "";
    uint8_t out[20];
    sha1(input, strlen(input), out);
    char hex_str[40];
    TO_STR(hex_str, out)
    assert(strcmp(hex_str, "da39a3ee5e6b4b0d3255bfef95601890afd80709") == 0)
}

void test3()
{
    const char *input = "hello world";
    uint8_t out[20];
    sha1(input, strlen(input), out);
    char hex_str[40];
    TO_STR(hex_str, out)
    assert(strcmp(hex_str, "2aae6c35c94fcfb415dbe95f408b9ce91ee846ed") == 0)
}

void test4()
{
    const char *input = "1234567890";
    uint8_t out[20];
    sha1(input, strlen(input), out);
    char hex_str[40];
    TO_STR(hex_str, out)
    assert(strcmp(hex_str, "01b307acba4f54f55aafc33bb06bbbf6ca803e9a") == 0)
}

int main()
{
    test1();
    test2();
    test3();
    test4();
    return 0;
}
