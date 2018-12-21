/**
 * @file
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

void normalUser(int userId);
void initGlobals(int argc);
void saveAgenda();
void generateUsers();
int loadAgenda();
void garbage();
void menu();

/**
 * @brief Lancement de l'application
 * @return Code d'erreur de l'application
 */
int main(int argc, char *argv[]) {

    initGlobals(argc);

    printf("Bienvenue sur votre agenda.\n");

    int choix = 0;
    int i = 1;

    while (choix != i+1) {

        printf("Qui êtes-vous ?\n");
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

    garbage();

    return 0;
}



/**
 * @brief Libère la mémoire non utilisée
 */
void garbage() {
    int i;

    for(i = 0; i < getSize(users); i++) {
        User user = get(users, i).user;
        freeArray(user.rdvs);
    }

    freeArray(specialDays);
    freeArray(users);
}

/**
 * @brief Initialisation variables globales
 * @param argc Nombre d'arguments lors du lancement du programme
 */
void initGlobals(int argc) {

    usegui = argc > 1 ? 1 : 0;

    filterMode = 1;

    users = initArray();
    specialDays = initArray();


    if(!loadAgenda()) {
        printf("Il semblerait que cela soit votre première utilisation.\nPour commmencer, veuillez créer un utilisateur en tant qu'administrateur\n");

        if(!usegui) {
            printf("Si votre console affiche mal les charactères spéciaux: veuillez executer Agenda-encode.exe si vous êtes sur Agenda.exe et inversement.\n");
            printf("Vous pouvez aussi afficher votre Agenda en interface graphique en executant GUI.exe");
        }

        printf("Vous pouvez conserver vos donnéees en sélectionnant Quitter puis Sauvegarder.\n\n");
    }
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

/**
 * @brief Sauvegarde toutes les données de l'agenda dans un binaire save.bin
 */
void saveAgenda() {

    FILE *file = NULL;

    file = fopen("save.bin", "w+b");

    int i,j;

    // Ecriture du mode de fitrage
    fwrite(&filterMode, sizeof(int), 1, file);

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

/**
 * @brief recupère toutes les données de l'agenda depuis save.bin
 * @return 1 si le fichier existe. Sinon 0.
 */
int loadAgenda() {
    FILE *file = NULL;

    file = fopen("save.bin", "rb");

    if(file != NULL) {

        int i, j, userSize, rdvSize, specialDaysSize;

        // Lecture du mode de filtrage
        fread(&filterMode, sizeof(int), 1, file);

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

/**
 * @brief Genère des utilisateurs
 * @deprecated Utilisée pour faciliter le developpement avant les sauvegardes
 */
void generateUsers() {
    User thomas, louis;

    strcpy(thomas.name, "Thomas");
    strcpy(louis.name, "Louis");

    thomas.rdvs = initArray();
    louis.rdvs = initArray();

    add(users, fromUser(thomas));
    add(users, fromUser(louis));
}