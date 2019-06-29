#include <stdlib.h>
#include "doublelinklist.h"

void destroy(doublelinklist* self) {
    node* curr = self->head;
    while(curr != NULL) {
        curr = curr->next;
        free(curr);
    }
    free(self);
}

//Returns value at a specific index. Returns null if such index does not exist etc.
int get(doublelinklist* self, int index){
    if (index >= self->length) return NULL;

    //TODO: iterate from rear if index >= length/2
    int curin = 0;
    node* curr = self->head;
    while(curr != NULL) {
        if(curin != index) {
            curin++;
            curr = curr->next;
        }
        return curr->value;
    }
}

//Returns the first element. Equivalent to get(0)
int getfirst(doublelinklist* self){
    self->get(self, 0);
}

//Returns the last element. Equivalent to get(length())
int getlast(doublelinklist* self){
    self->get(self, self->length);
}

//Returns the length of the list, where 0 <= n
int getlength(doublelinklist* self){
    return self->length;
}

//Removes the element at the given index. Returns the element deleted, or null otherwise
int remove(doublelinklist* self, int index){
    return NULL;
}
//Appends another list to this one. Returns the length of the new list.
int append(doublelinklist* self, doublelinklist* other){
    return NULL;
}
//Returns the index of the given value. Returns -1 if not found.
int find(doublelinklist* self, int value){
    return NULL;
}

//Adds the given value to the end of the list. Returns the new length of the list.
int add(doublelinklist* self, int value){
    return NULL;
}

doublelinklist* dllcreate() {
    doublelinklist* result = malloc(sizeof(doublelinklist));
    if (result == NULL) {
        return NULL;
    }

    result->length = 0;
    result->get = &get;
    return result;
}
