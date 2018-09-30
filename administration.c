//
// Created by Thomas on 30-Sep-18.
//

#include <stdio.h>

#include "administration.h"
#include "tools.h"

void administrator() {
    int choix = 0;

    while (choix != 9) {
        printf("Bienvenue sur l'interface d'administration\n"
               "0) Ajouter un utilisateur\n"
               "1) Lister les utilisateurs\n"
               "2) Ajouter un jour special\n"
               "3) Lister les jours speciaux\n"
               "9) Se deconnecter\n");
        scanf("%d", &choix);

        switch (choix) {
            case 0:
                newUser();
                break;

            case 1:
                listUsers();
                break;
        }

        if(choix == 0)
            newUser();

        else if(choix == 1)
            listUsers();

        else if(choix == 2) {

            int day, month, year;

            promptDate(&day, &month, &year);

            struct Rdv newRdv;

            newRdv.jour = day;
            newRdv.mois = month;
            newRdv.annee = year;

            specialDays[specialDaysNbr] = newRdv;
            specialDaysNbr++;

        }
    }
}

void newUser() {
    struct User user;

    user.nRdvs = 0;

    printf("Nom de l'utilisateur ?\n");
    scanf("%s", user.nom);

    users[usrNbr] = user;
    usrNbr++;
}

void listUsers() {

    for (i = 0; i < usrNbr; i++) {
        printf("%d) %s\n", i + 1, users[i].nom);
    }

    int choix = 0;

    while(choix != 9) {
        printf("\n1) Renommer un utilisateur\n2) Supprimer un utilisateur\n9) Retour a l'interface d'administration");
        scanf("%d", &choix);

        if(choix == 1 || choix == 2) {

            int usrId;

            printf("Identifiant de l'utilisateur ? (Entre 1 et %d)\n", usrNbr);
            scanf("%d", &usrId);

            usrId--;

            if(choix == 1) {
                printf("Nouveau nom de l'utilisateur ?\n");
                scanf("%s", users[usrId].nom);
                printf("Le nouveau nom de l'utilisateur est %s\n", users[usrId].nom);
            }

            else if(choix == 2) {
                printf("Suppression de l'utilisateur %s...\n", users[usrId].nom);
                users[usrId] = users[usrNbr];
                usrNbr--;
            }
        }
    }

}