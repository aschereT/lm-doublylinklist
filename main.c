#include <stdio.h>
#include "doublelinklist.h"

int main()
{
    doublelinklist* testlist = dllcreate();
    printf("The length is %d\n", testlist->getlength(testlist));
    return 0;
}