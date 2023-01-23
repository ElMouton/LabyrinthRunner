/**
 * @file musics.c
 * @brief Fichier regroupant les corps des fonctions qui font du son
 * @author GONTHIER Dimitri
 * @author HERTER Julian
*/
#include "music.h"

/**
 * \fn void porte()
 * \brief Fait le bruit d'une porte qui se débloque
 * 
 * \return
*/
void porte(){
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1){ //Initialisation de l'API Mixer
		printf("%s", Mix_GetError());
		exit(1);
	}
    Mix_Chunk *musique; //Création du pointeur de type Mix_Music
    musique = Mix_LoadWAV("Ressources/Son/porte.wav"); //Chargement de la musique
	if(musique == 0){
		printf("erreur %s", Mix_GetError());
		exit(1);
	}
    Mix_PlayChannel(-1, musique, 0); //Jouer une fois la musique
}

/**
 * \fn void coffre()
 * \brief Fait le bruit d'un coffre qui s'ouvre
 * 
 * \return
*/
void coffre(){
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1){ //Initialisation de l'API Mixer
		printf("%s", Mix_GetError());
		exit(1);
	}
    Mix_Chunk *musique; //Création du pointeur de type Mix_Music
    musique = Mix_LoadWAV("Ressources/Son/coffre.wav"); //Chargement de la musique
	if(musique == 0){
		printf("erreur %s", Mix_GetError());
		exit(1);
	}
    Mix_PlayChannel(-1, musique, 0); //Jouer une fois la musique
}

/**
 * \fn void step()
 * \brief Fait le bruit de pas du personnage
 * 
 * \return
*/
void step(){
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1){ //Initialisation de l'API Mixer
		printf("%s", Mix_GetError());
		exit(1);
	}
    Mix_Chunk *musique; //Création du pointeur de type Mix_Music
    musique = Mix_LoadWAV("Ressources/Son/pas.wav"); //Chargement de la musique
	if(musique == 0){
		printf("erreur %s", Mix_GetError());
		exit(1);
	}
    Mix_PlayChannel(-1, musique, 0); //Jouer une fois la musique
}

/**
 * \fn void sword()
 * \brief Fait le bruit de l'épée lorsque le perso la prend
 * 
 * \return
*/
void sword(){
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1){ //Initialisation de l'API Mixer
		printf("%s", Mix_GetError());
		exit(1);
	}
    Mix_Chunk *musique; //Création du pointeur de type Mix_Music
    musique = Mix_LoadWAV("Ressources/Son/epee.wav"); //Chargement de la musique
	if(musique == 0){
		printf("erreur %s", Mix_GetError());
		exit(1);
	}
    Mix_PlayChannel(-1, musique, 0); //Jouer une fois la musique
}

/**
 * \fn void teleporteur()
 * \brief Fait le bruit du téléporteur
 * 
 * \return
*/
void teleporteur(){
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1){ //Initialisation de l'API Mixer
		printf("%s", Mix_GetError());
		exit(1);
	}
    Mix_Chunk *musique; //Création du pointeur de type Mix_Music
    musique = Mix_LoadWAV("Ressources/Son/teleporteur.wav"); //Chargement de la musique
	if(musique == 0){
		printf("erreur %s", Mix_GetError());
		exit(1);
	}
    Mix_PlayChannel(-1, musique, 0); //Jouer une fois la musique
}

/**
 * \fn void activateur()
 * \brief Fait le bruit de l'activateur
 * 
 * \return
*/
void activateur(){
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1){ //Initialisation de l'API Mixer
		printf("%s", Mix_GetError());
		exit(1);
	}
    Mix_Chunk *musique; //Création du pointeur de type Mix_Music
    musique = Mix_LoadWAV("Ressources/Son/activateur.wav"); //Chargement de la musique
	if(musique == 0){
		printf("erreur %s", Mix_GetError());
		exit(1);
	}
    Mix_PlayChannel(-1, musique, 0); //Jouer une fois la musique
}

/**
 * \fn void pierre()
 * \brief Fait le bruit d'une pierre qui se casse
 * 
 * \return
*/
void pierre(){
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1){ //Initialisation de l'API Mixer
		printf("%s", Mix_GetError());
		exit(1);
	}
    Mix_Chunk *musique; //Création du pointeur de type Mix_Music
    musique = Mix_LoadWAV("Ressources/Son/pierre.wav"); //Chargement de la musique
	if(musique == 0){
		printf("erreur %s", Mix_GetError());
		exit(1);
	}
    Mix_PlayChannel(-1, musique, 0); //Jouer une fois la musique
}

/**
 * \fn void hurt()
 * \brief Bruit du perso qui se fait attaquer
 * 
 * \return
*/
void hurt(){
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1){ //Initialisation de l'API Mixer
		printf("%s", Mix_GetError());
		exit(1);
	}
    Mix_Chunk *musique; //Création du pointeur de type Mix_Music
    musique = Mix_LoadWAV("Ressources/Son/hurt.wav"); //Chargement de la musique
	if(musique == 0){
		printf("erreur %s", Mix_GetError());
		exit(1);
	}
    Mix_PlayChannel(-1, musique, 0); //Jouer une fois la musique
}

/**
 * \fn void coup_epee1()
 * \brief Bruit du perso qui attaque
 * 
 * \return
*/
void coup_epee1(){
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1){ //Initialisation de l'API Mixer
		printf("%s", Mix_GetError());
		exit(1);
	}
    Mix_Chunk *musique; //Création du pointeur de type Mix_Music
    musique = Mix_LoadWAV("Ressources/Son/coup_epee1.wav"); //Chargement de la musique
	if(musique == 0){
		printf("erreur %s", Mix_GetError());
		exit(1);
	}
    Mix_PlayChannel(-1, musique, 0); //Jouer une fois la musique
}

/**
 * \fn void coup_epee2()
 * \brief Bruit du perso qui attaque
 * 
 * \return
*/
void coup_epee2(){
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1){ //Initialisation de l'API Mixer
		printf("%s", Mix_GetError());
		exit(1);
	}
    Mix_Chunk *musique; //Création du pointeur de type Mix_Music
    musique = Mix_LoadWAV("Ressources/Son/coup_epee2.wav"); //Chargement de la musique
	if(musique == 0){
		printf("erreur %s", Mix_GetError());
		exit(1);
	}
    Mix_PlayChannel(-1, musique, 0); //Jouer une fois la musique
}




