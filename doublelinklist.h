#ifndef doublelinklisth
#define doublelinklisth

typedef struct node {
    int value;
    struct node* next;
    struct node* prev;
} node;

typedef struct doublelinklist {
    node* head;
    node* tail;
    int length;

    //Destroys the double linked list
    void (*destroy)(void* self);
    //Returns value at a specific index. Returns null if such index does not exist etc.
    int (*get)(void* self, int index);
    //Returns the first element. Equivalent to get(0)
    int (*getfirst)(void* self);
    //Returns the last element. Equivalent to get(length())
    int (*getlast)(void* self);
    //Returns the length of the list, where 0 <= n
    int (*getlength)(void* self);
    //Removes the element at the given index. Returns the element deleted, or null otherwise
    int (*remove)(void* self, int index);
    //Appends another list to this one. Returns the length of the new list.
    int (*append)(void* self, void* other);
    //Returns the index of the given value. Returns -1 if not found.
    int (*find)(void* self, int value);
    //Adds the given value to the index given. Returns the new length of the list, or -1 otherwise
    int (*add)(void* self, int index, int value);
    //Adds the given value to the end. Equivalent to add(length). Returns the new length of the list, or -1 otherwise
    int (*addtail)(void* self, int value);
} doublelinklist;

//Creates a new double linked list
doublelinklist* dllcreate();
#endif