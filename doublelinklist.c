#include <stdlib.h>
#include "doublelinklist.h"

void destroy(doublelinklist *self)
{
    node *curr = self->head;
    node *next;
    while (curr != NULL)
    {
        //iterate through all the nodes, free-ing them
        next = curr->next;
        free(curr);
        curr = next;
    }
    //finally free self
    free(self);
}

//Returns value at a specific index. Returns null if such index does not exist etc.
int get(doublelinklist *self, int index)
{
    if (index >= self->length)
        return NULL;

    if (index >= self->length / 2)
    {
        //traverse from the tail, since index is closer to tail
        int curin = self->length - 1;
        node *curr = self->tail;
        while (curr != NULL)
        {
            if (curin == index)
            {
                return curr->value;
            }
            curin--;
            curr = curr->prev;
        }
    }
    else
    {
        //traverse from the head, since index is closer to head
        int curin = 0;
        node *curr = self->head;
        while (curr != NULL)
        {
            if (curin == index)
            {
                return curr->value;
            }
            curin++;
            curr = curr->next;
        }
    }

    return NULL;
}

//Returns the first element. Equivalent to get(0)
int getfirst(doublelinklist *self)
{
    return self->get(self, 0);
}

//Returns the last element. Equivalent to get(length())
int getlast(doublelinklist *self)
{
    return self->get(self, self->length);
}

//Returns the length of the list, where 0 <= n
int getlength(doublelinklist *self)
{
    return self->length;
}

//Removes the element at the given index. Returns the element deleted, or null otherwise
int remove(doublelinklist *self, int index)
{
    //return if out of bounds
    if (index >= self->length)
        return NULL;
    if (index == 0)
    {
        //special case, head
        if (self->length == 1)
        {
            //extra special case, also tail
            free(self->head);
            self->head = NULL;
            self->tail = NULL;
            return self->length--;
        }
        //set pointers and then free
        node* temp = self->head;
        self->head = self->head->next;
        self->head->prev = NULL;
        free(temp);
        return self->length--;
    }
    if (index == self->length - 1)
    {
        //special case, tail
        if (self->length == 1)
        {
            //extra special case, also head
            free(self->head);
            self->head = NULL;
            self->tail = NULL;
            return self->length--;
        }
        //set pointers and then free
        node* temp = self->tail;
        self->tail = self->tail->prev;
        self->tail->next = NULL;
        free(temp);
        return self->length--;
    }
    if (index >= self->length / 2)
    {
        //traverse from the tail, since index is closer to tail
        int curin = self->length - 1;
        node *curr = self->tail;
        while (curr != NULL)
        {
            if (curin == index)
            {
                //found the index. Redirect pointers around
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
                free(curr);
                return self->length--;
            }
            curin--;
            curr = curr->prev;
        }
    }
    else
    {
        //traverse from the head, since index is closer to head
        int curin = 0;
        node *curr = self->head;
        while (curr != NULL)
        {
            if (curin == index)
            {
                //found the index. Redirect pointers around
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
                free(curr);
                return self->length--;
            }
            curin++;
            curr = curr->next;
        }
    }
    return NULL;
}
//Appends another list to this one, destroying the other list. Returns the length of the new list.
int append(doublelinklist *self, doublelinklist *other)
{
    if (self->length == 0)
    {
        //self is empty, so this is just a move
        self->head = other->head;
        self->tail = other->tail;
    }
    else if (other->length > 0)
    {
        //Most cases end up here. Neither lists are empty.
        self->tail->next = other->head;
        other->head->prev = self->tail;
        self->tail = other->tail;
    }
    //If the other list is empty, we do nothing to our current list
    self->length += other->length;
    free(other);
    return self->length;
}

//Returns the index of the given value. Returns the index for the first match. Returns -1 if not found.
int find(doublelinklist *self, int value)
{
    //always traverses from the head, since we don't know where value might be
    int curin = 0;
    node *curr = self->head;
    while (curr != NULL)
    {
        if (curr->value == value)
        {
            //found it!
            return curin;
        }
        //didn't find it yet
        curin++;
        curr = curr->next;
    }
    //didn't find it
    return -1;
}

//Adds the given value to the index given. Returns the new length of the list, or -1 otherwise
int add(doublelinklist *self, int index, int value)
{
    if (index < 0 || index > self->length)
    {
        //preemptively error out if out of bounds
        return -1;
    }
    //allocate the memory
    node *newnode = malloc(sizeof(node));
    //setup the new node
    newnode->value = value;

    if (index == 0)
    {
        //new head
        newnode->prev = NULL;
        newnode->next = self->head;
        if (self->head != NULL)
        {
            //set old head to point to new head
            self->head->prev = newnode;
        }
        self->head = newnode;
        if (self->length == 0)
        {
            //if only element, it is both head and tail
            self->tail = newnode;
        }
        return self->length++;
    }
    else if (index == self->length)
    {
        //new tail
        newnode->next = NULL;
        newnode->prev = self->tail;
        if (self->tail != NULL)
        {
            //set old tail to point to new tail
            self->tail->next = newnode;
        }
        self->tail = newnode;
        if (self->length == 0)
        {
            //if only element, it is both head and tail
            self->head = newnode;
        }
        return self->length++;
    }
    else
    {
        //somewhere else in the middle
        if (index >= self->length / 2)
        {
            //closer to tail
            int curin = self->length - 1;
            node *curr = self->tail;
            while (curr != NULL)
            {
                if (curin == index)
                {
                    newnode->prev = curr->prev;
                    newnode->next = curr;
                    curr->prev->next = newnode;
                    curr->prev = newnode;
                    return self->length++;
                }
                curin--;
                curr = curr->prev;
            }
        }
        else
        {
            //closer to head
            int curin = 0;
            node *curr = self->head;
            while (curr != NULL)
            {
                if (curin == index)
                {
                    newnode->prev = curr->prev;
                    newnode->next = curr;
                    curr->prev->next = newnode;
                    curr->prev = newnode;
                    return self->length++;
                }
                curin++;
                curr = curr->next;
            }
        }
    }
    return -1;
}

//Adds the given value to the end. Equivalent to add(length). Returns the new length of the list, or -1 otherwise
int addtail(doublelinklist *self, int value)
{
    return self->add(self, self->length, value);
}

doublelinklist *dllcreate()
{
    doublelinklist *result = malloc(sizeof(doublelinklist));
    if (result == NULL)
    {
        return NULL;
    }

    //set empty list
    result->length = 0;
    result->head = NULL;
    result->tail = NULL;

    //set function pointers
    result->destroy = &destroy;
    result->get = &get;
    result->getfirst = &getfirst;
    result->getlast = &getlast;
    result->getlength = &getlength;
    result->remove = &remove;
    result->append = &append;
    result->find = &find;
    result->add = &add;
    result->addtail = &addtail;
    return result;
}
