#include <stdlib.h>
#include <stdio.h>
#include "arrays.h"

// todo: passer du camel case a f_f_ pour vars

IntArray *init(int value) {

    IntArray *intArray = malloc(sizeof(*intArray));
    Int *integer = malloc(sizeof(*integer));

    integer->value = value;
    integer->next = NULL;
    intArray->first = integer;

    return intArray;
}

void setFirst(IntArray *intArray, int value) {
    intArray->first->value = value;
}

Int* getLast(IntArray *intArray) {

    Int *elt = intArray->first;

    while (elt->next != NULL) {
        elt = elt->next;
    }

    return elt;
}

int get(IntArray *intArray, int index) {

    Int *elt = intArray->first;
    int i = 0;

    for(i = 0; i < index; i++) {

        if(elt == NULL) {
            printf("Index trop grand !");
            exit(EXIT_FAILURE);
        }

        elt = elt->next;
    }

    return elt->value;
}

void add(IntArray *intArray, int new_value) {

    Int *new_int = malloc(sizeof(*new_int));
    new_int->value = new_value;
    new_int->next = NULL;

    Int *lastElt = getLast(intArray);
    lastElt->next = new_int;
}

void displayArray (IntArray *liste) {

    Int *elt = liste->first;

    while (elt != NULL)
    {
        printf("%d -> ", elt->value);
        elt = elt->next;
    }
    printf("NULL\n");
}