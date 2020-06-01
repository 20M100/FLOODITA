#include<stdlib.h>
#include "S_Zsg.h"

/* Initialise une Zsg et sa bordure */
void init_Zsg(S_Zsg zone, int dim, int nbcl){
    zone.dim = dim;
    zone.nbcl = nbcl;
    zone.Lzsg = NULL;
    zone.B = (ListeCase *) malloc(nbcl * sizeof(ListeCase));
    int i, j;
    for (i = 0; i < nbcl; i++) zone.B[i] = NULL;

    for (i = 0; i < dim; i++){

        for (j = 0; j < dim; j++){

            zone.App[i][j] = -2;
        }
    }
}

/* Ajoute un element dans la liste Lzsg */
void ajoute_Lzsg(S_Zsg zone, int i, int j){
    ajoute_en_tete(&(zone.Lzsg), i, j);
}

/* Ajoute une case dans la bordure d'une couleur cl donnée */
void ajoute_bordure(S_Zsg zone, int i, int j, int cl){
    ListeCase bordure = zone.B[cl];
    ajoute_en_tete(&bordure, i, j);
}

/* Renvoie vrai si une case est dans Lzsg */
int appartient_Zsg(S_Zsg zone, int i, int j){
    return (zone.App[i][j] == -1);
}

/* Renvoie vrai si une case est dans la bordure de couleur cl donnée */
int appartient_Bordure(S_Zsg zone, int i, int j, int cl){
    return (zone.App[i][j] == cl);
}

/* Met à jour les champs Lzsg et B de Z lorsqu'une case k,l de couleur cl, qui est dans la bordure B[cl], doit basculer dans Lzsg */
int agrandit_Zsg(int **M, S_Zsg *Z, int cl, int k, int l){

}

