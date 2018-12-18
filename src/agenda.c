/**
 * @file
 * @brief Répertorie toutes les méthodes pour gérer la prise, modification et supression de rendez-vous
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

/**
 * @brief: Affiche les rendez-vous et les journées spéciales d'une journée selectionnée
 */
void listerRdvParJour() {

    int jour, mois, annee;
    promptDate(&jour, &mois, &annee);

    // todo: passer en dynamique
    int corresps[1000];
    int ncorr = 0;

    int i = 0;
    int j = 0;
    int k = 0;

    // Affiche les rendez-vous filtrées et le stock dans un tableau temporaire
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
    for (i = 0; i < getSize(specialDays); i++) {
        Rdv specialDay = get(specialDays, i).rdv;
        if(specialDay.day == jour && specialDay.month == mois && specialDay.year == annee) {
            displaySpecialDay(k + 1, specialDay);
            k++;
        }
    }

    if(k == 0) {
        printf("Aucune journée spéciale aujourd'hui\n");
    }

    if(j == 0) {
        printf("Aucun rendez-vous ce jour-ci\n");
    }

    else {
        int choix = 0;

        while (choix != 9) {
            printf("\n");
            printChoice(1, "Modifier un rendez-vous");
            printChoice(2, "Supprimer un rendez-vous");
            printChoice(3, "Sauvegarder un rendez-vous");
            printChoice(9, "Menu principal");
            printf("\n");
            inputint(&choix, 0);

            if(choix == 1 || choix == 2 || choix == 3) {
                int id;
                printf("Identifiant du rendez-vous ? (Entre 1 et %d)\n", j);
                inputint(&id, 0);

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

/**
 * Ajoute un nouveau rendez-vous
 * @return Nouveau rendez-vous
 */
Rdv nouveauRdv() {

    char tmp;
    Rdv newRdv;

    promptDate(&newRdv.day, &newRdv.month, &newRdv.year);


    do {
        printf("Heure du rendez-vous ? (Format hh:mm)\n");
        printInputText();
        scanf("%d%c%d", &newRdv.hour, &tmp, &newRdv.minute);
        emptyBuffer();
    }
    while (newRdv.hour >= 24 || newRdv.minute >= 60);


    printf("Durée du rendez-vous ? (En minutes)\n");
    inputint(&newRdv.duration, 1);


    collision();


    printf("Nom du rendez-vous ?\n");
    input(newRdv.label, 99, 1);

    printf("Lieu du rendez-vous ?\n");
    input(newRdv.place, 99, 1);

    printf("Personnes présentes lors du rendez-vous ?\n");
    input(newRdv.with, 99, 1);


    return newRdv;
}

/**
 * @brief Affiche un rendez-vous dans les détails
 * @param id Variable unique par rendez-vous par jour
 * @param rdv Rendez-vous
 */
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


/**
 * @brief Sauvegarde un rendez-vous au format txt. Le nom est demandé par l'utilisateur
 * @param rdv Rendez-vous
 */
void sauvegarderRdv(Rdv rdv) {

    FILE *file = NULL;
    char filename[250];

    printf("Nom du ficher ?");
    input(filename, 250, 1);
    strcat(filename, ".txt");

    file = fopen(filename, "w");

    int minuteFin = (rdv.minute + rdv.duration) % 60;
    int heureFin = (rdv.hour * 60 + rdv.minute + rdv.duration) / 60;

    fwprintf(file, L"Date de rendez-vous: %02d/%02d/%04d\n"
                   "Heure de début: %02d:%02d\n"
                   "Heure de fin: %02d:%02d\n"
                   "Label: %s\n"
                   "Lieu: %s\n"
                   "Personnes présentes: %s\n",
            rdv.day, rdv.month, rdv.year, rdv.hour, rdv.minute, heureFin, minuteFin, rdv.label, rdv.place, rdv.with);

    fclose(file);
}

/**
 * @brief Décide si un rendez-vous fait partie du filtre correspondant
 * @param rdv Rendez-vous
 * @param day Jour du rendez-vous
 * @param month Mois du rendez-vous
 * @param year Année du rendez-vous
 * @return 1 si ça correspond, sinon 0.
 */
 // todo: passer filtermode en paramètre
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

int StartMinute(Rdv rdv) {
    return rdv.hour * 60 + rdv.minute;
}

int EndMinute(Rdv rdv) {
    int minuteFin = (rdv.minute + rdv.duration) % 60;
    int heureFin = (rdv.hour * 60 + rdv.minute + rdv.duration) / 60;

    return heureFin * 60 + minuteFin;
}

int collision(Rdv newRdv) {
    int i;
    Rdv current;
    for(i = 0 ; i < getSize(rdvs) ; i++) {
        current = get(rdvs, i).rdv;
        if(newRdv.day == current.day && newRdv.month==current.month && newRdv.year==current.year &&
        //Cas décalé
        ((StartMinute(newRdv)<= EndMinute(current) && EndMinute(newRdv)>=StartMinute(current)) ||
        //current dans rdv
        (StartMinute(newRdv)>=StartMinute(current) && EndMinute(newRdv)>=EndMinute(current))||
        //rdv dans current
        (StartMinute(newRdv)<=StartMinute(current) && EndMinute(newRdv)<=EndMinute(current)) ) ) {

        }

    }
}