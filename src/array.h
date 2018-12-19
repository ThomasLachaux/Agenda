#ifndef AGENDA_ARRAYS_H
#define AGENDA_ARRAYS_H

#include "tools.h"

Array *initArray();
Type fromInt(int integer);
Type fromRdv(Rdv rdv);
Type fromUser(User user);
Type get(Array *array, int index);
Element *getElement(Array *array, int index);
Element* getLastElement(Array *array);
int getSize(Array *array);
void set(Array *array, int index, Type new_value);
void add(Array *array, Type new_value);
void pop(Array *array, int index);
void sortArrayByStartHour(Array *array);
void freeArray(Array *array);
void debugArray(Array *liste);



#endif //AGENDA_ARRAYS_H
