#include <stdio.h>
#include <stdlib.h>

void __assert(const char* expression, const char* funcName, const char* filename, unsigned int line)
{
    printf("Assert(%s) failed in function %s at line %u in file %s.\n",
            expression, funcName, filename, line);
    for(;;) ;
}
