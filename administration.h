//
// Created by Thomas on 30-Sep-18.
//

#ifndef AGENDA_ADMINISTRATION_H
#define AGENDA_ADMINISTRATION_H

#include "tools.h"

struct User users[9];
int usrNbr;

struct Rdv specialDays[1000];
int specialDaysNbr;

void administrator();
void newUser();
void listUsers();
struct Rdv addSpecialDay();
void listSpecialDays();
#endif //AGENDA_ADMINISTRATION_H
