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
// todo: affichage du calendrier sur UI
void normalUser(int userId);
void initGlobals(int argc);
void saveAgenda();
void generateUsers();
int loadAgenda();

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
        for (i = 0; i < getSize(users); i++) {
            printChoice(i + 1, get(users, i).user.name);
        }

        printChoice(i + 1, "Quitter");
        printf("\n");
        inputint(&choix, 0);


        if(choix == 0) {
            administrator();
        }

        else if (choix < i + 1 && choix <= getSize(users)) {
            normalUser(choix - 1);
        }
    }

    int choice = 0;

    do {
        printf("Voulez vous sauvegarder ?\n");
        printChoice(0, "Sauvegarder");
        printChoice(1, "Ne pas sauvegarder");
        inputint(&choice, 1);

        if(choice == 0) {
            printf("Sauvegarde en cours...");
            saveAgenda();
        }
    } while (choice < 0 || choice > 1);
    printf("À bientôt !");
    return 0;
}
/**
 * @fn void initGlobals()
 * @brief Initialisation variables globales
 */
void initGlobals(int argc) {

    usegui = argc > 1 ? 1 : 0;

    filterMode = 1;

    users = initArray();
    specialDays = initArray();

    if(loadAgenda())
        printf("Chargement des données...\n");

    else
        printf("Il semblerait que cela soit votre première utilisation.\nPour commmencer, veuillez créer un utilisateur en tant qu'administrateur\n\n\n");
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

void saveAgenda() {

    FILE *file = NULL;

    file = fopen("save.bin", "w+b");

    int i,j;

    fwrite(&(users->size), sizeof(int), 1, file);

    for(i = 0; i < getSize(users); i++) {
        User user = get(users, i).user;

        // toute la structure est sauvegardé. Il faut faire attention de ne pas utiliser les pointeurs lors de la reouverture
        fwrite(&user, sizeof(user), 1, file);

        fwrite(&(user.rdvs->size), sizeof(int), 1, file);
        for(j = 0; j < getSize(user.rdvs); j++) {
            Rdv rdv = get(user.rdvs, j).rdv;
            fwrite(&rdv, sizeof(rdv), 1, file);
        }
    }

    // Ecriture des journées spéciales
    fwrite(&(specialDays->size), sizeof(int), 1, file);

    for(i = 0; i < getSize(specialDays); i++) {
        Rdv specialDay = get(specialDays, i).rdv;
        fwrite(&specialDay, sizeof(specialDay), 1, file);
    }

    if(file != NULL)
        fclose(file);
}


int loadAgenda() {
    FILE *file = NULL;

    file = fopen("save.bin", "rb");

    if(file != NULL) {

        int i, j, userSize, rdvSize, specialDaysSize;

        // Lecture du nombre d'utilisateurs
        fread(&userSize, sizeof(int), 1, file);



        for(i = 0; i < userSize; i++) {
            User user;

            // Lecture de l'utilisateur
            fread(&user, sizeof(user), 1, file);

            // Lecture du nombre de rendez-vous
            fread(&rdvSize, sizeof(int), 1, file);
            Array *rdvs = initArray();
            user.rdvs = rdvs;

            add(users, fromUser(user));

            for(j = 0; j < rdvSize; j++) {
                Rdv rdv;
                // Lecture du rendez-vous
                fread(&rdv, sizeof(rdv), 1, file);
                add(rdvs, fromRdv(rdv));
            }
        }

        fread(&specialDaysSize, sizeof(int), 1, file);

        for(i = 0; i < specialDaysSize; i++) {
            Rdv specialDay;

            // Lecture du jour spécial
            fread(&specialDay, sizeof(specialDay), 1, file);
            add(specialDays, fromRdv(specialDay));
        }

        fclose(file);

        return 1;
    }

    return 0;
}
// todo: ajouter journéee speciales
void generateUsers() {
    User thomas, louis;

    strcpy(thomas.name, "Thomas");
    strcpy(louis.name, "Louis");

    // todo: creer un fonction createUser
    thomas.rdvs = initArray();
    louis.rdvs = initArray();

    add(users, fromUser(thomas));
    add(users, fromUser(louis));
}