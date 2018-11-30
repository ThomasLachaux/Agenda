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
#include "array.h"


/*
 * todo: anglissisez les variables
 * todo: gerer les conflits
 * todo: ajouter un lieu, personnes
 */

void normalUser(int userId) ;
void initGlobals(int argc) ;

/**
 * @fn int main()
 * @brief Lancement de l'application
 * @return Code d'erreur de l'application
 */
int main(int argc, char *argv[]) {

    initGlobals(argc);

    // todo: faire un executable chcp 850 et 33165
    // todo: choisir entre console et GUI
    int choix = 0;

    int i = 1;

    // todo: PASSER à DES DO WHILE
    while (choix != i+1) {

        printf("Bienvenue sur votre agenda. Qui êtes-vous ?\n");
        printChoice(0, "Administrateur");
        for (i = 0; i < getSize(newUsers); i++) {
            printChoice(i + 1, get(newUsers, i).user.name);
        }

        printChoice(i + 1, "Quitter");
        printf("\n");
        inputint(&choix, 0);


        if(choix == 0) {
            administrator();
        }

        else if (choix < i + 1 && choix <= getSize(newUsers)) {
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
void initGlobals(int argc) {

    usegui = argc > 1 ? 1 : 0;

    specialDaysNbr = 0;
    filterMode = 1;

    newUsers = initArray();

    User thomas, louis;

    strcpy(thomas.name, "Thomas");
    strcpy(louis.name, "Louis");

    // todo: creer un fonction createUser
    thomas.rdvs = initArray();
    louis.rdvs = initArray();

    add(newUsers, fromUser(thomas));
    add(newUsers, fromUser(louis));

}

/**
 * @brief Menu agenda
 * @param userId : identité utilisateur
 */
void normalUser(int userId) {
    currentUser = userId;

    // Par soucis de lisibilité
    rdvs = get(newUsers, currentUser).user.rdvs;

    printf("Agenda de %s\n", get(newUsers, currentUser).user.name);

    int choice = 0;
    int i = 1;

    while (choice != i + 1) {

        printf("\nQuelle action voulez-vous effectuer ?\n");
        printChoice(0, "Ajouter un rendez-vous");
        printChoice(1, "Lister les rendez-vous d'un jour");
        printChoice(i + 1, "Se déconnecter");
        printf("\n");
        inputint(&choice, 0);

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