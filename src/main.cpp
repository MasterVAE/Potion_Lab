
#include "user.h"


int main()
{
    if(!Init()) return 1;
    while(Loop());

    return 0;
}