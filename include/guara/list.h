#ifndef GUARA_LIST_H
#define GUARA_LIST_H

#include "object.h"

extern Object List;

Object* list_new();
Object* list_append(Object* list, Object* item);

#endif