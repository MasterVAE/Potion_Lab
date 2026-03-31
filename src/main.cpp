#include <time.h>
#include <stdlib.h>

#include "user.h"


int main()
{
    srand((unsigned int)time(NULL));
    
    if(!Init()) return 1;
    while(Loop());

    return 0;
}