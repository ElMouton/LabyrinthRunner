/**
 * @file data.h
 * @brief Fichier regroupant les en-tête des fonctions qui change les données de jeu
 * @author GONTHIER Dimitri
 * @author HERTER Julian
*/

#ifndef data_h
#define data_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

void saveMap(char nomFichier[15]);

void supprimerDoss(char nomFichier[17]);

void change_map(char nom_Map[28], int coef);

void creerFichierSave(char *nomFichier, char nomMap[28], int posX, int posY, int nbCle, int aEpee);

char* setMap(char *nomFichier);
int setPosX(char *nomFichier);
int setPosY(char *nomFichier);
int setnbCle(char *nomFichier);
bool setEpee(char *nomFichier);

#endif