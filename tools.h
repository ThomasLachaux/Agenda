/**
 * @file tools.h
 * @authors Thomas de Lachaux
 * @authors Louis Bichet
 * @copyright GNU Public License
 */

#ifndef AGENDA_TOOLS_H
#define AGENDA_TOOLS_H

typedef struct Rdv Rdv;
struct Rdv {
    char label[100];
    int annee;
    int mois;
    int jour;
    int heure;
    int minute;
    int duree;
    char place[100];
    char with[100];
};

typedef struct User User;
struct User {
    int nRdvs;
    char nom[40];
    Rdv rdvs[1000];
};

void promptDate(int *jour, int *mois, int *annee);
int weekNumber(int day, int month, int year);
#endif //AGENDA_TOOLS_H
