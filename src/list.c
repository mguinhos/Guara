#include <string.h>

#include "guara/tracer.h"
#include "guara/list.h"

typedef struct listnode
{
    Object* item;
    
    struct listnode* previous;
    struct listnode* next;
}
Node;

Object ListIterator;

Object* ListIterator__iter__(Object* self)
{
    if (type(self) == &ListIterator)
        return self;

    Object* listiterator_instance = new(&ListIterator);

    listiterator_instance->raw_data = self->raw_data;

    return listiterator_instance;
}

Object* ListIterator__next__(Object* self)
{
    Node* node = (Node*) self->raw_data;
    Object* item = &None;

    if (node->item != NULL)
        item = node->item;

    if (node->next == NULL)
        goto stopiteration;
    
    self->raw_data = node->next;

    return item;

stopiteration:
    throw(stopiteration_new(NULL));
    return item;
}

Object ListIterator = {
    &Type,

    "list_iterator",
    
    NULL,
    NULL,

    NULL,
    NULL,

    NULL,
    NULL,

    ListIterator__iter__,
    ListIterator__next__
};


// possible unsafe
// note: fix it
char* List__repr__(Object* self)
{
    size_t buffer_length = 2;

    Object* iterator = &None;
    Object* item = &None;

    for (iterator = iter(self); ; )
    {
        item = next(iterator);

        if (catch(&StopIteration) != &None)
            break;

        buffer_length += strlen(repr(item));
        buffer_length += 2;
    }

    if (buffer_length == 2)
        return "[]";

    char* buffer = malloc(buffer_length +1);

    buffer[0] = '[';

    if (buffer == NULL)
        return "(List__repr__)";
    
    buffer_length = 1;

    for (iterator = iter(self); ; )
    {
        item = next(iterator);

        strcpy(buffer + buffer_length, repr(item));
        buffer_length += strlen(repr(item));

        if (catch(&StopIteration) != &None)
            break;

        buffer[buffer_length++] = ',';
        buffer[buffer_length++] = ' ';
    }

    buffer[buffer_length++] = ']';
    buffer[buffer_length] = '\0';

    return buffer;
}

Object List = {
    &Type,

    "list",
    
    NULL,
    NULL,

    List__repr__,
    NULL,

    NULL,
    NULL,

    ListIterator__iter__,
    NULL
};

Object* list_new()
{
    Object* list_instance = new(&List);

    Node* node = malloc(sizeof(Node));

    node->item = NULL;
    node->previous = NULL;
    node->next = NULL;

    list_instance->raw_data = node;

    return list_instance;
}

Object* list_append(Object* list, Object* item)
{
    Node* node;

    for (node = list->raw_data; node->next != NULL; node = node->next)
        continue;

    if (node->item == NULL)
    {
        node->item = item;
        return list;
    }
    
    node->next = malloc(sizeof(Node));

    node->next->item = item;
    node->next->previous = node;
    node->next->next = NULL;

    return list;
}