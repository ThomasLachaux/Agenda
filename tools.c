//
// Created by Thomas on 30-Sep-18.
//

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "tools.h"

// Bug propre à CLion pour afficher printf dans le debugger
#define printf setbuf(stdout, 0);printf

void promptDate(int *jour, int *mois, int *annee) {

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
            *jour = timeinfo->tm_mday;
            *mois = timeinfo->tm_mon + 1;
            *annee = timeinfo->tm_year + 1900;
            break;

        case 2:
            *jour = timeinfo->tm_mday + 1;
            *mois = timeinfo->tm_mon + 1;
            *annee = timeinfo->tm_year + 1900;
            break;

        default:
            printf("Date ? (Format : jj/mm/aaaa)\n");
            scanf("%d%c%d%c%d", jour, &tmp, mois, &tmp, annee);

    }
}

int weekNumber(Rdv *rdv) {

    struct tm date = {0};

    date.tm_year = rdv->annee + 1900;
    date.tm_mon = rdv->mois - 1;
    date.tm_mday = rdv->jour;

    // todo: source https://www.codeproject.com/Questions/592534/HelpplustoplusfindoutplusWeekplusnumberplusofplusy
    // todo: autheur Ian A Davidson 14-May-13 22:40pm

    int monToSun = (date.tm_wday == 0) ? 7 : date.tm_wday; // Passe le lundi en premier jour de la semaine
    int week = ((date.tm_yday + 8 - monToSun) / 7);

    return week;

}