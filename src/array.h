//
// Created by Thomas on 21-Oct-18.
//

#ifndef AGENDA_ARRAYS_H
#define AGENDA_ARRAYS_H

#include "tools.h"

Array *initArray();
Type get(Array *array, int index);
Element* getLastElement(Array *array);
int getSize(Array *array);
void add(Array *array, Type new_value);
void displayArray(Array *liste);



#endif //AGENDA_ARRAYS_H
