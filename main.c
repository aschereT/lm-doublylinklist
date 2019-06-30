#include <stdio.h>
#include <string.h>
#include "doublelinklist.h"

//how many bytes for each element printList prints?
#define PRINTLISTELELENGTH sizeof(char) * 26
//"[2147483648] -2147483648"

doublelinklist *createTestList(int length)
{
    doublelinklist *testlist = dllcreate();
    for (size_t i = 0; i < length; i++)
    {
        testlist->addtail(testlist, i);
    }
    return testlist;
}

char *printList(doublelinklist *list)
{
    //enough space for elements at intmax and an endline
    char *output = malloc((PRINTLISTELELENGTH * list->getlength(list)) + 2);
    int offset = 0;
    for (size_t i = 0; i < list->getlength(list); i++)
    {
        offset += sprintf(output + offset, "[%lu] %d ", i, list->get(list, i));
    }
    sprintf(output + offset, "\n");
    return output;
}

void printListOut(doublelinklist *list)
{
    char *output = printList(list);
    printf("%s", output);
    free(output);
}

//compares actual list with expected list, and prints them out if they actually differ
//Format: "[%index] %value "
void expect(char *testName, doublelinklist *list, char *expected)
{
    printf("%s ", testName);
    char *output = printList(list);
    if (strcmp(output, expected) != 0)
    {
        printf("Expected %s, got %s\n", expected, output);
    }
    else
    {
        printf("OK\n");
    }
    free(output);
}

//similar to expect, but compares ints instead
void expectVal(char *testName, int output, int expected)
{
    printf("%s ", testName);
    if (output != expected)
    {
        printf("Expected %s, got %s\n", expected, output);
    }
    else
    {
        printf("OK\n");
    }
}

void testCreate()
{
    doublelinklist *list = createTestList(0);
    expect("testCreate:empty", list, "\n");
    list->destroy(list);

    list = createTestList(1);
    expect("testCreate:one", list, "[0] 0 \n");
    list->destroy(list);

    list = createTestList(10);
    expect("testCreate:ten", list, "[0] 0 [1] 1 [2] 2 [3] 3 [4] 4 [5] 5 [6] 6 [7] 7 [8] 8 [9] 9 \n");
    list->destroy(list);
}

void testDestroy()
{
    doublelinklist *list = createTestList(0);
    printf("testDestroy:empty Current pointer is %p. \n", list);
    list->destroy(list);
    //uncomment the following line to check if list is deallocated
    // printf("Destroyed, expect to get segfault when accessing list %lu\n", list->length);
}

void testFirst()
{
    doublelinklist *list = createTestList(0);
    expectVal("testFirst:empty", list->getfirst(list), NULL);
    list->add(list, 0, 0);
    expectVal("testFirst:one", list->getfirst(list), 0);
    list->add(list, 0, 5);
    expectVal("testFirst:five", list->getfirst(list), 5);
    list->destroy(list);
}

void testLast()
{
    doublelinklist *list = createTestList(0);
    expectVal("testLast:empty", list->getlast(list), NULL);
    list->add(list, 0, 0);
    expectVal("testLast:one", list->getlast(list), 0);
    list->add(list, 0, 5);
    expectVal("testLast:five", list->getlast(list), 0);
    list->destroy(list);
}

void testLength()
{
    doublelinklist *list = createTestList(0);
    expectVal("testLength:empty", list->getlength(list), 0);
    list->destroy(list);

    list = createTestList(1);
    expectVal("testLength:one", list->getlength(list), 1);
    list->destroy(list);

    list = createTestList(10);
    expectVal("testLength:ten", list->getlength(list), 10);
    list->destroy(list);

    list = createTestList(1000);
    expectVal("testLength:thousand", list->getlength(list), 1000);
    list->destroy(list);
}

void testAddTail()
{
    doublelinklist *list = createTestList(0);
    list->addtail(list, 6);
    expect("testAddTail:six", list, "[0] 6 \n");

    list->addtail(list, 486);
    expect("testAddTail:486", list, "[0] 6 [1] 486 \n");

    list->addtail(list, 99999);
    expect("testAddTail:99999", list, "[0] 6 [1] 486 [2] 99999 \n");
    list->destroy(list);
}

void testAdd()
{
    doublelinklist *list = createTestList(0);
    list->add(list, 0, 6);
    expect("testAdd:six", list, "[0] 6 \n");

    list->add(list, 0, 486);
    expect("testAdd:486", list, "[0] 486 [1] 6 \n");

    list->add(list, 2, 99999);
    expect("testAdd:99999", list, "[0] 486 [1] 6 [2] 99999 \n");
    list->destroy(list);
}

void testRemove()
{
    doublelinklist *list = createTestList(6);
    list->remove(list, 3);
    expect("testRemove:delthree", list, "[0] 0 [1] 1 [2] 2 [3] 4 [4] 5 \n");

    list->remove(list, 1);
    expect("testRemove:486", list, "[0] 0 [1] 2 [2] 4 [3] 5 \n");

    list->remove(list, 3);
    expect("testRemove:99999", list, "[0] 0 [1] 2 [2] 4 \n");
    list->destroy(list);

    //test edge cases
    list = createTestList(1);
    //test out of index
    expectVal("testRemove:outofbounds", list->remove(list, 1), NULL);
    //test removing the last element
    list->remove(list, 0);
    expect("testRemove:removelast", list, "\n");
    list->destroy(list);
}

void testAppend()
{
    doublelinklist *list1 = createTestList(0);
    doublelinklist *list2 = createTestList(0);

    list1->append(list1, list2);
    expect("testAppend:empty&empty", list1, "\n");
    list1->destroy(list1);

    list1 = createTestList(0);
    list2 = createTestList(3);
    list1->append(list1, list2);
    expect("testAppend:empty&three", list1, "[0] 0 [1] 1 [2] 2 \n");
    list1->destroy(list1);

    list1 = createTestList(4);
    list2 = createTestList(0);
    list1->append(list1, list2);
    expect("testAppend:four&empty", list1, "[0] 0 [1] 1 [2] 2 [3] 3 \n");
    list1->destroy(list1);

    list1 = createTestList(2);
    list2 = createTestList(2);
    list1->append(list1, list2);
    expect("testAppend:two&two", list1, "[0] 0 [1] 1 [2] 0 [3] 1 \n");
    list1->destroy(list1);

    list1 = createTestList(1);
    list2 = createTestList(2);
    list1->append(list1, list2);
    expect("testAppend:one&two", list1, "[0] 0 [1] 0 [2] 1 \n");
    list1->destroy(list1);

    list1 = createTestList(2);
    list2 = createTestList(1);
    list1->append(list1, list2);
    expect("testAppend:two&one", list1, "[0] 0 [1] 1 [2] 0 \n");
    list1->destroy(list1);
}

void testFind()
{
    doublelinklist *list = createTestList(10);
    expectVal("testFind:five", list->find(list, 5), 5);
    list->add(list, 7, 3);
    expectVal("testFind:threefirst", list->find(list, 3), 3);
    list->add(list, 0, 9);
    expectVal("testFind:ninefirst", list->find(list, 9), 0);
    list->destroy(list);
}

int main()
{
    testCreate();
    testDestroy();
    testFirst();
    testLast();
    testLength();
    testAddTail();
    testAdd();
    testRemove();
    testAppend();
    testFind();
    return 0;
}