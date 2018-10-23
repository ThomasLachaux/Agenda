/**
 * @file administration.c
 * @authors Thomas de Lachaux
 * @authors Louis Bichet
 * @copyright GNU Public License
 */

#include <stdio.h>

#include "administration.h"
#include "tools.h"

// Bug propre à CLion pour afficher printf dans le debugger
#define printf setbuf(stdout, 0);printf

/**
 * @brief Menu admnistrateur
 */
void administrator() {
    int choix = 0;

    while (choix != 9) {
        printf("Bienvenue sur l'interface d'administration\n"
               "0) Ajouter un utilisateur\n"
               "1) Lister les utilisateurs\n"
               "2) Ajouter un jour spécial\n"
               "3) Lister les jours spéciaux\n"
               "9) Se déconnecter\n");
        scanf("%d", &choix);

        switch (choix) {
            case 0:
                newUser();
                break;

            case 1:
                listUsers();
                break;

            case 2:
                specialDays[specialDaysNbr] = promptSpecialDay();
                specialDaysNbr++;
                break;

            case 3:
                listSpecialDays();
                break;
        }
    }
}

/**
 * @brief Saisie nouvel utilisateur
 */

void newUser() {

    Type type;

    printf("Nom de l'utilisateur ?\n");
    scanf("%s", type.user.name);

    type.user.rdvs = initArray();
    add(newUsers, type);
}

/**
 * @brief liste les utilisateurs et affiche les options de gestion des utilisateurs
 */

void listUsers() {

    int i;

    for (i = 0; i < getSize(newUsers); i++) {
        printf("%d) %s\n", i + 1, get(newUsers, i).user.name);
    }

    int choix = 0;

    while(choix != 9) {
        printf("\n1) Renommer un utilisateur\n2) Supprimer un utilisateur\n9) Retour à l'interface d'administration");
        scanf("%d", &choix);

        if(choix == 1 || choix == 2) {

            int usrId;

            printf("Identifiant de l'utilisateur ? (Entre 1 et %d)\n", getSize(newUsers));
            scanf("%d", &usrId);

            usrId--;

            if(choix == 1) {
                printf("Nouveau nom de l'utilisateur ?\n");
                char *new_name = getElement(newUsers, usrId)->value.user.name;
                scanf("%s", new_name);
                printf("Le nouveau nom de l'utilisateur est %s\n", new_name);
            }

            else if(choix == 2) {
                printf("Suppression de l'utilisateur %s...\n", get(newUsers, usrId).user.name);
                pop(newUsers, usrId);
            }
        }
    }
}

/**
 * @brief Propose d'ajouter/modifier un jour spécial
 * @return Jour spécial
 */
Rdv promptSpecialDay () {
    Rdv specialDay;
    int day, month, year;

    printf("Nom du jour spécial ?\n");
    scanf("%s", specialDay.label);

    promptDate(&day, &month, &year);


    specialDay.day = day;
    specialDay.month = month;
    specialDay.year = year;

    return specialDay;
}

/**
 * @brief affiches les jours  spéciaux et les options de ceux-ci
 */

void listSpecialDays() {

    int i;
    int choice = 0;
    int specialDayId;

    for(i = 0; i < specialDaysNbr; i++) {
        displaySpecialDay(i + 1, &specialDays[i]);
    }

    while (choice != 9) {
        printf("1) Modifier un jour spécial\n2) Supprimer un jour spécial\n9) Retour au menu\n");
        scanf("%d", &choice);

        if(choice == 1 || choice == 2) {

            printf("Identifiant du jour spécial ? (De 1 a %d)\n", specialDaysNbr);
            scanf("%d", &specialDayId);

            specialDayId--;

            if(choice == 1)
                specialDays[specialDayId] = promptSpecialDay();

            else if(choice == 2) {
                printf("Suppression du jour spécial %s\n", specialDays[specialDayId].label);
                specialDays[specialDayId] = specialDays[specialDaysNbr - 1];
                specialDaysNbr--;
            }
        }
    }
}

/**
 * @brief fonction d'affichage
 * @param id  identifiant
 * @param specialDay  structure jour spécial
 */


void displaySpecialDay(int id, Rdv *specialDay) {
    printf("%d) %02d/%02d/%04d: %s\n", id, specialDay->day, specialDay->month, specialDay->year, specialDay->label);
}