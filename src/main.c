/**
 * @file main.c
 * @brief Point d'entrée de l'application. L'utilisateur choisit entre le mode admin et utilisateur
 * @authors Thomas de Lachaux
 * @authors Louis Bichet
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "administration.h"
#include "agenda.h"
#include "tools.h"

// Bug propre à CLion pour afficher printf dans le debugger
#define printf setbuf(stdout, 0);printf



/*
 * todo: anglissisez les variables
 * todo: gerer les conflits
 * todo: gerer les heures +24
 * todo: ajouter un lieu, personnes
 * todo: gerer pb scanf espace
 */


void normalUser(int userId) ;
void initGlobals() ;

/**
 * @fn int main()
 * @brief Lancement de l'application
 * @return Code d'erreur de l'application
 */
int main() {
    printf("J'ai un super téléphone");
    initGlobals();

    int choix = 0;
    int i;

    while (choix != 9) {

        printf("Bienvenue sur votre agenda. Qui êtes-vous ?\n0) Administrateur\n");

        for (i = 0; i < usrNbr; i++) {
            printf("%d) %s\n", i + 1, users[i].name);
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

    printf("À bientôt !");
    return 0;
}
/**
 * @fn void initGlobals()
 * @brief Initialisation variables globales
 */
void initGlobals() {
    specialDaysNbr = 0;
    filterMode = 1;
    users[0].nRdvs = 0;
    strcpy(users[0].name, "Thomas");
    strcpy(users[1].name, "Louis");

    usrNbr = 2;
}

/**
 * @brief Menu agenda
 * @param userId : identité utilisateur
 */
void normalUser(int userId) {
    currentUser = userId;

    // Par soucis de lisibilité
    nRdvs = &users[currentUser].nRdvs;
    rdvs = &users[currentUser].rdvs[0];


    printf("Agenda de %s\n", users[currentUser].name);

    int choice = 0;

    while (choice != 9) {

        printf("\nQuelle action voulez-vous effectuer ?\n"
               "0) Ajouter un rendez-vous\n"
               "1) Lister les rendez-vous d'un jour\n"
               "9) Se déconnecter\n");
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