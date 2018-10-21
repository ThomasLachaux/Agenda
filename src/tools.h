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
 * Nom du rendez-vous
 * @var Rdv::year
 * Année du rendez-vous
 * @var Rdv::month
 * Mois du rendez-vous
 * @var Rdv::day
 * Jour du rendez-vous
 * @var Rdv::hour
 * Heure du rendez-vous
 * @var Rdv::minute
 * Minute du rendez-vous
 * @var Rdv::duration
 * Durée du rendez-vous
 * @var Rdv::place
 * Lieu du rendez-vous
 * @var Rdv::with
 * Personnes présentes au rendez-vous
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

/**
 * @struct User
 * @brief Structure utilisateur
 * @var User::nRdvs
 * Nombre de rendez-vous
 * @var User::name
 * Nom de l'utilisateur
 * @var User::rdvs
 * Rendez-vous de l'utilisateur
 */

typedef struct User User;
struct User {
    int nRdvs;
    char name[40];
    Rdv rdvs[1000];
};

void promptDate(int *day, int *month, int *year);
int weekNumber(int day, int month, int year);
void displayDailyRdv(Rdv *rdv, int size);
#endif //AGENDA_TOOLS_H
