/**
 * @file
 * @authors Thomas de Lachaux
 * @authors Louis Bichet
 * @copyright GNU Public License
 */

#ifndef AGENDA_ADMINISTRATION_H
#define AGENDA_ADMINISTRATION_H

#include "tools.h"
#include "array.h"

/**
 * Liste contenant tous les utilisateurs
 */
Array *users;

/**
 * Liste contenant les jours spéciaux
 */
Array *specialDays;


/**
 * Mode de filtrage des rendez-vous. 1: filtrage par jour. 2: filtrage par semaine. 3: filtrage par mois
 */
int filterMode;

void administrator();
void newUser();
void listUsers();
Rdv promptSpecialDay();
void listSpecialDays();
void displaySpecialDay(int id, Rdv specialDay);
void setFilterMode();
#endif //AGENDA_ADMINISTRATION_H
