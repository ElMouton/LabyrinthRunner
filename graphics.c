/**
 * @file graphics.c
 * @brief Fichier regroupant les corps des fonctions qui montre ce qu'il y a à l'écran
 * @author GONTHIER Dimitri
 * @author HERTER Julian
*/
#include "graphics.h"

/**
 * \fn void affiche_nbCle(SDL_Renderer *renderer, int nbCle)
 * \brief Affiche le nombre de clés possédés en haut à droite de l'écran
*/
void affiche_nbCle(SDL_Renderer *renderer, int nbCle){

    TTF_Init();

    TTF_Font* Font = TTF_OpenFont("Ressources/Mustard_Smile.ttf", 50); //Récupére la police + initialise sa taille

    //Couleur de la police
    SDL_Color TextColor;
    TextColor.r = 255;
    TextColor.g = 255;
    TextColor.b = 0;

    char affiche[100];
	sprintf(affiche, "Cle : %d", nbCle); //Stocke la chaîne de caractère + la valeur de nbCle

    SDL_Surface* TextSurface = TTF_RenderText_Solid(Font, affiche, TextColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, TextSurface);

    SDL_Rect DstRect;
    DstRect.x = TAILLEFENETREX - 160;
    DstRect.y = 10;
    DstRect.w = TextSurface->w;
    DstRect.h = TextSurface->h;

    SDL_RenderCopy(renderer, texture, NULL, &DstRect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(TextSurface);
    TTF_CloseFont(Font);
    TTF_Quit();
}

void afficherTextMenu(SDL_Renderer *renderer, char* texte, int emplacement, int r, int g, int b){
    TTF_Init();

    TTF_Font* Font = TTF_OpenFont("Ressources/Mustard_Smile.ttf", 50); //Récupére la police + initialise sa taille

    //Couleur de la police
    SDL_Color TextColor;
    TextColor.r = r;
    TextColor.g = g;
    TextColor.b = b;
    TextColor.a = 0;

    SDL_Surface* TextSurface = TTF_RenderText_Solid(Font, texte, TextColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, TextSurface);

    int tailleX, tailleY;
    SDL_QueryTexture(texture, NULL, NULL, &tailleX, &tailleY);
    int espacement = (-4*tailleY + TAILLEFENETREY)/5;

    SDL_Rect DstRect;
    DstRect.x = TAILLEFENETREX/2 - tailleX/2;
    DstRect.y = (emplacement+1)*espacement + emplacement * tailleY;
    DstRect.w = TextSurface->w;
    DstRect.h = TextSurface->h;

    SDL_RenderCopy(renderer, texture, NULL, &DstRect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(TextSurface);
    TTF_CloseFont(Font);
    TTF_Quit();
}

void afficherMenu(SDL_Renderer *renderer){
    afficherTextMenu(renderer, "Labyrinthe Runner !", 0, 0, 0, 255);
    afficherTextMenu(renderer, "Jouer", 1, 0, 0, 255);
    afficherTextMenu(renderer, "Aide", 2, 0, 255, 0);
    afficherTextMenu(renderer, "Quitter", 3, 255, 0, 0);
}

void afficherTexteAide(SDL_Renderer *renderer){
    TTF_Init();

    TTF_Font* Font = TTF_OpenFont("Ressources/Mustard_Smile.ttf", 50); //Récupére la police + initialise sa taille

    //Couleur de la police
    SDL_Color TextColor;
    TextColor.r = 0;
    TextColor.g = 255;
    TextColor.b = 0;
    TextColor.a = 0;

    for (int i = 0; i < 4; i++)
    {
        SDL_Surface* TextSurface;
        SDL_Texture* texture;
        switch (i)
        {
        case 0:
            TextSurface = TTF_RenderText_Solid(Font, "Appuyer sur 'z', 'q', 's' et 'd' pour bouger.", TextColor);
            texture = SDL_CreateTextureFromSurface(renderer, TextSurface);
            break;
        
        case 1:
            TextSurface = TTF_RenderText_Solid(Font, "Appuyer sur 'e' pour interagir.", TextColor);
            texture = SDL_CreateTextureFromSurface(renderer, TextSurface);
            break;
        
        case 2:
            TextSurface = TTF_RenderText_Solid(Font, "Appuyer sur 'a' pour utiliser l'epee.", TextColor);
            texture = SDL_CreateTextureFromSurface(renderer, TextSurface);
            break;

        case 3:
            TextSurface = TTF_RenderText_Solid(Font, "Appuyer sur 'p' pour mettre en pause.", TextColor);
            texture = SDL_CreateTextureFromSurface(renderer, TextSurface);
            break;
            
        default:
            break;
        }

        int tailleX, tailleY;
        SDL_QueryTexture(texture, NULL, NULL, &tailleX, &tailleY);

        SDL_Rect DstRect;
        DstRect.x = TAILLEFENETREX/2 - tailleX/2;
        DstRect.y = i*tailleY + (i+1)*100;
        DstRect.w = TextSurface->w;
        DstRect.h = TextSurface->h;

        SDL_RenderCopy(renderer, texture, NULL, &DstRect);

        SDL_DestroyTexture(texture);
        SDL_FreeSurface(TextSurface);
    }
    
    TTF_CloseFont(Font);
    TTF_Quit();
}

void afficherRetourAide(SDL_Renderer *renderer){
    TTF_Init();

    TTF_Font* Font = TTF_OpenFont("Ressources/Mustard_Smile.ttf", 50); //Récupére la police + initialise sa taille

    //Couleur de la police
    SDL_Color TextColor;
    TextColor.r = 255;
    TextColor.g = 0;
    TextColor.b = 0;
    TextColor.a = 0;

    SDL_Surface* TextSurface = TTF_RenderText_Solid(Font, "Retour", TextColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, TextSurface);

    int tailleX, tailleY;
    SDL_QueryTexture(texture, NULL, NULL, &tailleX, &tailleY);

    SDL_Rect DstRect;
    DstRect.x = TAILLEFENETREX/2 - tailleX/2;
    DstRect.y = TAILLEFENETREY - tailleY;
    DstRect.w = TextSurface->w;
    DstRect.h = TextSurface->h;

    SDL_RenderCopy(renderer, texture, NULL, &DstRect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(TextSurface);
    TTF_CloseFont(Font);
    TTF_Quit();
}

/**
 * \fn void affiche_nbPv(SDL_Renderer *renderer, int nbCle)
 * \brief Affiche le nombre de pv du joueur
*/
void affiche_nbPv(SDL_Renderer *renderer, int nbPv){

    TTF_Init();

    TTF_Font* Font = TTF_OpenFont("Ressources/Mustard_Smile.ttf", 50); //Récupére la police + initialise sa taille

    //Couleur de la police
    SDL_Color TextColor;
    TextColor.r = 255;
    TextColor.g = 255;
    TextColor.b = 255;

    char affiche[100];
	sprintf(affiche, "PV : %d l 20", nbPv); //Stocke la chaîne de caractère + la valeur de nbPv

    SDL_Surface* TextSurface = TTF_RenderText_Solid(Font, affiche, TextColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, TextSurface);

    SDL_Rect DstRect;
    DstRect.x = 8;
    DstRect.y = 17;
    DstRect.w = TextSurface->w-75;
    DstRect.h = TextSurface->h-10;

    SDL_RenderCopy(renderer, texture, NULL, &DstRect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(TextSurface);
    TTF_CloseFont(Font);
    TTF_Quit();
}

void textePause(SDL_Renderer *renderer, char* texte, int p){
    TTF_Init();

    TTF_Font* Font = TTF_OpenFont("Ressources/Mustard_Smile.ttf", 50); //Récupére la police + initialise sa taille

    //Couleur de la police
    SDL_Color TextColor;
    TextColor.r = 0;
    TextColor.g = 0;
    TextColor.b = 255;
    TextColor.a = 0;

    SDL_Surface* TextSurface = TTF_RenderText_Solid(Font, texte, TextColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, TextSurface);

    int tailleX, tailleY;
    SDL_QueryTexture(texture, NULL, NULL, &tailleX, &tailleY);
    int espacement = 100;

    SDL_Rect DstRect;
    DstRect.x = TAILLEFENETREX/2 - tailleX/2;
    DstRect.y = TAILLEFENETREY/2 - tailleY/2 + p*(espacement+tailleY);
    DstRect.w = TextSurface->w;
    DstRect.h = TextSurface->h;

    SDL_RenderCopy(renderer, texture, NULL, &DstRect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(TextSurface);
    TTF_CloseFont(Font);
    TTF_Quit();
}

void afficherPause(SDL_Renderer *renderer){
    textePause(renderer, "Revenir dans le jeu", -2);
    textePause(renderer, "Revenir au menu", -1);
    textePause(renderer, "Quitter en sauvegardant", 1);
    textePause(renderer, "Quitter sans sauvegarder", 2);
}

void texteGameOver(SDL_Renderer *renderer, char* texte, int p){
    TTF_Init();

    TTF_Font* Font = TTF_OpenFont("Ressources/Mustard_Smile.ttf", 50); //Récupére la police + initialise sa taille

    //Couleur de la police
    SDL_Color TextColor;
    TextColor.r = 0;
    TextColor.g = 0;
    TextColor.b = 255;
    TextColor.a = 0;

    SDL_Surface* TextSurface = TTF_RenderText_Solid(Font, texte, TextColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, TextSurface);

    int tailleX, tailleY;
    SDL_QueryTexture(texture, NULL, NULL, &tailleX, &tailleY);
    int espacement = 100;

    SDL_Rect DstRect;
    DstRect.x = TAILLEFENETREX/2 - tailleX/2;
    DstRect.y = TAILLEFENETREY/2 - tailleY/2 + p*(espacement+tailleY);
    DstRect.w = TextSurface->w;
    DstRect.h = TextSurface->h;

    SDL_RenderCopy(renderer, texture, NULL, &DstRect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(TextSurface);
    TTF_CloseFont(Font);
    TTF_Quit();
}

void afficheGameOver(SDL_Renderer* renderer){
    texteGameOver(renderer, "Rejouer", -1);
    texteGameOver(renderer, "GAME OVER", 0);
    texteGameOver(renderer, "Quitter", 1);
}

void texteWin(SDL_Renderer *renderer, char* texte, int p){
    TTF_Init();

    TTF_Font* Font = TTF_OpenFont("Ressources/Mustard_Smile.ttf", 50); //Récupére la police + initialise sa taille

    //Couleur de la police
    SDL_Color TextColor;
    TextColor.r = 0;
    TextColor.g = 0;
    TextColor.b = 255;
    TextColor.a = 0;

    SDL_Surface* TextSurface = TTF_RenderText_Solid(Font, texte, TextColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, TextSurface);

    int tailleX, tailleY;
    SDL_QueryTexture(texture, NULL, NULL, &tailleX, &tailleY);
    int espacement = 100;

    SDL_Rect DstRect;
    DstRect.x = TAILLEFENETREX/2 - tailleX/2;
    DstRect.y = TAILLEFENETREY/2 - tailleY/2 + p*(espacement+tailleY);
    DstRect.w = TextSurface->w;
    DstRect.h = TextSurface->h;

    SDL_RenderCopy(renderer, texture, NULL, &DstRect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(TextSurface);
    TTF_CloseFont(Font);
    TTF_Quit();
}

void afficheWin(SDL_Renderer* renderer){
    texteWin(renderer, "Rejouer", -1);
    texteWin(renderer, "YOU WIN", 0);
    texteWin(renderer, "Quitter", 1);
}
