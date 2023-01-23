/**
 * @file data.c
 * @brief Fichier regroupant les corps des fonctions qui change les données de jeu
 * @author GONTHIER Dimitri
 * @author HERTER Julian
*/

#include "data.h"

/**
 * \fn void saveMap(char nomFichier[15])
 * \brief Fonction qui permet de faire une sauvegarde temporaire du jeu
*/
void saveMap(char nomFichier[15]){
    struct dirent *lecture;
    DIR *rep = opendir(nomFichier);

    while ((lecture = readdir(rep))){
        if(strcmp(lecture->d_name, ".") != 0 && strcmp(lecture->d_name, "..") != 0){
            char ch;
            char chemin1[20] = "";
            strcat(chemin1, nomFichier);
            strcat(chemin1, "/");
            strcat(chemin1, lecture->d_name);
            

            char chemin2[20] = ".";
            strcat(chemin2, nomFichier);

            char che[20] = "";
            strcat(che, chemin2);

            char cheminTmp[20] = "";
            char *p = strtok(che, "/");
            while(p != NULL)
            {
                strcat(cheminTmp, p);
                mkdir(cheminTmp,0775);
                strcat(cheminTmp, "/");
                p = strtok(NULL, "/");
            }
            strcat(chemin2, "/");
            strcat(chemin2, lecture->d_name);

            FILE* fich1 = fopen(chemin1, "r");
            FILE* fich2 = fopen(chemin2, "w");

            while((ch = getc(fich1)) != EOF){
                putc(ch, fich2);
            }

            fclose(fich1);
            fclose(fich2);
        }
    }

    closedir(rep);
}

/**
 * \fn void supprimerDoss(char nomFichier[30])
 * \brief Fonction qui permet de supprimer la sauvegarde tempon
*/
void supprimerDoss(char nomFichier[17]){
    struct dirent *lecture;
    DIR *rep = opendir(nomFichier);

    while ((lecture = readdir(rep))){
        if(strcmp(lecture->d_name, ".") != 0 && strcmp(lecture->d_name, "..") != 0){
            char nomFich[30] = "";
            strcat(nomFich, nomFichier);
            strcat(nomFich, lecture->d_name);
            remove(nomFich);
        }
    }

    rmdir(nomFichier);

    char cheminTmp[20] = "";
    strcat(cheminTmp, nomFichier);
    char *p = strtok(cheminTmp, "/");
    while(p != NULL){
        rmdir(p);
        p = strtok(NULL, "/");
    }
    free(p);
    closedir(rep);
}

/**
 * \fn void change_map(char nom_Map[30], int coef)
 * \brief Fonction qui permet de changer la map en jeu
*/
void change_map(char nom_Map[28], int coef){
    // On incrémente nom_Map[20]
    if(coef == 0){
        char cChar = nom_Map[22];
        int iChar = cChar - '0';
        iChar++;

        int iInt = iChar + '0'; 
        nom_Map[22] = iInt;
    }

    // On décrémente nom_Map[20]
    if(coef == 1){
        char cChar = nom_Map[22];
        int iChar = cChar - '0';
        iChar--;

        int iInt = iChar + '0'; 
        nom_Map[22] = iInt;
    }

    // On incrémente nom_Map[22]
    if(coef == 2){
        char cChar = nom_Map[20];
        int iChar = cChar - '0';
        iChar++;

        int iInt = iChar + '0'; 
        nom_Map[20] = iInt;
    }

    // On décrémente nom_Map[20]
    if(coef == 3){
        char cChar = nom_Map[20];
        int iChar = cChar - '0';
        iChar--;

        int iInt = iChar + '0'; 
        nom_Map[20] = iInt;
    }
}

void creerFichierSave(char *nomFichier, char nomMap[28], int posX, int posY, int nbCle, int aEpee){
    FILE* save = fopen(nomFichier, "w");

    char ph[100];
    sprintf(ph, "%s %d %d %d %d", nomMap, posX, posY, nbCle, aEpee);

    fputs(ph, save);

    fclose(save);
}

char* setMap(char *nomFichier){
    FILE* save = fopen(nomFichier, "r");

    char ph[100];
    
    fgets(ph, 40, save);

    char d[] = " ";
    char *p = strtok(ph, d);

    return p;
}

int setPosX(char *nomFichier){
    FILE* save = fopen(nomFichier, "r");

    char ph[100];
    
    fgets(ph, 40, save);

    char d[] = " ";
    char *p = strtok(ph, d);

    int cpt = 0;

    while(p != NULL){
        switch (cpt)
        {
        case 1:
            fclose(save);
            int res = atoi(p);

            return res;
            break;
        
        default:
            break;
        }
        p = strtok(NULL, d);
        cpt++;
    }
    fclose(save);
    return 0;
}

int setPosY(char *nomFichier){
    FILE* save = fopen(nomFichier, "r");

    char ph[100];
    
    fgets(ph, 40, save);

    char d[] = " ";
    char *p = strtok(ph, d);

    int cpt = 0;

    while(p != NULL){
        switch (cpt)
        {
        case 2:
            fclose(save);
            int res = atoi(p);

            return res;
            break;
        
        default:
            break;
        }
        p = strtok(NULL, d);
        cpt++;
    }
    fclose(save);
    return 0;
}

int setnbCle(char *nomFichier){
    FILE* save = fopen(nomFichier, "r");

    char ph[100];
    
    fgets(ph, 40, save);

    char d[] = " ";
    char *p = strtok(ph, d);

    int cpt = 0;

    while(p != NULL){
        switch (cpt)
        {
        case 3:
            fclose(save);
            int res = atoi(p);

            return res;
            break;
        
        default:
            break;
        }
        p = strtok(NULL, d);
        cpt++;
    }
    fclose(save);
    return 0;
}

bool setEpee(char *nomFichier){
    FILE* save = fopen(nomFichier, "r");

    char ph[100];
    
    fgets(ph, 40, save);

    char d[] = " ";
    char *p = strtok(ph, d);

    int cpt = 0;

    while(p != NULL){
        switch (cpt)
        {
        case 4:
            fclose(save);
            int res = atoi(p);

            return res;
            break;
        
        default:
            break;
        }
        p = strtok(NULL, d);
        cpt++;
    }
    fclose(save);
    return 0;
}