#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "administration.h"
#include "agenda.h"
#include "tools.h"

// Bug propre à CLion pour afficher printf dans le debugger
#define printf setbuf(stdout, 0);printf

/**
 * \file main.c
 * \author Thomas de Lachaux
 * \version 1.0
 *
 */



void normalUser(int userId) ;


/**
 * \fn int main()
 * \brief Lancement de l'application
 * \return Code d'erreur de l'application
 */
int main() {

    specialDaysNbr = 0;
    filterMode = 1;
    users[0].nRdvs = 0;
    strcpy(users[0].nom, "Thomas");

    usrNbr = 1;

    int choix = 0;

    while (choix != 9) {

        printf("Bienvenue sur votre agenda. Qui etes-vous ?\n0) Administrateur\n");

        for (i = 0; i < usrNbr; i++) {
            printf("%d) %s\n", i + 1, users[i].nom);
        }

        printf("9) Quitter\n");
        scanf("%d", &choix);

        if(choix == 0) {
            administrator();
        }

        else if (choix < 9 && choix <= usrNbr) {
            normalUser(choix - 1);
        }
    }

    printf("A bientot !");
    return 0;
}

void normalUser(int userId) {
    currentUser = userId;

    // Par soucis de lisibilité
    nRdvs = &users[currentUser].nRdvs;
    rdvs = &users[currentUser].rdvs[0];


    printf("Agenda de %s\n", users[currentUser].nom);

    int choice = 0;

    while (choice != 9) {

        printf("\nQuelle action voulez-vous effectuer ?\n"
               "0) Ajouter un rendez-vous\n"
               "1) Lister les rendez-vous d'un jour\n"
               "9) Se deconnecter\n");
        scanf("%d", &choice);


        switch (choice) {

            case 0:
                ajouterUnRdv();
                break;

            case 1:
                listerRdvParJour();
                break;

        }
    }
}