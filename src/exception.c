#include <string.h>
#include <stdio.h>

#include "guara/tracer.h"
#include "guara/exception.h"

char* BaseException__repr__(Object* self)
{
    char* buffer = malloc(20 +1);

    if (buffer == NULL)
        return "(base-exception)";
    
    sprintf(buffer, "%s(%s)", (char*) type(self)->raw_data, repr(self->raw_data));

    return buffer;
}

Object BaseException = {
    &Type,

    "BaseException",
    
    NULL,
    NULL,

    BaseException__repr__,
    NULL,

    NULL,
    NULL,

    NULL,
    NULL
};

Object NotImplementedError = {
    &BaseException,

    "NotImplementedError",
    
    NULL,
    NULL,

    NULL,
    NULL,

    NULL,
    NULL,

    NULL,
    NULL
};

Object TypeError = {
    &BaseException,

    "TypeError",
    
    NULL,
    NULL,

    NULL,
    NULL,

    NULL,
    NULL,

    NULL,
    NULL
};

Object StopIteration = {
    &BaseException,

    "StopIteration",
    
    NULL,
    NULL,

    NULL,
    NULL,

    NULL,
    NULL,

    NULL,
    NULL
};

Object* baseexception_new(Object* message)
{
    Object* baseexception_instance = new(&BaseException);

    baseexception_instance->raw_data = message;

    return baseexception_instance;
}

Object* stopiteration_new(Object* message)
{
    Object* stopiteration_instance = new(&StopIteration);

    stopiteration_instance->raw_data = message;

    return stopiteration_instance;
}

Object* notimplementederror_new(Object* message)
{
    Object* notimplementederror_instance = new(&NotImplementedError);

    notimplementederror_instance->raw_data = message;

    return notimplementederror_instance;
}

Object* typeerror_new(Object* message)
{
    Object* typeerror_instance = new(&TypeError);

    typeerror_instance->raw_data = message;

    return typeerror_instance;
}