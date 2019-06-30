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
    //enough space for elements at intmax and an endline
    char* output = malloc((PRINTLISTELELENGTH * list->getlength(list))+2);
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

void expect(char* testName, doublelinklist* list, char* expected) {
    printf("%s ", testName);
    char* output = printList(list);
    if (strcmp(output, expected) != 0) {
        printf("Expected %s, got %s\n", output, expected);
    }
    else
    {
        printf("\n");
    }
    free(output);
}

void testCreate() {
    doublelinklist* list = createTestList(0);
    expect("testCreate:empty", list, "\n");
    list->destroy(list);

    list = createTestList(1);
    expect("testCreate:one", list, "[0] 0 \n");
    list->destroy(list);

    list = createTestList(10);
    expect("testCreate:ten", list, "[0] 0 [1] 1 [2] 2 [3] 3 [4] 4 [5] 5 [6] 6 [7] 7 [8] 8 [9] 9 \n");
    list->destroy(list);
}

int main()
{
    testCreate();
    return 0;
}