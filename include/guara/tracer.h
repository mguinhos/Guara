#ifndef GUARA_TRACER_H
#define GUARA_TRACER_H

#include "exception.h"
#include "object.h"

typedef struct tracerstate
{
    char* origin;

    struct tracerstate* previous;
    struct tracerstate* next;
}
TracerState;

extern TracerState* epoch;

void tracerstate_print(TracerState* state);
void tracer_print();

void tracer_enter(char* origin);
bool tracer_leave();

Object* catch(Object* exception);
bool throw(Object* exception);

#endif