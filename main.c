#include <stdio.h>
#include "doublelinklist.h"

int main()
{
    doublelinklist* testlist = dllcreate();
    testlist->add(testlist, 3);
    printf("The length is %d\n", testlist->getlength(testlist));
    for (size_t i = 0; i < testlist->getlength(testlist); i++)
    {
        printf("Element %d, value %d\n", i, testlist->get(testlist, i));
    }
    testlist->destroy(testlist);
    return 0;
}