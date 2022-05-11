#include <string.h>
#include <stdio.h>

#include "guara/str.h"

char* Str__str__(Object* self)
{
    if (self->raw_data == NULL)
        return "(str.__str__)";

    return self->raw_data;
}

char* Str__repr__(Object* self)
{
    if (self->raw_data == NULL)
    {
        char* buffer = malloc(2 +1);

        if (buffer == NULL)
            return "(str.__repr__)";

        buffer[0] = '"';
        buffer[1] = '"';
        buffer[2] = '\0';

        return buffer;
    }

    char* buffer = malloc(2 + strlen((char*) self->raw_data));

    if (buffer == NULL)
        return "(string)";
    
    sprintf(buffer, "'%s'", (char*) self->raw_data);

    return buffer;
}

Object Str = {
    &Type,

    "str",
    
    NULL,
    NULL,

    Str__repr__,
    Str__str__,

    NULL,
    NULL,

    NULL,
    NULL
};

Object* str_new(char* string)
{
    Object* str_instance = new(&Str);

    str_instance->raw_data = string;

    return str_instance;
}