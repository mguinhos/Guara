#ifndef GUARA_OBJECT_H
#define GUARA_OBJECT_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct object
{
    struct object* type;

    void* raw_data;

    void (*__init__)(struct object*);
    void (*__del__)(struct object*);

    char* (*__repr__)(struct object*);
    char* (*__str__)(struct object*);
    
    int (*__int__)(struct object*);
    float (*__float__)(struct object*);

    struct object* (*__iter__)(struct object*);
    struct object* (*__next__)(struct object*);
}
Object;

extern Object Type;
extern Object NoneType;
extern Object None;

char* repr(Object* object);
char* str(Object* object);
char* name(Object* object);

Object* new(Object* type);
Object* type(Object* object);
Object* iter(Object* object);
Object* next(Object* object);

#endif