/**
 * @file fonctions_SDL.c
 * @brief Fichier regroupant les corps des fonctions qui permettent d'utiliser la bibliothèque SDL2
 * @author GONTHIER Dimitri
 * @author HERTER Julian
*/

#include "fonctions_SDL.h"

/**
 * \fn SDL_Texture* charger_image (const char* nomfichier, SDL_Renderer* renderer)
 * \brief Permet de charger une image dans un renderer
 * 
 * \return La texture chargée
*/
SDL_Texture* charger_image (const char* nomfichier, SDL_Renderer* renderer){
    SDL_Surface* surface = SDL_LoadBMP(nomfichier);
    return SDL_CreateTextureFromSurface(renderer, surface);
}

/**
 * \fn SDL_Texture* charger_image_transparente(const char* nomfichier, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b)
 * \brief Permet de charger une image transparente dans un renderer
 * 
 * \return La texture chargée
*/
SDL_Texture* charger_image_transparente(const char* nomfichier, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b){
    SDL_Surface* surface = SDL_LoadBMP(nomfichier);
    Uint32 key = SDL_MapRGB(surface->format, r, g, b);
    
    SDL_SetColorKey(surface, SDL_TRUE, key);
    return SDL_CreateTextureFromSurface(renderer, surface);
}

/**
 * \fn SDL_Texture* charger_texte(const char* message, SDL_Renderer* renderer, TTF_Font *font, SDL_Color color)
 * \brief Permet de charger une texture avec un texte dans un renderer
 * 
 * \return La texture avec le texte chargée
*/
SDL_Texture* charger_texte(const char* message, SDL_Renderer* renderer, TTF_Font *font, SDL_Color color){
    SDL_Surface* texte = TTF_RenderText_Solid(font, message, color);
    return SDL_CreateTextureFromSurface(renderer, texte);
}