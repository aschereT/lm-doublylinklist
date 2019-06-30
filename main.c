#include <stdio.h>
#include <string.h>
#include "doublelinklist.h"

//how many bytes for each element printList prints?
#define PRINTLISTELELENGTH sizeof(char)*26
//"[2147483648] -2147483648"

doublelinklist* createTestList(int length) {
    doublelinklist* testlist = dllcreate();
    for (size_t i = 0; i < length; i++)
    {
        testlist->addtail(testlist, i);
    }
    return testlist;
}

char* printList(doublelinklist* list) {
    char* output = malloc((PRINTLISTELELENGTH * list->getlength(list))+1);
    int offset = 0;
    for (size_t i = 0; i < list->getlength(list); i++)
    {
        offset += sprintf(output+offset, "[%lu] %d ", i, list->get(list, i));
    }
    sprintf(output+offset, "\n");
    return output;
}

void printListOut(doublelinklist* list) {
    char* output = printList(list);
    printf("%s", output);
    free(output);
}

void testCreate() {
    doublelinklist* testlist = createTestList(0);

}

int main()
{
    doublelinklist* testlist = createTestList(10);
    printf("The length is %d\n", testlist->getlength(testlist));
    printListOut(testlist);
    testlist->destroy(testlist);
    return 0;
}