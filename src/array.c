#include <stdlib.h>
#include <stdio.h>
#include "array.h"


/**
 * @file
 * @brief Répertorie toutes les fonctions pour gérer des listes chainés de différents types
 * @authors Thomas de Lachaux
 * @authors Louis Bichet
 * @copyright GNU Public License
 */

// ===== INIT =======

/**
 * Crée un tableau dynamique vide
 * @return tableau dynamique vide
 */
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

/**
 * Convertie un type Rdv en type Type, pour pouvoir manipuler les listes chainées
 * @param rdv Rendez-vous
 * @return type
 */
Type fromRdv(Rdv rdv) {
    Type type;
    type.rdv = rdv;
    return type;
}

/**
 * Convertie un type User en type Type, pour pouvoir manipuler les listes chainées
 * @param user Utilisateur
 * @return Type
 */
Type fromUser(User user) {
    Type type;
    type.user = user;
    return type;
}

// ===== GETTERS =====

/**
 * Renvoie un type à l'index donné du tableau
 * @param array Tableau dynamique
 * @param index Index donné
 * @return Type
 */
Type get(Array *array, int index) {
    return getElement(array, index)->value;
}

/**
 * Renvoie un élément à l'index donné du tableau
 * @param array Tableau dynamique
 * @param index Index donné
 * @return Element
 */
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

/**
 * Renvoie le dernier élement du tableau
 * @param array Tableau dynamique
 * @return Element
 */
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

/**
 * Modifie un element à l'index donné du tableau
 * @param array Tableau dynamique
 * @param index Index donné
 * @param new_value Nouvelle valeur
 */
void set(Array *array, int index, Type new_value) {
    Element *element = getElement(array, index);
    element->value = new_value;
}

/**
 * Ajoute un element en fin du tableau
 * @param array Tableau dynamique
 * @param new_value Nouvelle valeur
 */
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

/**
 * Supprime un élément à l'index donné
 * @param array Tableau dynamique
 * @param index Index donné
 */
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

/**
 * Libère le tableau de la RAM
 * @param array Tableau dynamique
 */
void freeArray(Array *array) {
    Element *current = array->first;

    if(current != NULL) {
        while (current->next != NULL) {
            current = current->next;
            free(current);
        }
    }

    free(array->first);
    free(array);
}


/**
 * Debug un tableau (dans le cas d'un tableau d'entiers
 * @param liste Tableau dynamique
 * @deprecated Utilisé seulement pour le développement
 */
void debugArray(Array *liste) {

    Element *elt = liste->first;

    while (elt != NULL)
    {
        printf("%d -> ", elt->value.integer);
        elt = elt->next;
    }
    printf("NULL\n");
}