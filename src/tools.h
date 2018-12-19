/**
 * @file
 * @brief Toutes les fonctions annexes aux projet
 * @authors Thomas de Lachaux
 * @authors Louis Bichet
 * @copyright GNU Public License
 */

#ifndef AGENDA_TOOLS_H
#define AGENDA_TOOLS_H

#define printf handlePrint

typedef struct Rdv Rdv;
typedef struct User User;
typedef struct Type Type;
typedef struct Element Element;
typedef struct Array Array;


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
 * @var User::name
 * Nom de l'util    isateur
 * @var User::rdvs
 * Rendez-vous de l'utilisateur
 */


struct User {
    char name[40];
    Array *rdvs;
};

/**
 * @struct Type
 * @brief Types supportés pour la manipulation de listes chainées
 * @var Type::rdv
 * Rendez-vous
 * @var Type::user
 * Utilisateur
 * @var Type::integer
 * Nombre
 */
struct Type {
    Rdv rdv;
    User user;
    int integer;
};


/**
 * @struct Element
 * @brief Element d'une liste chainée
 * @var Element::value
 * Valeur de l'element
 * @var Element::previous
 * Pointeur vers l'element précédent
 * @var Element::next
 * Pointeur vers l'element suivant
 */
struct Element {
    Type value;
    Element *previous;
    Element *next;
};

/**
 * @struct Array
 * @brief Liste chainée
 * @var Array::first
 * Pointeur vers le premier element
 * @var Array::size
 * Taille du tableau
 */
struct Array {
    Element *first;
    int size;
};

/**
 * 0 si en mode console
 * 1 si en mode graphique
 */
int usegui;

void promptDate(int *day, int *month, int *year);
int weekNumber(int day, int month, int year);
void emptyBuffer();
void input(char *string, int length, int inputText);
void inputint(int *integer, int inputText);

//void handlePrint(char *tag, char *attrs, const char * format, ...);
void printChoice(int id, char *value);
void handlePrint(const char *format, ...);
void printInputText();
int getMinutesStart(Rdv rdv);
int getMintesEnd(Rdv rdv);
long getTimestamp(Rdv rdv);
#endif //AGENDA_TOOLS_H
