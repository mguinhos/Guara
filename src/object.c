#include <malloc.h>
#include <memory.h>
#include <string.h>
#include <stdio.h>

#include "guara/object.h"
#include "guara/tracer.h"
#include "guara/str.h"

char* Type__repr__(Object* self)
{
    if (self->raw_data == NULL)
    {
        char* buffer = malloc(32);

        if (buffer == NULL)
            return "(type)";

        sprintf(buffer, "(type at %p)", self);
        
        return buffer;
    }

    char* buffer = malloc(16 + strlen((char*) self->raw_data));

    if (buffer == NULL)
        return "(type)";

    sprintf(buffer, "(type '%s')", (char*) self->raw_data);
    
    return buffer;
}

Object Type = {
    NULL,

    "type",

    NULL,
    NULL,

    Type__repr__,
    NULL,

    NULL,
    NULL
};

char* NoneType__repr__()
{
    return "None";
}

Object NoneType = {
    &Type,

    "NoneType",

    NULL,
    NULL,

    NoneType__repr__,
    NULL,

    NULL,
    NULL
};

Object None = {
    &NoneType,

    NULL,
    
    NULL,
    NULL,

    NULL,
    NULL,

    NULL,
    NULL
};

char* name(Object* object)
{
    if (object == NULL)
        return "(name)";

    if (object->type == NULL || object->type == &Type)
        return object->raw_data;
    else if (object->type->type == &Type)
        return name(object->type);
    
    return "(name)";
}

char* repr(Object* object)
{
    if (object == NULL)
        return "(repr)";
        
    else if (object->type == NULL)
    {
        if (object->__repr__ != NULL)
            return object->__repr__(object);
        else if (object->__str__ != NULL)
            return str(object);
    }
    else if (object->type->__repr__ != NULL)
        return object->type->__repr__(object);
    else if (object->type->__str__ != NULL)
        return str(object);

    
    char* object_name = name(object);
    char* buffer = malloc(32 + strlen(object_name));

    if (buffer == NULL)
        return "(object)";
    
    sprintf(buffer, "(object '%s' at %p)", object_name, object);

    return buffer;
}

char* str(Object* object)
{
    if (object == NULL)
        return "(str)";

    else if (object->type == NULL)
    {
        if (object->__str__ != NULL)
            return object->__str__(object);
        else if (object->__str__ != NULL)
            return object->__str__(object);
    }
    else if (object->type->__str__ != NULL)
        return object->type->__str__(object);
    else if (object->type->__str__ != NULL)
        return object->type->__str__(object);
    
    return repr(object);
}



Object* new(Object* type)
{
    Object* instance = malloc(sizeof(Object));

    instance->type = type;

    instance->raw_data = type->raw_data;

    instance->__init__ = type->__init__;
    instance->__del__ = type->__del__;

    instance->__repr__ = type->__repr__;
    instance->__str__ = type->__str__;
    instance->__float__ = type->__float__;
    instance->__int__ = type->__int__;

    instance->__iter__ = type->__iter__;
    instance->__next__ = type->__next__;

    return instance;
}

Object* type(Object* object)
{
    if (object == NULL)
        return &NoneType;
    else if (object->type == NULL)
        return &Type;

    return object->type;
}

Object* iter(Object* object)
{
    if (object == NULL)
        return &None;
    else if (object->type != NULL && object->type->__iter__ != NULL)
        return object->type->__iter__(object);
    else if (object->__iter__ != NULL)
        return object->__iter__(object);

    char* buffer = malloc(64);

    sprintf(buffer, "'%s' object is not iterable", (char*) type(object)->raw_data);
    throw(typeerror_new(str_new(buffer)));

    return &None;
}

Object* next(Object* object)
{
    if (object == NULL)
        return &None;
    else if (object->type != NULL && object->type->__next__ != NULL)
        return object->type->__next__(object);
    else if (object->__next__ != NULL)
        return object->__next__(object);

    return &None;
}