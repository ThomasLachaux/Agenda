//
// Created by Thomas on 30-Sep-18.
//

#ifndef AGENDA_AGENDA_H
#define AGENDA_AGENDA_H

#include "tools.h"

int currentUser;
int *nRdvs;
struct Rdv *rdvs;

void ajouterUnRdv();
void listerRdvParJour();
void afficherRdv(int id, struct Rdv rdv);
struct Rdv nouveauRdv();
void sauvegarderRdv(struct Rdv *rdv);
#endif //AGENDA_AGENDA_H
