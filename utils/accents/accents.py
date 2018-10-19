# coding: utf8

##
# @file accents.py
# @brief Encode et décode les accents du projet en ASCII Etendu
# @authors Thomas de Lachaux
# @authors Louis Bichet
# @copyright GNU Public License
# @warning Le dossier courant du terminal doit être celui du script python.
# @warning Il faut pouvoir executer dans le terminal python accents.py

from sys import argv

# Table des correspondances:
# Correspond à la table ASCII étendue en octal (https://bit.ly/2pZ9gYG)
# é: é
# à: \205
# ç: \207
# ê: \210
# è: \212
# À: \267
# ô: \223

##
# @var files
# @brief Liste des fichiers destinées à être enocdés/décodés

files = ['main.c', 'agenda.c', 'agenda.h', 'administration.c', 'administration.h', 'tools.c', 'tools.h']

##
# @var srcDirectory
# @brief Source des fichiers (en chemin absolu)

srcDirectory = "../../src/"

##
# @var mapping
# @brief Liste à 2 dimensions décrivant les correspondances UTF-8 et ASCII Etendu


mapping = [
    ['é', '\\202'],
    ['à', '\\205'],
    ['ç', '\\207'],
    ['ê', '\\210'],
    ['è', '\\212'],
    ['À', '\\267'],
    ['ô', '\\223']
]


## Ouvre un fichier, remplace des caractères par d'autres et l'écrit dans le fichier
# @param path chemin vers le ficher
# @param mapping table des correspondances entre l'UTF et l'ASCII Etendu
# @param reverse si false: l'UTF remplace l'ASCII. Sinon inverse le résultat

def find_and_replace(path, mapping, reverse):
    with open(path, 'r', encoding='utf8') as file:
        filedata = file.read()

    for chars in mapping:
        if reverse is True:
            filedata = filedata.replace(chars[0], chars[1])

        else:
            filedata = filedata.replace(chars[1], chars[0])

    with open(path, 'w', encoding='utf8') as file:
        file.write(filedata)


## Point d'entrée de l'application. Determine si il faut encode ou décoder les caratères en fonctions des args
# @throw ValueError en cas d'arguments invalides, trop nombreux ou insuffisants

def main():
    if len(argv) != 2:
        raise ValueError('Too much/few arguments expected')

    if argv[1] == 'encode':
        reverse = True

    elif argv[1] == 'decode':
        reverse = False

    else:
        raise ValueError('Bad argument')

    for file in files:
        find_and_replace(srcDirectory + file, mapping, reverse)


if __name__ == '__main__':
    main()
