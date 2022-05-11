#include <stdio.h>
#include "guara.h"

bool module_main()
{
    Object* fruits = list_new();

    list_append(fruits, str_new("maca"));
    list_append(fruits, str_new("banana"));
    list_append(fruits, int_new(40));
    list_append(fruits, str_new("pera"));
    list_append(fruits, int_new(60));

    puts(repr(fruits));

    Object* fruits_iterator = &None;
    Object* fruit = &None;

    for (fruits_iterator = iter(fruits); catch(&StopIteration) == &None; )
    {
        fruit = next(fruits_iterator);

        puts(str(fruit));
    }

    return true;
}

int main()
{
    tracer_enter("main.c");
    module_main();
    tracer_leave();
}