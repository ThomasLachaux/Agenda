//
// Created by Thomas on 30-Sep-18.
//

#ifndef AGENDA_ADMINISTRATION_H
#define AGENDA_ADMINISTRATION_H

#include "tools.h"

User users[9];
int usrNbr;

Rdv specialDays[1000];
int specialDaysNbr;

void administrator();
void newUser();
void listUsers();
Rdv addSpecialDay();
void listSpecialDays();
void displaySpecialDay(int id, Rdv *specialDay);
#endif //AGENDA_ADMINISTRATION_H
