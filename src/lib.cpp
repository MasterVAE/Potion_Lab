#include <ctype.h>

#include "lib.h"

int lstrncmp(const char* str1, const char* str2, long unsigned n)
{
    for(unsigned i = 0; i < n; i++)
    {
        if(tolower(*str1) != tolower(*str2)) return 1;
        str1++;
        str2++;
    }

    return 0;
}