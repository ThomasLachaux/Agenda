//
// Created by Thomas on 30-Sep-18.
//

#ifndef AGENDA_TOOLS_H
#define AGENDA_TOOLS_H

int i;

struct Rdv {
    int annee;
    int mois;
    int jour;
    int heure;
    int minute;
    int duree;
};

struct User {
    int nRdvs;
    char nom[40];
    struct Rdv rdvs[1000];
};

void promptDate(int *jour, int *mois, int *annee);
#endif //AGENDA_TOOLS_H
