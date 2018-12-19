/**
 * @file tools.c
 * @authors Thomas de Lachaux
 * @authors Louis Bichet
 * @copyright GNU Public License
 */

#ifndef AGENDA_AGENDA_H
#define AGENDA_AGENDA_H

#include "tools.h"
#include "array.h"

/**
 * Index de l'utilisateur courant dans la liste des utilisateurs
 */
int currentUser;

/**
 * Liste contenant les rendez-vous de l'utilisateur courant
 */
Array *rdvs;

void ajouterUnRdv();
void listerRdvParJour();
void afficherRdv(int id, Rdv rdv);
Rdv nouveauRdv();
void saveRdv(Rdv rdv);
int filterRdv(Rdv rdv, int day, int month, int year);
int collision(Rdv newRdv);
#endif //AGENDA_AGENDA_H
