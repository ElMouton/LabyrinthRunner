/**
 * @file fonctions_fichiers.h
 * @brief Fichier regroupant les en-tête des fonctions qui permettent d'utiliser un tableau à 2 dimensions et un fichier texte
 * @author GONTHIER Dimitri
 * @author HERTER Julian
*/

#include <stdio.h>
#include <stdlib.h>

char** allouer_tab_2D(int n, int m);
void desallouer_tab_2D(char** tab, int n);
void afficher_tab_2D(char** tab, int n, int m);
void taille_fichier(const char* nomFichier, int* nbLig, int* nbCol);
char** lire_fichier(const char* nomFichier);

char** modifier_caractere(char** tab, int n, int m, char ancien, char nouveau);
void ecrire_fichier(const char* nomFichier, char** tab, int n, int m);