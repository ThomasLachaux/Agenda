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
#define printf setbuf(stdout, 0);printf

/**
 * @brief Propose date de rendez-vous et éventuellement récupère la date d'aujourd'hui ou de demain
 * @param day jour
 * @param month mois
 * @param year année
 */
// todo: atof atol atoi
void promptDate(int *day, int *month, int *year) {

    // todo: source: http://www.cplusplus.com/reference/ctime/localtime, http://www.cplusplus.com/reference/ctime/tm/
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);


    char tmp;

    int choix = 1;

    do {
        printf("1) Aujourd'hui\n2) Demain\n3) Autre chose\n");
        scanf("%d", &choix);
    } while (choix < 1 || choix > 3);

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

void emptyBuffer() {
    int c = 0;
    while(c != '\n' && c != EOF) {
        c = getchar();
    }
}
// todo: ajouter free pour les listes chainées

void input(char *string, int length) {
    char *first = NULL;

    if (fgets(string, length, stdin) != NULL) {
        first = strchr(string, '\n');
        if (first != NULL) {
            *first = '\0';
        } else {
            emptyBuffer();
        }

    } else {
        emptyBuffer();
        printf("Erreur dans la saisie :/");
    }
}

void inputi(int *integer) {
    char tmp[10];
    input(tmp, 9);
    *integer = atoi(tmp);
}

