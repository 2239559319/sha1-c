# c-sha1

sha1 implement by c language. a light, simple sha1 library

## usage

```c
#include "sha1.h"
#include <string.h>

int main()
{
    const char* input = "abc";
    uint_8 output[20];

    sha1(input, strlen(input), output);

    return 0;
}

```
