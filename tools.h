/**
 * @file tools.h
 * @authors Thomas de Lachaux
 * @authors Louis Bichet
 * @copyright GNU Public License
 */

#ifndef AGENDA_TOOLS_H
#define AGENDA_TOOLS_H

/**
 * @struct Rdv
 * @brief Structure rendez-vous
 * @var Rdv::label
 * Nom du rdv
 */

typedef struct Rdv Rdv;
struct Rdv {
    char label[100];
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int duration;
    char place[100];
    char with[100];
};

typedef struct User User;
struct User {
    int nRdvs;
    char name[40];
    Rdv rdvs[1000];
};

void promptDate(int *day, int *month, int *year);
int weekNumber(int day, int month, int year);
#endif //AGENDA_TOOLS_H
