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

void normalUser(int userId);
void initGlobals(int argc);
void save();

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
    int i;
    //setbuf(stdout, NULL);

    while (choix != 9) {

        printf("Bienvenue sur votre agenda. Qui êtes-vous ?\n");
        printChoice(0, "Administrateur");
        for (i = 0; i < getSize(users); i++) {
            printChoice(i + 1, get(users, i).user.name);
        }

        printChoice(9, "Quitter");
        printf("\n");
        inputint(&choix, 0);

        if(choix == 0) {
            administrator();
        }

        else if (choix < 9 && choix <= getSize(users)) {
            normalUser(choix - 1);
        }
    }

    int choice = 0;

    while (choice < 0 || choice > 1) {
        printf("Voulez vous sauvegarder ?\n");
        printChoice(0, "Sauvegarder");
        printChoice(1, "Ne pas sauvegarder");
        inputint(&choice, 1);

        if(choice == 0) {
            printf("Sauvegarde en cours...");
            save();
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

    users = initArray();

    User thomas, louis;

    strcpy(thomas.name, "Thomas");
    strcpy(louis.name, "Louis");

    // todo: creer un fonction createUser
    thomas.rdvs = initArray();
    louis.rdvs = initArray();

    add(users, fromUser(thomas));
    add(users, fromUser(louis));

}

/**
 * @brief Menu agenda
 * @param userId : identité utilisateur
 */
void normalUser(int userId) {
    currentUser = userId;

    // Par soucis de lisibilité
    rdvs = get(users, currentUser).user.rdvs;

    printf("Agenda de %s\n", get(users, currentUser).user.name);

    int choice = 0;

    while (choice != 9) {

        printf("\nQuelle action voulez-vous effectuer ?\n");
        printChoice(0, "Ajouter un rendez-vous");
        printChoice(1, "Lister les rendez-vous d'un jour");
        printChoice(9, "Se déconnecter");
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

void save() {

    FILE *file = NULL;

    file = fopen("save.bin", "w+b");

    int i,j;

    for(i = 0; i < getSize(users); i++) {
        User user = get(users, i).user;

        fwrite(user.name, sizeof(char), strlen(user.name), file);

        for(j = 0; j < getSize(user.rdvs); j++) {

        }
    }

    if(file != NULL)
        fclose(file);
}