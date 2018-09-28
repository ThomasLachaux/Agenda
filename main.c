#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"
#pragma clang diagnostic push
#pragma ide diagnostic ignored "missing_default_case"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Bug propre à CLion pour afficher printf dans le debugger
#define printf setbuf(stdout, 0);printf

/**
 * \file main.c
 * \author Thomas de Lachaux
 * \version 1.0
 *
 */

struct Rdv {
    int annee;
    int mois;
    int date;
    int heure;
    int minute;
    int duree;
};

int nRdvs;
struct Rdv rdvs[1000];


void ajouterUnRdv();
void listerRdvParJour();
void afficherRdv(int id, struct Rdv rdv);
struct Rdv nouveauRdv();


void promptDate(int *jour, int *mois, int *annee) ;

void sauvegarderRdv(struct Rdv *rdv) ;


/**
 * \fn int main()
 * \brief Lancement de l'application
 * \return Code d'erreur de l'application
 */
int main() {

    int choice = 0;
    nRdvs = 0;




    while (choice != 9) {

        printf("\nQuelle action voulez-vous effectuer ?\n"
               "0) Ajouter un rendez-vous\n"
               "1) Lister les rendez-vous d'un jour\n"
               "9) Quitter\n");
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

    printf("A bientot !");
    return 0;
}


void listerRdvParJour() {

    int jour, mois, annee;
    promptDate(&jour, &mois, &annee);

    struct Rdv *rdvDuJour[1000];

    int i = 0;
    int j = 0;

    for (i = 0; i < nRdvs; i++) {
        if(rdvs[i].date == jour && rdvs[i].mois == mois && rdvs[i].annee == annee) {
            rdvDuJour[j] = &rdvs[i];
            afficherRdv(j + 1, *rdvDuJour[j]);
            j++;
        }

    }

    if(j == 0) {
        printf("Aucun rendez-vous ce jour-ci\n");
    }

    else {
        int choix = 0;

        while (choix != 9) {
            printf("\n"
                   "1) Modifier un rendez-vous\n"
                   "2) Supprimer un rendez-vous\n"
                   "3) Sauvegarder un rendez-vous\n"
                   "9) Menu principal\n");
            scanf("%d", &choix);

            if(choix == 1 || choix == 2 || choix == 3) {
                int id;
                printf("Identifiant du rendez-vous ? (De 1 a %d)\n", j);
                scanf("%d", &id);

                if(choix == 1) {
                    printf("Modification du rendez-vous...\n");
                    *rdvDuJour[id - 1] = nouveauRdv();
                }

                else if (choix == 2) {
                    printf("Suppression du rendez-vous...\n");
                    *rdvDuJour[id - 1] = rdvs[nRdvs - 1];
                    nRdvs--;
                }

                else if (choix == 3) {
                    printf("Sauvegarde du rendez-vous...\n");
                    sauvegarderRdv(rdvDuJour[id - 1]);
                }
            }

        }
    }
}


void ajouterUnRdv() {
    rdvs[nRdvs] = nouveauRdv();
    nRdvs++;
}

struct Rdv nouveauRdv() {

    char tmp;
    struct Rdv newRdv;

    promptDate(&newRdv.date, &newRdv.mois, &newRdv.annee);

    printf("Heure du rendez-vous ? (Format hh:mm)\n");
    scanf("%d%c%d", &newRdv.heure, &tmp, &newRdv.minute);

    printf("Duree du rendez-vous ?\n");
    scanf("%d", &newRdv.duree);

    return newRdv;
}

void afficherRdv(int id, struct Rdv rdv) {

    int minuteFin = (rdv.minute + rdv.duree) % 60;
    int heureFin = (rdv.heure * 60 + rdv.minute + rdv.duree) / 60;

    printf("\n%d) "
           "Date de rendez-vous: %02d/%02d/%04d\n"
           "   Heure de debut: %02d:%02d\n"
           "   Heure de fin: %02d:%02d\n",
           id, rdv.date, rdv.mois, rdv.annee, rdv.heure, rdv.minute, heureFin, minuteFin);
}

void sauvegarderRdv(struct Rdv *rdv) {

    FILE *file = NULL;
    char filename[250];

    printf("Nom du ficher ?");
    scanf("%s", filename);
    strcat(filename, ".txt");

    file = fopen(filename, "w");

    int minuteFin = (rdv->minute + rdv->duree) % 60;
    int heureFin = (rdv->heure * 60 + rdv->minute + rdv->duree) / 60;

    fprintf(file, "Date de rendez-vous: %02d/%02d/%04d\n"
                  "Heure de debut: %02d:%02d\n"
                  "Heure de fin: %02d:%02d\n",
            rdv->date, rdv->mois, rdv->annee, rdv->heure, rdv->minute, heureFin, minuteFin);

    fclose(file);

}


void promptDate(int *jour, int *mois, int *annee) {

    // todo: source: http://www.cplusplus.com/reference/ctime/localtime, http://www.cplusplus.com/reference/ctime/tm/
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );


    char tmp;

    int choix = 1;

    printf("1) Aujourd'hui\n2) Demain\n3) Autre chose\n");
    scanf("%d", &choix);


    switch (choix) {

        case 1:
            *jour = timeinfo->tm_mday;
            *mois = timeinfo->tm_mon + 1;
            *annee = timeinfo->tm_year + 1900;
            break;

        case 2:
            *jour = timeinfo->tm_mday + 1;
            *mois = timeinfo->tm_mon + 1;
            *annee = timeinfo->tm_year + 1900;
            break;

        default:
        printf("Date ? (Format : jj/mm/aaaa)\n");
            scanf("%d%c%d%c%d", jour, &tmp, mois, &tmp, annee);

    }
}