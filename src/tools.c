/**
 * @file tools.c
 * @authors Thomas de Lachaux
 * @authors Louis Bichet
 * @copyright GNU Public License
 */

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tools.h"

// Bug propre à CLion pour afficher printf dans le debugger
//#define printf setbuf(stdout, 0);printf

/**
 * @brief Propose date de rendez-vous et éventuellement récupère la date d'aujourd'hui ou de demain
 * @param day jour
 * @param month mois
 * @param year année
 */

void promptDate(int *day, int *month, int *year) {

    // todo: source: http://www.cplusplus.com/reference/ctime/localtime, http://www.cplusplus.com/reference/ctime/tm/
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);


    char tmp;

    int choix = 1;

    printf("1) Aujourd'hui\n2) Demain\n3) Autre chose\n");
    scanf("%d", &choix);


    switch (choix) {

        case 1:
            *day = timeinfo->tm_mday;
            *month = timeinfo->tm_mon + 1;
            *year = timeinfo->tm_year + 1900;
            break;

        case 2:
            *day = timeinfo->tm_mday + 1;
            *month = timeinfo->tm_mon + 1;
            *year = timeinfo->tm_year + 1900;
            break;

        default:
        printf("Date ? (Format : jj/mm/aaaa)\n");
            scanf("%d%c%d%c%d", day, &tmp, month, &tmp, year);

    }
}

/**
 * @brief Conversion données horaires en numéro de semaine
 * @param day jour
 * @param month mois
 * @param year année
 * @return le numéro de semaine
 */

int weekNumber(int day, int month, int year) {

    struct tm date = {0};

    date.tm_year = year + 1900;
    date.tm_mon = month - 1;
    date.tm_mday = day;

    // todo: source https://www.codeproject.com/Questions/592534/HelpplustoplusfindoutplusWeekplusnumberplusofplusy
    // todo: autheur Ian A Davidson 14-May-13 22:40pm

    int monToSun = (date.tm_wday == 0) ? 7 : date.tm_wday; // Passe le lundi en premier jour de la semaine
    int week = ((date.tm_yday + 8 - monToSun) / 7);

    return week;
}


void println(char c) {
    int width = 103;
    int i;
    for (i = 0; i < width; i++) {
        printf("%c", c);
    }
    printf("\n");
}

// todo: passer en tableau dynamique
// todo: ATTENTION LES RENDEZ VOUS DOIVENT ETRE TRIES !!!!!!!!!!!!!
/**
 * @brief Affiche les rendez-vous du jour dans un tableau en ASCII
 *
 */
void displayDailyRdv(Rdv *rdv, int size) {

    // Calcul de la taille maximale
    int i;
    int maxize = 0;

    for (i = 0; i < size; i++)
        maxize = (int) (strlen(rdv[i].label) > maxize ? strlen(rdv[i].label) : maxize);

    int hour;
    int minute;
    int endhour;
    int endminute;

    i = 0;

    int csize = 4;
    int csel = 0;
    // todo: \256: ×
    // todo: \372 ·
    char c[4] = {'*', (char) '\236', (char) '\372', '+'};


    println('_');
    for (hour = 0; hour < 24; hour++) {

        println('-');

        if (hour < 10) {
            printf("|  %dh | ", hour);
        } else {
            printf("| %dh | ", hour);
        }


        for (minute = 0; minute < 60; minute++) {

            endminute = (rdv[i].minute + rdv[i].duration) % 60;
            endhour = (rdv[i].hour * 60 + rdv[i].minute + rdv[i].duration) / 60;

            if (minute % 5 == 0 && minute != 0) {
                printf(" | ");
            }

            if (hour < rdv[i].hour || hour > endhour)
                printf("%c", ' ');

            else {

                if (minute < rdv[i].minute && hour == rdv[i].hour) {
                    printf("%c", ' ');

                } else if (minute > endminute - 1 && hour == endhour) {
                    printf("%c", ' ');
                } else {
                    printf("%c", c[csel]);

                    if(minute == endminute - 1 && i < size) {
                        i++;
                        csel = (csel + 1) % csize;
                    }

                }
            }
        }

        printf(" |\n");
    }

    // todo : mettre dans accents.py
    println((char) '\356');
}

void displayWeeklyRdv(Rdv *rdv) {

}

