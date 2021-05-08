#include "tinyexpr.h"
#include <stdio.h>

int main()
{
    double answer = te_interp("3*2+4*1+(4+9)*6", 0);
    printf("Answer is %f\n", answer);
    return 0;
}