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
 * Propose date de rendez-vous et éventuellement récupère la date d'aujourd'hui ou de demain
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

/**
 * Vide le buffer du stdin
 */
void emptyBuffer() {
    int c = 0;
    while(c != '\n' && c != EOF) {
        c = getchar();
    }
}

/**à
 * Assigne à une variable par référence les données entrées par le clavier
 * @param string variable par référence
 * @param length longueur de la variable
 * @param inputText 1 si il faut faire apparaitre un champ en mode graphique. Sinon 0
 */
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

/**
 * Récupère les données entrée au clavier en tant que nombre
 * @param integer valeur par référence
 * @param inputText 1 si il faut faire apparaitre un champ en mode graphique. Sinon 0
 */
void inputint(int *integer, int inputText) {
    char tmp[10];
    input(tmp, 9, inputText);
    *integer = atoi(tmp);
}

/**
 * Grace au define, les appels de printf sont remplacés par l'appel de cette fonction.
 * Vide le buffer en cas d'uilisation en interface après l'appel du printf.
 * @param format format des données
 * @param ... arguments
 */
void handlePrint(const char *format, ...) {

    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);

    if(usegui)
        fflush(stdout);
}

/**
 * En mode console: affiche un choix de façon formatée
 * En mode interface: affiche un choix sous forme de bouton
 */
void printChoice(int id, char *value) {
    if(usegui)
        printf("<button value=\"%d\">%s</button>", id, value);

    else
        printf("%d) %s\n", id, value);
}

/**
 * En mode interface: affiche un champ
 */
void printInputText() {
    if(usegui)
        printf("<form method=\"get\" action=\"\" class=\"form-group\">"
                   "<input type=\"text\" class=\"input form-control\"/>"
               "</form>");
}