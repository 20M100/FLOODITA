#ifndef ENTETE_FONCTIONS_H
#define ENTETE_FONCTIONS_H

#include "API_Grille.h"
#include "Liste_case.h"

/* Retourne dans L la liste des cases de meme couleur que la case i,j
   et met -1 dans ces cases */
void trouve_zone_rec(int **M, int nbcase, int i, int j, int *taille, ListeCase *L);


/* Version dérécursifiée */
void trouve_zone_imp(int **M, int nbcase, int i, int j, int *taille, ListeCase *L);

/* Algorithme tirant au sort une couleur: il utilise la fonction recursive pour determiner la Zsg */
int sequence_aleatoire_rec(int **M, Grille *G, int dim, int nbcl, int aff);

/* Version qui utilise trouve_zone_imp */
int sequence_aleatoire_imp(int **M, Grille *G, int dim, int nbcl, int aff);

/* Fonction dérécursifiée construisant la zone itération par itération ; la zone sera complète une fois la dernière itération terminée */
void trouve_zone_derec(int **M, int nbcase, int i, int j, int *taille, ListeCase *L, ListeCase *B, int cl);
#endif  /* __ENTETE_FONCTIONS__ */
