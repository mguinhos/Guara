#include <string.h>
#include <stdio.h>

#include "guara/int.h"

int Int__int__(Object* self)
{
    return (int)(size_t) self->raw_data;
}

char* Int__repr__(Object* self)
{
    char* buffer = malloc(20 +1);

    if (buffer == NULL)
        return "(int)";
    
    sprintf(buffer, "%llu", (unsigned long long) self->raw_data);

    return buffer;
}

Object Int = {
    &Type,

    "int",
    
    NULL,
    NULL,

    Int__repr__,
    NULL,

    Int__int__,
    NULL,

    NULL,
    NULL
};

Object* int_new(int integer)
{
    Object* int_instance = new(&Int);

    int_instance->raw_data = (void*)(size_t) integer;

    return int_instance;
}