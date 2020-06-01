#ifndef S_ZSG_H
#define S_ZSG_H

#include "API_Grille.h"
#include "Liste_case.h"

// Zsg et sa bordure
typedef struct {
    int dim;        // dimension de la grille
    int nbcl;       // nombre de couleurs

    ListeCase Lzsg;     // liste des cases de la zone Zsg
    ListeCase *B;       // tableau de listes de cases de la bordure
    int **App;          // tableau à double entrée des appartenances

} S_Zsg;

/* Initialise une Zsg et sa bordure */
void init_Zsg(S_Zsg *zone, int dim, int nbcl);

/* Ajoute un element dans la liste Lzsg */
void ajoute_Lzsg(S_Zsg *zone, int i, int j);

/* Ajoute une case dans la bordure d'une couleur cl donnée */
void ajoute_bordure(S_Zsg *zone, int i, int j, int cl);

/* Renvoie vrai si une case est dans Lzsg */
int appartient_Zsg(S_Zsg *zone, int i, int j);

/* Renvoie vrai si une case est dans la bordure de couleur cl donnée */
int appartient_Bordure(S_Zsg *zone, int i, int j, int cl);

/* Met à jour les champs Lzsg et B de Z lorsqu'une case k,l de couleur cl, qui est dans la bordure B[cl], doit basculer dans Lzsg */
int agrandit_Zsg(int **M, S_Zsg *Z, int cl, int k, int l);

/* Algorithme tirant au sort une couleur: il utilise la fonction agrandit_Zsg pour determiner la Zsg */
int sequence_aleatoire_rapide(int **M, Grille *G, int dim, int nbcl);

#endif //S_ZSG_H
