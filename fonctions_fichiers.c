/**
 * @file fonctions_fichiers.c
 * @brief Fichier regroupant les corps des fonctions qui permettent d'utiliser un tableau à 2 dimensions et un fichier texte
 * @author GONTHIER Dimitri
 * @author HERTER Julian
*/

#include "fonctions_fichiers.h"

/**
 * \fn char** allouer_tab_2D(int x, int y)
 * \brief Permet d'allouer à la mémoire un tableau à 2 dimensions de taille x*y
 * 
 * \return Le tableau à 2 dimensions
*/
char** allouer_tab_2D(int x, int y){
    char** tab = malloc(x*sizeof(char*));
    for (int i = 0; i < x; i++)
    {
        tab[i] = malloc((y+1)*sizeof(char));
    }
    

    for (int i = 0; i < x; i++){
        for (int j = 0; j < y+1; j++){
            tab[i][j] = ' ';
        }
    }

    return tab;
}

/**
 * \fn void desallouer_tab_2D(char** tab, int n)
 * \brief Desalloue un tableau à 2 dimensions
*/
void desallouer_tab_2D(char** tab, int n){
    for (int i = 0; i < n; i++)
    {
        free(tab[i]);
    }
    free(tab);
}

/**
 * \fn void afficher_tab_2D(char** tab, int n, int m
 * \brief Affiche dans la console un tableau à 2 dimensions
*/
void afficher_tab_2D(char** tab, int n, int m){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            printf("%c ", tab[i][j]);
        }
        printf("\n");
    }
    
}

/**
 * \fn void taille_fichier(const char* nomFichier, int* nbLig, int* nbCol)
 * \brief Donne les dimensions d'un tableau dans un fichier texte
 * 
 * \return Le nombre de ligne et de colonnes du tableau
*/
void taille_fichier(const char* nomFichier, int* nbLig, int* nbCol){
    FILE* fichier = fopen(nomFichier, "r");
    *nbLig = 0;
    *nbCol = 0;

    int nbColonnes = 0, nbColonnesMax = 0;

    int c = 45;
    if(fichier != NULL){
        while(c != EOF){
            c = fgetc(fichier);
            

            if(c == '\n'){
                *nbLig += 1;
                if(nbColonnes > nbColonnesMax){
                    nbColonnesMax = nbColonnes;
                }
                nbColonnes = 0;
            }else{
                nbColonnes += 1;
            }
        }
    }
    *nbCol = nbColonnesMax;

    fclose(fichier);
}

/**
 * \fn char** lire_fichier(const char* nomFichier)
 * \brief Creer un tableau à 2 dimensions comportant le tableau du fichier texte
 * 
 * \return Le tableau à 2 dimensions
*/
char** lire_fichier(const char* nomFichier){
    int nbLig;
    int nbCol;

    FILE* fichier = fopen(nomFichier, "r");

    taille_fichier(nomFichier, &nbLig, &nbCol);

    char** tab = allouer_tab_2D(nbLig, nbCol);

    int i = 0, j = 0;
    char c = 24;
    
    if(fichier != NULL){
        while(c != EOF){
            c = fgetc(fichier);
            
            if(c == 10){
                i++;
                j = 0;
            }else if (c != -1){
                tab[i][j] = c;
                j++;
            }
        }
    }

    return tab;
}

/**
 * \fn char** modifier_caractere(char** tab, int n, int m, char ancien, char nouveau)
 * \brief Modifier des caractere dans un tableau à 2 dimensions
 * 
 * \return Le tableau avec les caracteres modifié
*/
char** modifier_caractere(char** tab, int n, int m, char ancien, char nouveau){
    char** tabModif = allouer_tab_2D(n, m);
    tabModif = tab;

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if(tabModif[i][j] == ancien){
                tabModif[i][j] = nouveau;
            }
        }
    }
    return tabModif;
}

/**
 * \fn void ecrire_fichier(const char* nomFichier, char** tab, int n, int m)
 * \brief Ecrit dans un fichier texte un tableau à 2 dimensions
*/
void ecrire_fichier(const char* nomFichier, char** tab, int n, int m){
    FILE* fichier = fopen(nomFichier, "w");

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            fputc(tab[i][j], fichier);
        }
        fputc('\n', fichier);
    }

    fclose(fichier);
}