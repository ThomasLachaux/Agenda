//
// Created by Thomas on 30-Sep-18.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "agenda.h"
#include "tools.h"

// Bug propre à CLion pour afficher printf dans le debugger
#define printf setbuf(stdout, 0);printf

void listerRdvParJour() {

    int jour, mois, annee;
    promptDate(&jour, &mois, &annee);

    Rdv *rdvDuJour[1000];

    int i = 0;
    int j = 0;

    // Filtrage des rendez-vous
    for (i = 0; i < *nRdvs; i++) {
        if(rdvs[i].jour == jour && rdvs[i].mois == mois && rdvs[i].annee == annee) {
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
                printf("Identifiant du rendez-vous ? (Etre 1 et %d)\n", j);
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

    printf("Duree du rendez-vous ?\n");
    scanf("%d", &newRdv.duree);

    return newRdv;
}

void afficherRdv(int id, Rdv rdv) {

    int minuteFin = (rdv.minute + rdv.duree) % 60;
    int heureFin = (rdv.heure * 60 + rdv.minute + rdv.duree) / 60;

    printf("\n%d) "
           "Date de rendez-vous: %02d/%02d/%04d\n"
           "   Heure de debut: %02d:%02d\n"
           "   Heure de fin: %02d:%02d\n",
           id, rdv.jour, rdv.mois, rdv.annee, rdv.heure, rdv.minute, heureFin, minuteFin);
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

    fprintf(file, "Date de rendez-vous: %02d/%02d/%04d\n"
                  "Heure de debut: %02d:%02d\n"
                  "Heure de fin: %02d:%02d\n",
            rdv->jour, rdv->mois, rdv->annee, rdv->heure, rdv->minute, heureFin, minuteFin);

    fclose(file);

}