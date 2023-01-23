/**
 * @file graphics.h
 * @brief Fichier regroupant les en-tête des fonctions qui montre ce qu'il y a à l'écran
 * @author GONTHIER Dimitri
 * @author HERTER Julian
*/
#ifndef graphics_h
#define graphics_h

#include "define.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

void affiche_nbCle(SDL_Renderer *renderer, int nbCle);

void afficherTextMenu(SDL_Renderer *renderer, char* texte, int emplacement, int r, int g, int b);
void afficherMenu(SDL_Renderer *renderer);

void afficherTexteAide(SDL_Renderer *renderer);
void afficherRetourAide(SDL_Renderer *renderer);

void affiche_nbPv(SDL_Renderer *renderer, int nbPv);

void textePause(SDL_Renderer *renderer, char* texte, int p);
void afficherPause(SDL_Renderer *renderer);

void texteGameOver(SDL_Renderer *renderer, char* texte, int p);
void afficheGameOver(SDL_Renderer* renderer);

void texteWin(SDL_Renderer *renderer, char* texte, int p);
void afficheWin(SDL_Renderer* renderer);

#endif