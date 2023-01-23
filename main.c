/**
 * @file main.c
 * @brief Fonctions qui lance le jeu
 * @author GONTHIER Dimitri
 * @author HERTER Julian
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#undef NDEBUG
#include <assert.h>
#include <SDL2/SDL.h>

#include "fonctions_fichiers.h"
#include "fonctions_SDL.h"
#include "music.h"
#include "data.h"
#include "graphics.h"
#include "player.h"
#include "enemy.h"

/**
 * \fn unsigned int timer()
 * \brief Initialise un timer
 *
 * \return Retourne le timer
 */
unsigned int timer(){
    return (SDL_GetTicks());
}

bool collisionPlayer(enemy_t e, player_t p){
    if (e.x < p.x + p.taille &&
    e.x + e.taille > p.x &&
    e.y < p.y + p.taille &&
    e.taille + e.y > p.y) {
        return true;
    }

    return false;
}

/**
 * \fn int main()
 * \brief Lance le jeu
 */
int main(){
    bool rejouer = false;

    while(!rejouer){
        char saveFile[21] = "save.txt";
        bool terminer = false;
        bool sauvegarde = false;
        int menu = 0; // 0 : menu principal, 1 : aide, 2 : jeu, 3 : pause

        player_t player = {64, 64, 64, -1, 20, false};     // Perso principal
        enemy_t enemy1 = {64 * 7, 64 * 2, 64, 20, 0}; // Ennemi de la map 3_1
        enemy_t boss1 = {64*5, 64*3, 64, 20, 0};
        enemy_t bossFin = {64*8, 64*6, 64, 30, 0};

        int coef; // sert à savoir si on incrémente ou décrémente nom_Map[20] ou nom_map[22];
        int nbCle = 0;
        int compteur; // Temps écoulé entre chaque PAS
        int compteur2 =200; //Fait en sorte que le perso ne soit touché qu'une seule fois par l'ennemi de la map 3_1 à chaque collison
        int coup = 0; //Alterne les 2 sons de l'épée lorsque le joueur attaque

        char nom_Map[28] = ".Ressources/Map/map_0_0.txt";

        DIR *doss = opendir(".Ressources");
        if(doss == NULL){
            saveMap("Ressources/Map");
        }else{
            strcpy(nom_Map, setMap(saveFile));
            player.x = setPosX(saveFile);
            player.y = setPosY(saveFile);
            nbCle = setnbCle(saveFile);
            player.aUneEpee = setEpee(saveFile);
        }

        SDL_Window *fenetre = SDL_CreateWindow("Fenetre SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, TAILLEFENETREX, TAILLEFENETREY, SDL_WINDOW_RESIZABLE);
        SDL_Renderer *ecran = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);

        char **map = lire_fichier(nom_Map);

        int nbLigMap, nbColMap;
        taille_fichier(nom_Map, &nbLigMap, &nbColMap);

        // Texture des blocs
        SDL_Texture *blocs = charger_image("Ressources/blocs.bmp", ecran);

        SDL_Rect SrcBlocs[9], DestBlocs[9];

        int k = 0;
        for (int i = 0; i < 2; i++){
            for (int j = 0; j < 8; j++){
                if (k < 9){
                    SrcBlocs[k].x = j * 32;
                    SrcBlocs[k].y = i * 32;
                    SrcBlocs[k].w = 32;
                    SrcBlocs[k].h = 32;
                }
                k++;
            }
        }

        // Texture du playerText (on mettra une autre texture plus tard, la c'est pour tester)
        SDL_Texture *playerText = charger_image("Ressources/Perso/player.bmp", ecran);
        SDL_Texture *playerEpee = charger_image("Ressources/Perso/playerEpee.bmp", ecran);
        SDL_Texture *fondMenu = charger_image("Ressources/FondMenu.bmp", ecran);
        SDL_Texture *Enemy1 = charger_image("Ressources/Perso/gargouille.bmp", ecran);
        SDL_Texture *Boss1 = charger_image("Ressources/Perso/boss1.bmp", ecran);
        SDL_Texture *vie_Boss1 = charger_image("Ressources/barre_pv.bmp", ecran);
        SDL_Texture *bpv = charger_image("Ressources/barre_pv.bmp", ecran);
        SDL_Texture *contour_bpv = charger_image("Ressources/contour_bpv.bmp", ecran);
        SDL_Texture *bossFinText = charger_image("Ressources/Perso/bossFin.bmp", ecran);
        SDL_Texture *vie_BossFin = charger_image("Ressources/barre_pv.bmp", ecran);

        SDL_Rect SrcPlayer, DestPlayer;
        SrcPlayer.x = 0;
        SrcPlayer.y = 0;
        SrcPlayer.w = 32;
        SrcPlayer.h = 32;

        
        SDL_Rect SrcEnemy1, DestEnemy1;
        SrcEnemy1.x = 0;
        SrcEnemy1.y = 96;
        SrcEnemy1.w = 32;
        SrcEnemy1.h = 32;

        SDL_Rect SrcBoss1, DestBoss1;
        SrcBoss1.x = 0;
        SrcBoss1.y = 0;
        SrcBoss1.w = 32;
        SrcBoss1.h = 32;

        SDL_Rect SrcBossFin, DestBossFin;
        SrcBossFin.x = 0;
        SrcBossFin.y = 0;
        SrcBossFin.w = 32;
        SrcBossFin.h = 32;

        SDL_Rect DestBarrePv;

        SDL_Rect DestContourBarrePv;

        SDL_Rect DestBpv_Boss1;

        SDL_Rect DestBpv_BossFin;

            while (!terminer){
                SDL_RenderClear(ecran);

                switch (menu){
                case 0: // Menu principal
                    SDL_RenderCopy(ecran, fondMenu, NULL, NULL);

                    afficherMenu(ecran);

                    SDL_Event eventMenu;
                    while (SDL_PollEvent(&eventMenu)){
                        switch (eventMenu.type){
                        case SDL_QUIT:
                            terminer = true;
                            rejouer = true;
                            break;

                        case SDL_KEYDOWN:
                            switch (eventMenu.key.keysym.sym){
                            case SDLK_ESCAPE:
                                terminer = true;
                                rejouer = true;
                                break;
                            }
                            break;

                        case SDL_MOUSEBUTTONDOWN:
                            if (eventMenu.button.x > 380 && eventMenu.button.x < 520){
                                if (eventMenu.button.y > 280 && eventMenu.button.y < 330)
                                {
                                    menu = 2;
                                }
                            }

                            if (eventMenu.button.x > 400 && eventMenu.button.x < 500){
                                if (eventMenu.button.y > 450 && eventMenu.button.y < 485)
                                {
                                    menu = 1;
                                }
                            }

                            if (eventMenu.button.x > 365 && eventMenu.button.x < 530){
                                if (eventMenu.button.y > 600 && eventMenu.button.y < 660){
                                    terminer = true;
                                    rejouer = true;
                                }
                            }
                            break;
                        }
                    }
                    break;

                case 1: // Aide
                    SDL_RenderCopy(ecran, fondMenu, NULL, NULL);

                    afficherTexteAide(ecran);
                    afficherRetourAide(ecran);

                    SDL_Event eventAide;
                    while (SDL_PollEvent(&eventAide)){
                        switch (eventAide.type){
                        case SDL_QUIT:
                            terminer = true;
                            rejouer = true;
                            break;

                        case SDL_KEYDOWN:
                            switch (eventAide.key.keysym.sym){
                            case SDLK_ESCAPE:
                                terminer = true;
                                rejouer = true;
                                break;
                            }
                            break;

                        case SDL_MOUSEBUTTONDOWN:
                            if (eventAide.button.x > 380 && eventAide.button.x < 530){
                                if (eventAide.button.y > 720 && eventAide.button.y < TAILLEFENETREY){
                                    menu = 0;
                                }
                            }
                            break;
                        }
                    }
                    break;

                case 2: // Jeu

                    // Si le joueur touche la droite de l'écran
                    if (player.x + player.taille == TAILLEFENETREX){
                        coef = 0;
                        ecrire_fichier(nom_Map, map, nbLigMap, nbColMap);
                        change_map(nom_Map, coef);
                        map = lire_fichier(nom_Map);
                        player.x = PAS;
                    }

                    // Si le joueur touche la gauche de l'écran
                    if (player.x == 0){
                        coef = 1;
                        ecrire_fichier(nom_Map, map, nbLigMap, nbColMap);
                        change_map(nom_Map, coef);
                        map = lire_fichier(nom_Map);
                        player.x = TAILLEFENETREX - player.taille - PAS;
                    }

                    // Si le joueur touche le bas de l'écran
                    if (player.y == TAILLEFENETREY - player.taille){
                        coef = 2;
                        ecrire_fichier(nom_Map, map, nbLigMap, nbColMap);
                        change_map(nom_Map, coef);
                        map = lire_fichier(nom_Map);
                        player.y = PAS;
                    }

                    // Si le joueur touche le bord haut de l'écran
                    if (player.y == 0){
                        coef = 3;
                        ecrire_fichier(nom_Map, map, nbLigMap, nbColMap);
                        change_map(nom_Map, coef);
                        map = lire_fichier(nom_Map);
                        player.y = TAILLEFENETREY - player.taille - PAS;
                    }

                    // téléporte le joueur de la map 0_3 à la map 0_0
                    if ((nom_Map[20] == '0') && (nom_Map[22] == '3')){
                        if ((player.x == 576) && (player.y == 192)){
                            teleporteur();
                            nom_Map[22] = '0';
                            map = lire_fichier(nom_Map);
                            player.x = 320;
                            player.y = 448;
                            // modifier_caractere(map, nbLigMap, nbColMap, '3', ' ');
                        }
                    }

                    // téléporte le joueur de la map 1_3 à la map 1_0
                    if ((nom_Map[20] == '1') && (nom_Map[22] == '3')){
                        if (player.x == 576 && player.y == 448){
                            teleporteur();
                            nom_Map[22] = '0';
                            map = lire_fichier(nom_Map);
                            player.x = 576;
                            player.y = 128;
                        }
                    }

                    // téléporte le joueur de la map 2_3 à la map 2_0
                    if ((nom_Map[20] == '2') && (nom_Map[22] == '3')){
                        if ((player.x == 704) && (player.y == 384)){
                            teleporteur();
                            nom_Map[22] = '0';
                            map = lire_fichier(nom_Map);
                            player.x = 384;
                            player.y = 384;
                        }
                    }

                    // Téléporteurs de la map 2_1
                    if ((nom_Map[20] == '2') && (nom_Map[22] == '1')){
                        // Chemin du haut
                        if ((player.x == 256) && (player.y == 256)){
                            teleporteur();
                            player.y = 128;
                        }
                        if ((player.x == 384) && (player.y == 192)){
                            teleporteur();
                            player.x = 576;
                            player.y = 128;
                        }
                        if ((player.x == 704) && (player.y == 192)){
                            teleporteur();
                            player.x = 192;
                            player.y = 384;
                        }

                        // Chemin du bas
                        if ((player.x == 256) && (player.y == 512)){
                            teleporteur();
                            player.y = 640;
                        }
                        if ((player.x == 384) && (player.y == 576)){
                            teleporteur();
                            player.x = 576;
                            player.y = 640;
                        }
                        if ((player.x == 704) && (player.y == 576)){
                            teleporteur();
                            player.y = 384;
                        }
                    }

                    int temps = timer();

                    // Si le joueur va vers le haut
                    if (player.posture == 0){
                        if (compteur > 0){
                            if ((temps / 200) % 2 == 0){
                                SrcPlayer.x = 32;
                                SrcPlayer.y = 64;
                                // step();
                            }

                            if ((temps / 200) % 2 == 1){
                                SrcPlayer.x = 64;
                                SrcPlayer.y = 64;
                                // step();
                            }

                            compteur -= 1;
                        }

                        if (compteur == 0){
                            SrcPlayer.x = 0;
                            SrcPlayer.y = 64;
                        }
                    }

                    // Si le joueur va vers la gauche
                    if (player.posture == 1){

                        if (compteur > 0){
                            if ((temps / 200) % 2 == 0) {
                                SrcPlayer.x = 32;
                                SrcPlayer.y = 96;
                                // step();
                            }

                            if ((temps / 200) % 2 == 1){
                                SrcPlayer.x = 64;
                                SrcPlayer.y = 96;
                                // step();
                            }

                            compteur -= 1;
                        }

                        if (compteur == 0){
                            SrcPlayer.x = 0;
                            SrcPlayer.y = 96;
                        }
                    }

                    // Si le joueur va vers le bas
                    if (player.posture == 2){

                        if (compteur > 0){
                            if ((temps / 200) % 2 == 0){
                                SrcPlayer.x = 32;
                                SrcPlayer.y = 0;
                                // step();
                            }

                            if ((temps / 200) % 2 == 1){
                                SrcPlayer.x = 64;
                                SrcPlayer.y = 0;
                                // step();
                            }

                            compteur -= 1;
                        }

                        if (compteur == 0){
                            SrcPlayer.x = 0;
                            SrcPlayer.y = 0;
                        }
                    }

                    // Si le joueur va vers la droite
                    if (player.posture == 3){

                        if (compteur > 0){
                            if ((temps / 200) % 2 == 0){
                                SrcPlayer.x = 32;
                                SrcPlayer.y = 32;
                                // step();
                            }

                            if ((temps / 200) % 2 == 1){
                                SrcPlayer.x = 64;
                                SrcPlayer.y = 32;
                                // step();
                            }

                            compteur -= 1;
                        }

                        if (compteur == 0){
                            SrcPlayer.x = 0;
                            SrcPlayer.y = 32;
                        }
                    }

                    // RenderCopy des blocs
                    for (int i = 0; i < nbLigMap; i++){
                        for (int j = 0; j < nbColMap; j++){
                            for (int k = 0; k < 8; k++){
                                DestBlocs[k].x = j * 64;
                                DestBlocs[k].y = i * 64;
                                DestBlocs[k].w = 64;
                                DestBlocs[k].h = 64;

                                char c = map[i][j];
                                int n;
                                if (c == ' '){
                                    n = 0;
                                } else{
                                    n = c - '0';
                                }
                                SDL_RenderCopy(ecran, blocs, &SrcBlocs[n], &DestBlocs[k]);
                            }
                        }
                    }

                    // RenderCopy du playerText
                    DestPlayer.x = player.x;
                    DestPlayer.y = player.y;
                    DestPlayer.w = 64;
                    DestPlayer.h = 64;

                    // RenderCopy de l'ennemi de la map 3_1
                    DestEnemy1.x = enemy1.x;
                    DestEnemy1.y = enemy1.y;
                    DestEnemy1.w = 64;
                    DestEnemy1.h = 64;

                    // RenderCopy du boss de la map 0_3
                    DestBoss1.x = boss1.x;
                    DestBoss1.y = boss1.y;
                    DestBoss1.w = 64;
                    DestBoss1.h = 64;

                    // RenderCopy du boss de fin
                    DestBossFin.x = bossFin.x;
                    DestBossFin.y = bossFin.y;
                    DestBossFin.w = 64;
                    DestBossFin.h = 64;

                    // RenderCopy de la barre de pv
                    DestBarrePv.x = 8;
                    DestBarrePv.y = 7;
                    DestBarrePv.w = ((279/20)*player.pv);
                    DestBarrePv.h = 19;

                    // RenderCopy du contour de la barre de pv
                    DestContourBarrePv.x = 5;
                    DestContourBarrePv.y = 5;
                    DestContourBarrePv.w = 267;
                    DestContourBarrePv.h = 23;

                    // RenderCopy de la barre de pv du boss1
                    DestBpv_Boss1.x = boss1.x;
                    DestBpv_Boss1.y = boss1.y - 10;
                    DestBpv_Boss1.w = ((64/20)*boss1.pv);
                    DestBpv_Boss1.h = 10;

                    // RenderCopy de la barre de pv du bossFin
                    DestBpv_BossFin.x = bossFin.x;
                    DestBpv_BossFin.y = bossFin.y - 10;
                    DestBpv_BossFin.w = ((64/30)*bossFin.pv);
                    DestBpv_BossFin.h = 10;

                    if(player.pv > 0){
                        if (!player.aUneEpee){
                            SDL_RenderCopy(ecran, playerText, &SrcPlayer, &DestPlayer);
                        } else{
                            SDL_RenderCopy(ecran, playerEpee, &SrcPlayer, &DestPlayer);
                        }
                    }

                    if ((nom_Map[20] == '0') && (nom_Map[22] == '3')) { // Boss map 0_3
                        
                        if(boss1.pv > 0 && player.pv > 0){
                            int tempsBoss1 = timer();
                        
                            if (tempsBoss1 % 100 == 0){
                                if(boss1.x < player.x){ // Gauche du joueur
                                    boss1.x += PAS;
                                    boss1.regard = 1;


                                    if(collisionPlayer(boss1, player)){
                                        player.pv -= 1;
                                        //player.x += PAS;
                                        hurt();
                                    }
                                }else if (boss1.x > player.x){ // Droite du joueur
                                    boss1.x -= PAS;
                                    boss1.regard = 3;

                                    if(collisionPlayer(boss1, player)){
                                        player.pv -= 1;
                                        //player.x -= PAS;
                                        hurt();
                                    }
                                }

                                if(boss1.y < player.y){  // Bas du joueur
                                    boss1.y += PAS;
                                    boss1.regard = 0;

                                    if(collisionPlayer(boss1, player)){
                                        player.pv -= 1;
                                        //player.y += PAS;
                                        hurt();
                                    }
                                }else if (boss1.y > player.y){ // Haut du joueur
                                    boss1.y -= PAS;
                                    boss1.regard = 2;

                                    if(collisionPlayer(boss1, player)){
                                        player.pv -= 1;
                                        //player.y -= PAS;
                                        hurt();
                                    }
                                }

                                //Sans cette condition, pas de collision si x et y du joueur = x et y du boss1
                                if((boss1.x == player.x) && (boss1.y == player.y)){
                                    player.pv -= 1;
                                    hurt();
                                }
                            }
                            SrcBoss1.y = 32*boss1.regard;

                            SDL_RenderCopy(ecran, Boss1, &SrcBoss1, &DestBoss1);

                            SDL_RenderCopy(ecran, vie_Boss1, NULL, &DestBpv_Boss1);
                        }else{
                            //Le boss est invisible est n'attaque plus mais on peut continuer à tirer dans le vide...
                        }
                    }

                    if ((nom_Map[20] == '3') && (nom_Map[22] == '3')) { // Boss map 3_3
                        
                        int tempsBossFin = timer();
                        
                        if(bossFin.pv > 0 && player.pv > 0){
                            if (tempsBossFin % 100 == 0){
                                if(bossFin.x < player.x){ // Gauche du joueur
                                    bossFin.x += PAS*2;
                                    bossFin.regard = 1;


                                    if(collisionPlayer(bossFin, player)){
                                        player.pv -= 1;
                                        //player.x += PAS*2;
                                        hurt();
                                    }
                                }else if (bossFin.x > player.x){ // Droite du joueur
                                    bossFin.x -= PAS*2;
                                    bossFin.regard = 3;

                                    if(collisionPlayer(bossFin, player)){
                                        player.pv -= 1;
                                        //player.x -= PAS*2;
                                        hurt();
                                    }
                                }

                                if(bossFin.y < player.y){  // Bas du joueur
                                    bossFin.y += PAS*2;
                                    bossFin.regard = 0;

                                    if(collisionPlayer(bossFin, player)){
                                        player.pv -= 1;
                                        //player.y += PAS*2;
                                        hurt();
                                    }
                                }else if (bossFin.y > player.y){ // Haut du joueur
                                    bossFin.y -= PAS*2;
                                    bossFin.regard = 2;

                                    if(collisionPlayer(bossFin, player)){
                                        player.pv -= 1;
                                        //player.y -= PAS*2;
                                        hurt();
                                    }
                                }

                                //Sans cette condition, pas de collision si x et y du joueur = x et y du bossFin
                                if((bossFin.x == player.x) && (bossFin.y == player.y)){
                                    player.pv -= 1;
                                    hurt();
                                }
                            }
                            SrcBossFin.y = 32*bossFin.regard;

                            SDL_RenderCopy(ecran, vie_BossFin, NULL, &DestBpv_BossFin);

                            SDL_RenderCopy(ecran, bossFinText, &SrcBossFin, &DestBossFin);
                        }else{
                            //...
                        }
                    }

                    //Si le joueur n'a plus de pv
                    if(player.pv <= 0){
                        afficheGameOver(ecran);

                        SDL_Event eventPause;
                        while (SDL_PollEvent(&eventPause)){
                            switch (eventPause.type){
                            case SDL_QUIT:
                                terminer = true;
                                rejouer = true;
                                break;

                            case SDL_KEYDOWN:
                                switch (eventPause.key.keysym.sym){
                                case SDLK_ESCAPE:
                                    terminer = true;
                                    rejouer = true;
                                    break;
                                }
                                break;

                            case SDL_MOUSEBUTTONDOWN:
                                if (eventPause.button.x > 290 && eventPause.button.x < 615){        //Rejouer   
                                    if (eventPause.button.y > 200 && eventPause.button.y < 240){
                                        terminer = true;
                                    }
                                }

                                if (eventPause.button.x > 200 && eventPause.button.x < 700){        //Quitter  
                                    if (eventPause.button.y > 520 && eventPause.button.y < 575){
                                        terminer = true;
                                        rejouer = true;
                                    }   
                                }
                                break;
                            }
                        }
                        break;
                    }

                    //Si le joueur bat le bossFin
                    if(bossFin.pv <= 0){
                        afficheWin(ecran);

                        SDL_Event eventPause;
                        while (SDL_PollEvent(&eventPause)){
                            switch (eventPause.type){
                            case SDL_QUIT:
                                terminer = true;
                                rejouer = true;
                                break;

                            case SDL_KEYDOWN:
                                switch (eventPause.key.keysym.sym){
                                case SDLK_ESCAPE:
                                    terminer = true;
                                    rejouer = true;
                                    break;
                                }
                                break;

                            case SDL_MOUSEBUTTONDOWN:
                                if (eventPause.button.x > 290 && eventPause.button.x < 615){        //Rejouer   
                                    if (eventPause.button.y > 200 && eventPause.button.y < 240){
                                        terminer = true;
                                    }
                                }

                                if (eventPause.button.x > 200 && eventPause.button.x < 700){        //Quitter   
                                    if (eventPause.button.y > 520 && eventPause.button.y < 575){
                                        terminer = true;
                                        rejouer = true;
                                    }   
                                }
                                break;
                            }
                        }
                        break;
                    }


                    if ((nom_Map[20] == '3') && (nom_Map[22] == '1')) {
                        SDL_RenderCopy(ecran, Enemy1, &SrcEnemy1, &DestEnemy1);
                        int temps2 = timer();

                        //Mouvement de l'ennemi
                        if(enemy1.x > 128 && enemy1.y == 128){
                            enemy1.x -= 1;

                            if ((temps2 / 200) % 2 == 0){
                                SrcEnemy1.x = 32;
                                SrcEnemy1.y = 32;
                            }else{
                                SrcEnemy1.x = 64;
                                SrcEnemy1.y = 32;
                            }
                        }

                        if(enemy1.x == 128 && enemy1.y < 384){
                            enemy1.y += 1;

                            if ((temps2 / 200) % 2 == 0) {
                                SrcEnemy1.x = 32;
                                SrcEnemy1.y = 0;
                            }else{
                                SrcEnemy1.x = 64;
                                SrcEnemy1.y = 0;
                            }
                        }

                        if(enemy1.x < 704 && enemy1.y == 384){
                            enemy1.x += 1;

                            if ((temps2 / 200) % 2 == 0){
                                SrcEnemy1.x = 32;
                                SrcEnemy1.y = 64;
                            }else{
                                SrcEnemy1.x = 64;
                                SrcEnemy1.y = 64;
                            }
                        }

                        if(enemy1.x == 704 && enemy1.y > 128){
                            enemy1.y -= 1;

                            if ((temps2 / 200) % 2 == 0) {
                                SrcEnemy1.x = 32;
                                SrcEnemy1.y = 96;
                            }else{
                                SrcEnemy1.x = 64;
                                SrcEnemy1.y = 96;
                            }
                        }
                        
                        if(collisionPlayer(enemy1, player) && compteur2 == 200){
                            hurt();
                            player.pv -= 5;
                            compteur2 -= 1;
                        }

                        if(compteur2 < 200){
                            compteur2 -= 1;
                            if(compteur2 == 0){
                                compteur2 = 200;
                            }
                        }
                    }

                    SDL_RenderCopy(ecran, contour_bpv, NULL, &DestContourBarrePv);

                    SDL_RenderCopy(ecran, bpv, NULL, &DestBarrePv);

                    SDL_Event event;
                    while (SDL_PollEvent(&event)){
                        switch (event.type){
                        case SDL_QUIT:
                            terminer = true;
                            rejouer = true;
                            break;

                        case SDL_KEYDOWN:
                            switch (event.key.keysym.sym){
                            case SDLK_ESCAPE:
                                terminer = true;
                                rejouer = true;
                                break;
                            case 'z':
                                player.posture = 0;
                                if ((player.y > 0 && map[(player.y - PAS) / 64][player.x / 64] == ' ' && map[(player.y - PAS) / 64][(player.x + player.taille - 1) / 64] == ' ') || (player.y > 0 && map[(player.y - PAS) / 64][player.x / 64] == '2' && map[(player.y - PAS) / 64][(player.x + player.taille - 1) / 64] == '2')){
                                    player.y -= PAS;
                                    compteur = 100;
                                }
                                break;

                            case 'q':
                                player.posture = 1;
                                if ((player.x > 0 && map[player.y / 64][(player.x - PAS) / 64] == ' ' && map[(player.y + player.taille - 1) / 64][(player.x - PAS) / 64] == ' ') || (player.x > 0 && map[player.y / 64][(player.x - PAS) / 64] == '2' && map[(player.y + player.taille - 1) / 64][(player.x - PAS) / 64] == '2')){
                                    player.x -= PAS;
                                    compteur = 100;
                                }
                                break;

                            case 's':
                                player.posture = 2;
                                if ((player.y + player.taille < TAILLEFENETREY && map[(player.y + player.taille) / 64][player.x / 64] == ' ' && map[(player.y + player.taille) / 64][(player.x + player.taille - 1) / 64] == ' ') || (player.y + player.taille < TAILLEFENETREY && map[(player.y + player.taille) / 64][player.x / 64] == '2' && map[(player.y + player.taille) / 64][(player.x + player.taille - 1) / 64] == '2')){
                                    player.y += PAS;
                                    compteur = 100;
                                }
                                break;

                            case 'd':
                                player.posture = 3;
                                if ((player.x + player.taille < TAILLEFENETREX && map[player.y / 64][(player.x + player.taille) / 64] == ' ' && map[(player.y + player.taille - 1) / 64][(player.x + player.taille) / 64] == ' ') || (player.x + player.taille < TAILLEFENETREX && map[player.y / 64][(player.x + player.taille) / 64] == '2' && map[(player.y + player.taille - 1) / 64][(player.x + player.taille) / 64] == '2')){
                                    player.x += PAS;
                                    compteur = 100;
                                }
                                break;

                            case 'e':
                                // Détection s'il y a un coffre autour du playerText
                                if (map[(player.y - 1) / 64][player.x / 64] == '5'){
                                    coffre();
                                    nbCle++;
                                    map[(player.y - 1) / 64][player.x / 64] = '7';
                                }else if (map[(player.y + player.taille + 1) / 64][player.x / 64] == '5'){
                                    coffre();
                                    nbCle++;
                                    map[(player.y + player.taille + 1) / 64][player.x / 64] = '7';
                                }else if (map[player.y / 64][(player.x + player.taille + 1) / 64] == '5'){
                                    coffre();
                                    nbCle++;
                                    map[player.y / 64][(player.x + player.taille + 1) / 64] = '7';
                                }else if (map[player.y / 64][(player.x - 1) / 64] == '5'){
                                    coffre();
                                    nbCle++;
                                    map[player.y / 64][(player.x - 1) / 64] = '7';
                                }

                                // Détection s'il y a une porte autour du playerText et s'il a une clé pour l'ouvrir
                                if (nbCle > 0){
                                    if (map[(player.y - 1) / 64][player.x / 64] == '4') {
                                        porte();
                                        nbCle--;
                                        map[(player.y - 1) / 64][player.x / 64] = ' ';
                                    }else if (map[(player.y + player.taille + 1) / 64][player.x / 64] == '4'){
                                        porte();
                                        nbCle--;
                                        map[(player.y + player.taille + 1) / 64][player.x / 64] = ' ';
                                    } else if (map[player.y / 64][(player.x + player.taille + 1) / 64] == '4'){
                                        porte();
                                        nbCle--;
                                        map[player.y / 64][(player.x + player.taille + 1) / 64] = ' ';
                                    }else if (map[player.y / 64][(player.x - 1) / 64] == '4'){
                                        porte();
                                        nbCle--;
                                        map[player.y / 64][(player.x - 1) / 64] = ' ';
                                    }
                                }

                                // Ramasse l'épée
                                if (map[(player.y - 1) / 64][player.x / 64] == '8'){
                                    sword();
                                    modifier_caractere(map, nbLigMap, nbColMap, '8', ' ');
                                    player.aUneEpee = true;
                                }else if (map[(player.y + player.taille + 1) / 64][player.x / 64] == '8'){
                                    sword();
                                    modifier_caractere(map, nbLigMap, nbColMap, '8', ' ');
                                    player.aUneEpee = true;
                                }else if (map[player.y / 64][(player.x + player.taille + 1) / 64] == '8'){
                                    sword();
                                    modifier_caractere(map, nbLigMap, nbColMap, '8', ' ');
                                    player.aUneEpee = true;
                                }else if (map[player.y / 64][(player.x - 1) / 64] == '8'){
                                    sword();
                                    modifier_caractere(map, nbLigMap, nbColMap, '8', ' ');
                                    player.aUneEpee = true;
                                }

                                // Activateur
                                if (map[(player.y - 1) / 64][player.x / 64] == '6'){ // 1er activateur de la map 1_1
                                    activateur();
                                    map[4][11] = ' ';
                                    map[4][6] = '4';
                                }else if (map[(player.y + player.taille + 1) / 64][player.x / 64] == '6'){ // 2eme activateur de la map 1_1
                                    activateur();
                                    map[4][6] = ' ';
                                    map[4][11] = '4';
                                }else if (map[player.y / 64][(player.x + player.taille + 1) / 64] == '6'){ // Activateur de la map 1_2
                                    activateur();
                                    map[5][12] = ' ';
                                    map[8][7] = ' ';
                                }

                                break;
                                
                            case 'a':
                                // Pierre cassée
                                if (map[(player.y - 1) / 64][player.x / 64] == '3' && player.aUneEpee){
                                    pierre();
                                    map[(player.y - 1) / 64][player.x / 64] = ' ';
                                }else if (map[(player.y + player.taille + 1) / 64][player.x / 64] == '3' && player.aUneEpee){
                                    pierre();
                                    map[(player.y + player.taille + 1) / 64][player.x / 64] = ' ';
                                } else if (map[player.y / 64][(player.x + player.taille + 1) / 64] == '3' && player.aUneEpee){
                                    pierre();
                                    map[player.y / 64][(player.x + player.taille + 1) / 64] = ' ';
                                }else if (map[player.y / 64][(player.x - 1) / 64] == '3' && player.aUneEpee){
                                    pierre();
                                    map[player.y / 64][(player.x - 1) / 64] = ' ';
                                }

                                //Attaque le boss1
                                if(collisionPlayer(boss1, player)){
                                    boss1.pv -= 5;

                                    if(player.x <= boss1.x){
                                        boss1.x += 64;
                                    }else if(player.x > boss1.x){
                                        boss1.x -= 64;
                                    }

                                    /*if(player.y <= boss1.y){
                                        boss1.y += 64;
                                    }else if(player.x > boss1.x){
                                        boss1.y -= 64;
                                    }*/
                                }

                                //Attaque le boss de fin
                                if(collisionPlayer(bossFin, player)){
                                    bossFin.pv -= 5;

                                    if(player.x <= bossFin.x){
                                        bossFin.x += 64;
                                    }else if(player.x > bossFin.x){
                                        bossFin.x -= 64;
                                    }
                                }

                                //Son de l'épée lorsque le perso attaque
                                if(player.aUneEpee && coup == 0){
                                    coup_epee1();
                                    coup = 1;
                                }else if(player.aUneEpee && coup == 1){
                                    coup_epee2();
                                    coup = 0;
                                }

                                break;

                            case 'p':
                                menu = 3;

                            }

                        default:
                            break;
                        }
                    }
                    affiche_nbCle(ecran, nbCle);
                    affiche_nbPv(ecran, player.pv);
                    break;

                case 3 :        // Menu pause
                    SDL_RenderCopy(ecran, fondMenu, NULL, NULL);

                    afficherPause(ecran);

                    SDL_Event eventPause;
                    while (SDL_PollEvent(&eventPause)){
                        switch (eventPause.type){
                        case SDL_QUIT:
                            terminer = true;
                            rejouer = true;
                            break;

                        case SDL_KEYDOWN:
                            switch (eventPause.key.keysym.sym){
                            case SDLK_ESCAPE:
                                terminer = true;
                                rejouer = true;
                                break;
                            }
                            break;

                        case SDL_MOUSEBUTTONDOWN:
                            if (eventPause.button.x > 260 && eventPause.button.x < 640){        //Revenir Jeu
                                if (eventPause.button.y > 40 && eventPause.button.y < 80){
                                    menu = 2;
                                }
                            }

                            if (eventPause.button.x > 290 && eventPause.button.x < 615){        //Revenir Menu   
                                if (eventPause.button.y > 200 && eventPause.button.y < 240){
                                    menu = 0;
                                }
                            }

                            if (eventPause.button.x > 200 && eventPause.button.x < 700){        //Quitter avec sauvegarde   
                                if (eventPause.button.y > 520 && eventPause.button.y < 575){
                                    ecrire_fichier(nom_Map, map, nbLigMap, nbColMap);
                                    creerFichierSave(saveFile, nom_Map, player.x, player.y, nbCle, player.aUneEpee);
                                    sauvegarde = true;
                                    terminer = true;
                                    rejouer = true;
                                }   
                            }

                            if (eventPause.button.x > 190 && eventPause.button.x < 700){        //Quitter sans sauvegarde  
                                if (eventPause.button.y > 690 && eventPause.button.y < 740){
                                    terminer = true;
                                    rejouer = true;
                                }
                            }
                            break;
                        }
                    }
                    break;

                default:
                    break;
                }

                SDL_RenderPresent(ecran);
        }

        desallouer_tab_2D(map, nbLigMap);

        if(!sauvegarde){
            supprimerDoss(".Ressources/Map/");
        }
        
        /*Mix_FreeChunk(...);
        Mix_CloseAudio();*/
        SDL_DestroyTexture(blocs);
        SDL_DestroyTexture(playerText);
        SDL_DestroyTexture(playerEpee);
        SDL_DestroyTexture(fondMenu);
        SDL_DestroyTexture(Enemy1);
        SDL_DestroyTexture(Boss1);
        SDL_DestroyTexture(vie_Boss1);
        SDL_DestroyTexture(contour_bpv);
        SDL_DestroyTexture(bpv);
        SDL_DestroyTexture(bossFinText);
        SDL_DestroyTexture(vie_BossFin);
        SDL_DestroyRenderer(ecran);
        SDL_DestroyWindow(fenetre);
        SDL_Quit();
    }

    return 0;
}