#include <stdio.h>
#include "doublelinklist.h"

doublelinklist* createTestList(int length) {
    doublelinklist* testlist = dllcreate();
    for (size_t i = 0; i < length; i++)
    {
        testlist->addtail(testlist, i);
    }
    return testlist;
}

int main()
{
    doublelinklist* testlist = createTestList(10);
    printf("The length is %d\n", testlist->getlength(testlist));
    for (size_t i = 0; i < testlist->getlength(testlist); i++)
    {
        printf("Element %lu, value %d\n", i, testlist->get(testlist, i));
    }
    testlist->destroy(testlist);
    return 0;
}