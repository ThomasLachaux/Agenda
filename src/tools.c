/**
 * @file tools.c
 * @authors Thomas de Lachaux
 * @authors Louis Bichet
 * @copyright GNU Public License
 */

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <rpc.h>
#include "tools.h"


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

    do {
        printChoice(1, "Aujourd'hui");
        printChoice(2, "Demain");
        printChoice(3, "Autre chose");
        printf("\n");
        inputint(&choix, 0);
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

void input(char *string, int length, int inputText) {

    if(inputText)
        printInputText();

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

void inputint(int *integer, int inputText) {
    char tmp[10];
    input(tmp, 9, inputText);
    *integer = atoi(tmp);
}

void handlePrint(const char *format, ...) {

    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);

    if(usegui)
        fflush(stdout);
}

/**
 * Print list of buttons
 */
void printChoice(int id, char *value) {
    if(usegui) {
        printf("<button value=\"%d\">%s</button>", id, value);
    }

    else {
        printf("%d) %s\n", id, value);
    }
}

void printInputText() {
    if(usegui)
        printf("<form method=\"post\" action=\"\" class=\"form-group\">"
                   "<input type=\"text\" class=\"input form-control\"/>"
               "</form>");
}