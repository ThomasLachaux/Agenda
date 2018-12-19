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

    Array *newCorresp = initArray();

    int i = 0;
    int j = 0;
    int k = 0;

    sortArrayByStartHour(rdvs);

    // Affiche les rendez-vous filtrées et le stock dans un tableau temporaire
    for (i = 0; i < getSize(rdvs); i++) {
        if (filterRdv(get(rdvs, i).rdv, jour, mois, annee)) {

            add(newCorresp, fromInt(i));

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
        if (specialDay.day == jour && specialDay.month == mois && specialDay.year == annee) {
            displaySpecialDay(k + 1, specialDay);
            k++;
        }
    }

    if (k == 0) {
        printf("Aucune journée spéciale aujourd'hui\n");
    }

    if (j == 0) {
        printf("Aucun rendez-vous ce jour-ci\n");
    } else {
        int choix = 0;

        while (choix != 9) {
            printf("\n");
            printChoice(1, "Modifier un rendez-vous");
            printChoice(2, "Supprimer un rendez-vous");
            printChoice(3, "Sauvegarder un rendez-vous");
            printChoice(9, "Menu principal");
            printf("\n");
            inputint(&choix, 0);

            if (choix == 1 || choix == 2 || choix == 3) {
                int id;
                printf("Identifiant du rendez-vous ? (Entre 1 et %d)\n", j);
                inputint(&id, 0);

                int correctId = get(newCorresp, id - 1).integer;

                if (choix == 1) {
                    printf("Modification du rendez-vous...\n");

                    // Modification un peu bourrinne, mais permet d'éviter un bug de collision non existant
                    Rdv tmp = get(rdvs, correctId).rdv;
                    tmp.year = 0;
                    set(rdvs, correctId, fromRdv(tmp));

                    // Vrai modificaition du rendez-vous
                    set(rdvs, correctId, fromRdv(nouveauRdv()));

                } else if (choix == 2) {
                    printf("Suppression du rendez-vous...\n");
                    pop(rdvs, correctId);
                } else if (choix == 3) {
                    printf("Sauvegarde du rendez-vous...\n");
                    Rdv save = get(rdvs, correctId).rdv;
                    saveRdv(save);
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

    do {
        promptDate(&newRdv.day, &newRdv.month, &newRdv.year);


        do {
            printf("Heure du rendez-vous ? (Format hh:mm)\n");
            printInputText();
            scanf("%d%c%d", &newRdv.hour, &tmp, &newRdv.minute);
            emptyBuffer();
        } while (newRdv.hour >= 24 || newRdv.minute >= 60);


        printf("Durée du rendez-vous ? (En minutes)\n");
        inputint(&newRdv.duration, 1);

    } while (collision(newRdv));


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
void saveRdv(Rdv rdv) {

    FILE *file = NULL;
    char filename[250];

    printf("Nom du ficher ?");
    input(filename, 250, 1);
    strcat(filename, ".txt");

    file = fopen(filename, "w");

    int minuteFin = (rdv.minute + rdv.duration) % 60;
    int heureFin = (rdv.hour * 60 + rdv.minute + rdv.duration) / 60;

    // todo: corriger bug label !!!!!!!!!!!!!
    fprintf(file, "Label: %s\n"
                   "Date de rendez-vous: %02d/%02d/%04d\n"
                   "Heure de début: %02d:%02d\n"
                   "Heure de fin: %02d:%02d\n"
                   "Lieu: %s\n"
                   "Personnes présentes: %s\n",
                   rdv.label, rdv.day, rdv.month, rdv.year, rdv.hour, rdv.minute, heureFin, minuteFin, rdv.place, rdv.with);


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
            return weekNumber(rdv.day, rdv.month, rdv.year) == weekNumber(day, month, year) &&
                   abs(rdv.year - year) <= 1;

            // Filtrage par mois
        default:
            return rdv.month == month && rdv.year == year;
    }
}

/**
 * Vérifie s'il y a une superposition de rendez-vous et propose différentes solutions à l'utilisateurs
 * @param newRdv Rendez-vous
 * @return 0 (si le nouveau rendez-vous n'est pas modifié) ou 1 (dans le cas contraire)
 */

int collision(Rdv newRdv) {
    int i, choice;
    Rdv current;
    for (i = 0; i < getSize(rdvs); i++) {
        current = get(rdvs, i).rdv;
        if (newRdv.day == current.day && newRdv.month == current.month && newRdv.year == current.year &&
            //Cas décalé
            ((getMinutesStart(newRdv) <= getMintesEnd(current) && getMintesEnd(newRdv) >= getMinutesStart(current)) ||
             //current dans rdv
             (getMinutesStart(newRdv) >= getMinutesStart(current) && getMintesEnd(newRdv) <= getMintesEnd(current)) ||
             //rdv dans current
             (getMinutesStart(newRdv) <= getMinutesStart(current) && getMintesEnd(newRdv) >= getMintesEnd(current)))) {

            printf("Vous avez déjà un rendez-vous : \n");
            afficherRdv(0, current);
            printf("\nQue voulez-vous faire ?\n");
            do {
                printChoice(1, "Modifier le nouveau rendez-vous");
                printChoice(2, "Modifier l'ancien rendez-vous");
                printChoice(3, "Supprimer l'ancien rendez-vous");

                inputint(&choice, 1);

            }while(choice < 1 || choice  > 3);

            switch (choice){
                case 1 :
                    return 1;

                case 2:
                    set(rdvs, i, fromRdv(nouveauRdv()));
                    printf("\nAncien rendez-vous modifié...\nFinalisation du nouveau rendez-vous...\n");
                    return 0;

                case 3:
                    pop(rdvs, i);
                    printf("\nAncien rendez-vous supprimé...\nFinalisation du nouveau rendez-vous...\n");
                    return 0;
            }
        }

    }
    return 0;
}