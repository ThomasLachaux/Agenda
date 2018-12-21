/**
 * @file administration.c
 * @authors Thomas de Lachaux
 * @authors Louis Bichet
 * @copyright GNU Public License
 */

#include <stdio.h>

#include "administration.h"
#include "tools.h"


/**
 * @brief Menu admnistrateur
 */
void administrator() {
    int choice = 0;
    const int i = 5;

    while (choice != i) {
        printf("Bienvenue sur l'interface d'administration\n");

        printChoice(0, "Ajouter un utilisateur");
        printChoice(1, "Lister les utilisateurs");
        printChoice(2, "Ajouter un jour spécial");
        printChoice(3, "Lister les jours spéciaux");
        printChoice(4, "Modifier le mode d'affichage");
        printChoice(i, "Se déconnecter");

        inputint(&choice, 0);

        switch (choice) {
            case 0:
                newUser();
                break;

            case 1:
                listUsers();
                break;

            case 2:
                add(specialDays, fromRdv(promptSpecialDay()));
                break;

            case 3:
                listSpecialDays();
                break;

            case 4:
                setFilterMode();
                break;
        }
    }
}

/**
 * @brief Saisie nouvel utilisateur
 */

void newUser() {

    User user;

    printf("Nom de l'utilisateur ?\n");
    input(user.name, 40, 1);

    user.rdvs = initArray();

    add(users, fromUser(user));
}

/**
 * @brief liste les utilisateurs et affiche les options de gestion des utilisateurs
 */
void listUsers() {

    int i;

    // Affichage des utilisateurs
    for (i = 0; i < getSize(users); i++) {
        printf("%d) %s\n", i + 1, get(users, i).user.name);
    }

    int choix = 0;

    while(choix != 3) {
        printf("\n");
        printChoice(1, "Renommer un utilisateur");
        printChoice(2, "Supprimer un utilisateur");
        printChoice(3, "Retour à l'interface d'administration");

        inputint(&choix, 0);


        if(choix == 1 || choix == 2) {

            int usrId;

            printf("Identifiant de l'utilisateur ? (Entre 1 et %d)\n", getSize(users));
            inputint(&usrId, 1);

            usrId--;

            if(choix == 1) {
                printf("Nouveau nom de l'utilisateur ?\n");
                char *new_name = getElement(users, usrId)->value.user.name;
                input(new_name, 39, 1);
                printf("Le nouveau nom de l'utilisateur est %s\n", new_name);
            }

            else if(choix == 2) {
                printf("Suppression de l'utilisateur %s...\n", get(users, usrId).user.name);
                pop(users, usrId);
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
    input(specialDay.label, 99, 1);

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

    // Affichage des jours spéciaux
    for(i = 0; i < getSize(specialDays); i++) {
        displaySpecialDay(i + 1, get(specialDays, i).rdv);
    }

    while (choice != 3) {
        printChoice(1, "Modifier un jour spécial");
        printChoice(2, "Supprimer un jour spécial");
        printChoice(3, "Retour au menu");
        inputint(&choice, 0);

        if(choice == 1 || choice == 2) {

            printf("Identifiant du jour spécial ? (De 1 a %d)\n", getSize(specialDays));
            inputint(&specialDayId, 0);

            specialDayId--;

            if(choice == 1)
                set(specialDays, specialDayId, fromRdv(promptSpecialDay()));

            else if(choice == 2) {
                printf("Suppression du jour spécial %s\n", get(specialDays, specialDayId).rdv.label);
                pop(specialDays, specialDayId);
            }
        }
    }
}

/**
 * @brief fonction d'affichage
 * @param id  identifiant
 * @param specialDay  structure jour spécial
 */


void displaySpecialDay(int id, Rdv specialDay) {
    printf("%d) %02d/%02d/%04d: %s\n", id, specialDay.day, specialDay.month, specialDay.year, specialDay.label);
}

/**
 * Change le mode de filtrage
 */
void setFilterMode() {

    int choice;
    do {
        printf("Nouveau mode de filtrage ?\n");
        printChoice(1, "Filtrage par jour");
        printChoice(2, "Filtrage par semaine");
        printChoice(3, "Filtrage par mois");

        inputint(&choice, 0);
    } while (choice < 1 || choice > 3);

    filterMode = choice;

    printf("Mode de filtrage modifié\n");
}