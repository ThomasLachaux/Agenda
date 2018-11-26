/**
 * @file administration.h
 * @authors Thomas de Lachaux
 * @authors Louis Bichet
 * @copyright GNU Public License
 */

#ifndef AGENDA_ADMINISTRATION_H
#define AGENDA_ADMINISTRATION_H

#include "tools.h"
#include "array.h"

Array *newUsers;

Rdv specialDays[1000];
int specialDaysNbr;


// todo: passer en enumeration
int filterMode;

void administrator();
void newUser();
void listUsers();
Rdv promptSpecialDay();
void listSpecialDays();
void displaySpecialDay(int id, Rdv *specialDay);
#endif //AGENDA_ADMINISTRATION_H
