#ifndef GUARA_EXCEPTION_H
#define GUARA_EXCEPTION_H

#include "object.h"

extern Object BaseException;
extern Object NotImplementedError;
extern Object TypeError;
extern Object StopIteration;

Object* baseexception_new(Object* message);
Object* notimplementederror_new(Object* message);
Object* typeerror_new(Object* message);
Object* stopiteration_new(Object* message);

#define NOTIMPLEMENTED throw(notimplementederror_new(str_new("this feature is currently not implemented")));

#endif