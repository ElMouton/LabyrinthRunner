/**
 * @file musics.h
 * @brief Fichier regroupant les en-têtes des fonctions qui font du son
 * @author GONTHIER Dimitri
 * @author HERTER Julian
*/
#ifndef music_h
#define music_h

#include <SDL2/SDL_mixer.h>

void porte(); //Bruit de porte

void coffre(); // Bruit d'ouverture de coffre

void step(); //Bruit de pas

void sword(); //Bruit d'épée lorsque le perso la prend

void teleporteur(); //Bruit du téléporteur

void activateur(); // Bruit de l'activateur

void pierre(); // Bruit de pierre qui se casse

void hurt(); //Bruit du perso qui se fait attaquer

void coup_epee1(); // 1er bruit du perso qui attaque

void coup_epee2(); // 2eme bruit du perso qui attaque

#endif
