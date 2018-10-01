//
// Created by Thomas on 30-Sep-18.
//

#ifndef AGENDA_TOOLS_H
#define AGENDA_TOOLS_H

int i;

typedef struct Rdv Rdv;
struct Rdv {
    char label[40];
    int annee;
    int mois;
    int jour;
    int heure;
    int minute;
    int duree;
};

typedef struct User User;
struct User {
    int nRdvs;
    char nom[40];
    Rdv rdvs[1000];
};

void promptDate(int *jour, int *mois, int *annee);
#endif //AGENDA_TOOLS_H
