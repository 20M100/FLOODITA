#ifndef ENTETE_FONCTIONS_H
#define ENTETE_FONCTIONS_H

#include "API_Grille.h"
#include "Liste_case.h"

/* Retourne dans L la liste des cases de meme couleur que la case i,j
   et met -1 dans ces cases */
void trouve_zone_rec(int **M, int nbcase, int i, int j, int *taille, ListeCase *L);

/* Même chose qu'au-dessus avec un pointeur B vers une ListeCase qui contient la liste des bords de la zone à un instant donné et un int qui
 * sera affecté la valeur de la couleur de i,j */
void trouve_zone_imp(int **M, int nbcase, int i, int j, int *taille, ListeCase *L, ListeCase *B, int cl);

/* Algorithme tirant au sort une couleur: il utilise la fonction recursive pour determiner la Zsg */
int sequence_aleatoire_rec(int **M, Grille *G, int dim, int nbcl, int aff);

int sequence_aleatoire_imp(int **M, Grille *G, int dim, int nbcl, int aff);

#endif  /* __ENTETE_FONCTIONS__ */
