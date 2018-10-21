//
// Created by Thomas on 21-Oct-18.
//

#ifndef AGENDA_ARRAYS_H
#define AGENDA_ARRAYS_H


typedef struct Int Int;
struct Int {
    int value;
    Int *next;
};

typedef struct IntArray IntArray;
struct IntArray {
    Int *first;
};

IntArray *init(int value);
void setFirst(IntArray *intArray, int value);
Int* getLast(IntArray *intArray);
int get(IntArray *intArray, int index);
void add(IntArray *intArray, int new_value);
void displayArray(IntArray *liste);



#endif //AGENDA_ARRAYS_H
