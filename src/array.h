//
// Created by Thomas on 21-Oct-18.
//

#ifndef AGENDA_ARRAYS_H
#define AGENDA_ARRAYS_H

#include "tools.h"

typedef struct Type Type;
struct Type {
    Rdv rdv;
    User user;
    int number;
};

typedef struct Element Element;
struct Element {
    Type value;
    Element *next;
};

typedef struct Array Array;
struct Array {
    Element *first;
    int size;
};

Array *initArray();
Type get(Array *array, int index);
Element *getElement(Array *array, int index);
Element* getLastElement(Array *array);
int getSize(Array *array);
void add(Array *array, Type new_value);
void displayArray(Array *liste);



#endif //AGENDA_ARRAYS_H
