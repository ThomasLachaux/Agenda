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

    // todo: passer en dynamique
    int corresps[1000];
    int ncorr = 0;
    
    int i = 0;
    int j = 0;
    int k = 0;

    for (i = 0; i < getSize(rdvs); i++) {
        if(filterRdv(get(rdvs, i).rdv, jour, mois, annee)) {
            
            corresps[ncorr] = i;
            ncorr++;
            
            Rdv rdv = get(rdvs, i).rdv;
            afficherRdv(j + 1, rdv);
            
            j++;
        }
    }

    // Nouveaux rdvs

    printf("=============================");
    printf("\nJournées spéciales:\n");
    // Filtrage des journées spéciales
    for (i = 0; i < specialDaysNbr; i++) {
        if(specialDays[i].day == jour && specialDays[i].month == mois && specialDays[i].year == annee) {
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
                    //newRdvDuJour[id - 1]->value.rdv = nouveauRdv();
                    set(rdvs, corresps[id - 1], fromRdv(nouveauRdv()));

                }

                else if (choix == 2) {
                    printf("Suppression du rendez-vous...\n");
                    //*rdvDuJour[id - 1] = rdvs[*nRdvs - 1];
                    //(*nRdvs)--;
                    pop(rdvs, corresps[id - 1]);
                }

                else if (choix == 3) {
                    printf("Sauvegarde du rendez-vous...\n");
                    Rdv save = get(rdvs, corresps[id - 1]).rdv;
                    sauvegarderRdv(save);
                }
            }

        }
    }
}


void ajouterUnRdv() {
    add(rdvs, fromRdv(nouveauRdv()));
}

Rdv nouveauRdv() {

    char tmp;
    Rdv newRdv;

    promptDate(&newRdv.day, &newRdv.month, &newRdv.year);

    printf("Heure du rendez-vous ? (Format hh:mm)\n");
    scanf("%d%c%d", &newRdv.hour, &tmp, &newRdv.minute);

    printf("Durée du rendez-vous ? (En minutes)\n");
    scanf("%d", &newRdv.duration);

    printf("Nom du rendez-vous ?\n");
    scanf("%s", newRdv.label);

    printf("Lieu du rendez-vous ?\n");
    scanf("%s", newRdv.place);

    printf("Personnes présentes lors du rendez-vous ?\n");
    scanf("%s", newRdv.with);

    return newRdv;
}

// todo: faire téléscopation rdv
void afficherRdv(int id, Rdv rdv) {

    int minuteFin = (rdv.minute + rdv.duration) % 60;
    int heureFin = (rdv.hour * 60 + rdv.minute + rdv.duration) / 60;

    printf("\n%d) "
           " Nom: %s\n"
           "    Date: %02d/%02d/%04d\n"
           "        Heure de debut: %02d:%02d\n"
           "        Heure de fin:   %02d:%02d\n"
           "    Lieu: %s\n"
           "    Personnes présentes: %s\n",
           id, rdv.label,
           rdv.day, rdv.month, rdv.year,
           rdv.hour, rdv.minute, heureFin, minuteFin,
           rdv.place, rdv.with);
}

void sauvegarderRdv(Rdv rdv) {

    FILE *file = NULL;
    char filename[250];


    printf("Nom du ficher ?");
    scanf("%s", filename);
    strcat(filename, ".txt");

    file = fopen(filename, "w");

    int minuteFin = (rdv.minute + rdv.duration) % 60;
    int heureFin = (rdv.hour * 60 + rdv.minute + rdv.duration) / 60;

    fwprintf(file, L"Date de rendez-vous: %02d/%02d/%04d\n"
                  "Heure de debut: %02d:%02d\n"
                  "Heure de fin: %02d:%02d\n",
            rdv.day, rdv.month, rdv.year, rdv.hour, rdv.minute, heureFin, minuteFin);

    fclose(file);
}

// todo: tout passer en anglais
int filterRdv(Rdv rdv, int day, int month, int year) {

    switch (filterMode) {

        // Filtrage par jour
        case 1:
            return rdv.day == day && rdv.month == month && rdv.year == year;

        // Filtrage par semaine
        // Le test de l'année est utilisé dans le cas la semaine se chevauche avec une annee
        case 2:
            return weekNumber(rdv.day, rdv.month, rdv.year) == weekNumber(day, month, year) && abs(rdv.year - year) <= 1;

        // Filtrage par mois
        default:
            return rdv.month == month && rdv.year == year;
    }
}