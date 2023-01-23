/**
 * @file fonctions_SDL.h
 * @brief Fichier regroupant les en-tête des fonctions qui permettent d'utiliser la bibliothèque SDL2
 * @author GONTHIER Dimitri
 * @author HERTER Julian
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

SDL_Texture* charger_image (const char* nomfichier, SDL_Renderer* renderer);
SDL_Texture* charger_image_transparente(const char* nomfichier, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b);
SDL_Texture* charger_texte(const char* message, SDL_Renderer* renderer, TTF_Font *font, SDL_Color color) ;