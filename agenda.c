/**
 * @file agenda.c
 * @authors Thomas de Lachaux
 * @authors Louis Bichet
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "agenda.h"
#include "administration.h"
#include "tools.h"



// Bug propre à CLion pour afficher printf dans le debugger
#define printf setbuf(stdout, 0);printf


void listerRdvParJour() {

    int jour, mois, annee;
    promptDate(&jour, &mois, &annee);

    Rdv *rdvDuJour[1000];

    int i = 0;
    int j = 0;
    int k = 0;

    // Filtrage des rendez-vous
    for (i = 0; i < *nRdvs; i++) {
        if(filterRdv(rdvs[i], jour, mois, annee)) {
            rdvDuJour[j] = &rdvs[i];
            afficherRdv(j + 1, rdvDuJour[j]);
            j++;
        }
    }

    printf("\nJournées spéciales:\n");
    // Filtrage des journées spéciales
    for (i = 0; i < specialDaysNbr; i++) {
        if(specialDays[i].jour == jour && specialDays[i].mois == mois && specialDays[i].annee == annee) {
            displaySpecialDay(k + 1, &specialDays[i]);
            k++;
        }
    }

    if(k == 0) {
        printf("Aucune journée spéciale aujourd'hui");
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
                printf("Identifiant du rendez-vous ? (Entre 1 et %d)\n", j);
                scanf("%d", &id);

                if(choix == 1) {
                    printf("Modification du rendez-vous...\n");
                    *rdvDuJour[id - 1] = nouveauRdv();
                }

                else if (choix == 2) {
                    printf("Suppression du rendez-vous...\n");
                    *rdvDuJour[id - 1] = rdvs[*nRdvs - 1];
                    (*nRdvs)--;
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
    rdvs[*nRdvs] = nouveauRdv();
    (*nRdvs)++;
}

Rdv nouveauRdv() {

    char tmp;
    Rdv newRdv;

    promptDate(&newRdv.jour, &newRdv.mois, &newRdv.annee);

    printf("Heure du rendez-vous ? (Format hh:mm)\n");
    scanf("%d%c%d", &newRdv.heure, &tmp, &newRdv.minute);

    printf("Durée du rendez-vous ? (En minutes)\n");
    scanf("%d", &newRdv.duree);

    printf("Nom du rendez-vous ?\n");
    scanf("%s", newRdv.label);

    printf("Lieu du rendez-vous ?\n");
    scanf("%s", newRdv.place);

    printf("Personnes présentes lors du rendez-vous ?\n");
    scanf("%s", newRdv.with);

    return newRdv;
}

// todo: faire téléscopation rdv
void afficherRdv(int id, Rdv *rdv) {

    int minuteFin = (rdv->minute + rdv->duree) % 60;
    int heureFin = (rdv->heure * 60 + rdv->minute + rdv->duree) / 60;

    // todo: terminer ça
    printf("\n%d) "
           "Nom: %s\n"
           "Date: %02d/%02d/%04d\n"
           "   Heure de debut: %02d:%02d\n"
           "   Heure de fin: %02d:%02d\n"
           "Lieu: %s\n"
           "Personnes présentes",
           id, rdv->jour, rdv->mois, rdv->annee, rdv->heure, rdv->minute, heureFin, minuteFin);
}

void sauvegarderRdv(Rdv *rdv) {

    FILE *file = NULL;
    char filename[250];

    printf("Nom du ficher ?");
    scanf("%s", filename);
    strcat(filename, ".txt");

    file = fopen(filename, "w");

    int minuteFin = (rdv->minute + rdv->duree) % 60;
    int heureFin = (rdv->heure * 60 + rdv->minute + rdv->duree) / 60;

    fwprintf(file, L"Date de rendez-vous: %02d/%02d/%04d\n"
                  "Heure de debut: %02d:%02d\n"
                  "Heure de fin: %02d:%02d\n",
            rdv->jour, rdv->mois, rdv->annee, rdv->heure, rdv->minute, heureFin, minuteFin);

    fclose(file);
}

// todo: tout passer en anglais
int filterRdv(Rdv rdv, int day, int month, int year) {

    switch (filterMode) {

        // Filtrage par jour
        case 1:
            return rdv.jour == day && rdv.mois == month && rdv.annee == year;

        // Filtrage par semaine
        // Le test de l'année est utilisé dans le cas la semaine se chevauche avec une annee
        case 2:
            return weekNumber(rdv.jour, rdv.mois, rdv.annee) == weekNumber(day, month, year) && abs(rdv.annee - year) <= 1;

        // Filtrage par mois
        default:
            return rdv.mois == month && rdv.annee == year;
    }
}