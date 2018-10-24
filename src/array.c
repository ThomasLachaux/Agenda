#include <stdlib.h>
#include <stdio.h>
#include "array.h"

// todo: passer du camel case a f_f_ pour vars

// ===== INIT =======
Array *initArray() {

    Array *array = malloc(sizeof(*array));
    array->first = NULL;
    array->size = 0;

    return array;
}

Type fromInt(int integer) {
    Type type;
    type.integer = integer;
    return type;
}

Type fromRdv(Rdv rdv) {
    Type type;
    type.rdv = rdv;
    return type;
}

Type fromUser(User user) {
    Type type;
    type.user = user;
    return type;
}

// ===== GETTERS =====

Type get(Array *array, int index) {
    return getElement(array, index)->value;
}

Element *getElement(Array *array, int index) {
    Element *elt = array->first;
    int i = 0;

    for(i = 0; i < index; i++) {

        if(elt == NULL) {
            printf("Index trop grand !");
            exit(EXIT_FAILURE);
        }

        elt = elt->next;
    }

    return elt;
}

Element *getLastElement(Array *array) {

    Element *elt = array->first;

    while (elt->next != NULL) {
        elt = elt->next;
    }

    return elt;
}

int getSize(Array *array) {
    return array->size;
}

// ===== SETTERS =====

void set(Array *array, int index, Type new_value) {
    Element *element = getElement(array, index);
    element->value = new_value;
}

void add(Array *array, Type new_value) {

    Element *new_elt = malloc(sizeof(*new_elt));
    new_elt->value = new_value;
    new_elt->next = NULL;
    new_elt->previous = NULL;

    // Si il n'y a aucun element dans le tableau
    if (array->first == NULL) {
        array->first = new_elt;
    }

        // Si il y a un element dans le tableau
    else {
        Element *lastElt = getLastElement(array);
        lastElt->next = new_elt;
        new_elt->previous = lastElt;
    }

    array->size++;
}

void pop(Array *array, int index) {
    Element *to_delete = getElement(array, index);
    Element *previous = to_delete->previous;
    Element *next = to_delete->next;

    // Si il n'est pas premier de la liste
    if(previous != NULL) {
        previous->next = next;
        next->previous = previous;
    }

    // Si il est premier de la liste
    else {
        array->first = next;
        next->previous = NULL;
    }

    free(to_delete);
}

void debugArray(Array *liste) {

    Element *elt = liste->first;

    while (elt != NULL)
    {
        printf("%d -> ", elt->value.integer);
        elt = elt->next;
    }
    printf("NULL\n");
}