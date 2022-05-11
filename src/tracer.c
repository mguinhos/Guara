#include <stdio.h>

#include <malloc.h>
#include "guara/tracer.h"

TracerState* epoch = NULL;
Object* traced_exception = NULL;

bool tracer_init()
{
    if (epoch != NULL)
        return true;
    
    epoch = malloc(sizeof(TracerState));

    if (epoch == NULL)
    {
        fputs("fatal (from tracer::tracer_init): epoch allocation failed\n", stderr);
        exit(-1);
    }

    *epoch = (TracerState) {
        "tracer.c",

        NULL,
        NULL
    };

    return true;
}

void tracerstate_print(TracerState* state)
{
    fprintf(stderr, "  Origin '%s'\n", state->origin);
}

void tracer_print()
{
    tracer_init();

    TracerState* state;

    fputs("Tracer (most recent call last)\n", stderr);

    for (state = epoch; state->next != NULL; state = state->next)
        tracerstate_print(state);
    
    tracerstate_print(state);

    // this seems to be unstable
    // note: fix later
    if (traced_exception == NULL)
        fputs("Sucess\n", stderr);
    else if (traced_exception->raw_data == NULL)
        fprintf(stderr, "%s\n", (char*) type(traced_exception)->raw_data);
    else
        fprintf(stderr, "%s: %s\n",  (char*) type(traced_exception)->raw_data, str(traced_exception->raw_data));
}

void tracer_enter(char* origin)
{
    tracer_init();

    TracerState* state;

    for (state = epoch; state->next != NULL; state = state->next)
        continue;
    
    TracerState* new_state = malloc(sizeof(TracerState));

    if (new_state == NULL)
    {
        fputs("fatal (from tracer::tracer_enter): new_state allocation failed\n", stderr);
        exit(-1);
    }

    new_state->origin = origin;
    new_state->previous = state;
    new_state->next = NULL;

    state->next = new_state;
}

bool tracer_leave()
{
    TracerState* state; 

    // this can cause trouble later
    // note: review later if it is the best approach
    if (traced_exception != NULL)
    {
        tracer_print();
        exit(-1);
    }

    for (state = epoch; state->next != NULL; state = state->next)
        continue;
    
    state->previous->next = NULL;
    free(state);

    return true;
}

Object* catch(Object* exception)
{
    if (traced_exception == NULL)
        return &None;
    
    else if (type(traced_exception) != exception)
        return &None;
    
    Object* catched_exception = traced_exception;

    traced_exception = NULL;
    
    return catched_exception;
}

bool throw(Object* exception)
{
    if (traced_exception != NULL)
    {
        tracer_print();
        exit(-1);
    }

    traced_exception = exception;

    return true;
}