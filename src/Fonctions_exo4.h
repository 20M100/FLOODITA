#ifndef FONCTIONS_EXO4_H
#define FONCTIONS_EXO4_H

#include "Liste_case.h"

typedef struct sommet Sommet;

/* Element d'une liste chainee de pointeurs sur Sommets */
typedef struct cellule_som{
    Sommet *sommet;
    struct cellule_som *suiv;
} Cellule_som;


struct sommet{
    int num;    /* Numero du sommet (affichage uniquement) */
    int cl;     /* Couleur d'origine du sommet-zone */
    ListeCase cases;    /* Liste des cases du sommet-zone */
    int nbcase_som;    /* Nombre de cases de cette liste */

    Cellule_som *sommet_adj; /* Liste des aretes, pointeurs sur les sommets adjacents */
};


typedef struct graphe_zone{
    int nbsom;      /* Nombre de sommets dans le graphe */
    Cellule_som *som;   /* Liste chainee des sommets du graphe */
    Sommet ***mat;  /* Matrice de pointeurs sur les sommets indiquant a quel sommet appartient (i,j) */
} Graphe_zone;


/* Ajoute un pointeur sur Sommet a une liste chainee de Cellule_som passée en paramètre */
void ajoute_liste_sommet(Sommet *S, Cellule_som **L);


/* Détruit une liste chainée de Cellule_som sans détruire les sommets pointés par cette liste */
void detruit_liste_sommet(Cellule_som *L);


/* Met a jour 2 sommets s1 et s2 en indiquant qu'ils sont adjacents l'un de l'autre */
void ajoute_voisin(Sommet *s1, Sommet *s2);


/* Renvoie vrai ssi 2 sommets sont adjacents */
int adjacent(Sommet *s1, Sommet *s2);

/* Crée le graphe de la grille représentée par la matrice M */
void cree_graphe_zone(int **M, int dim, Graphe_zone *GZ);

/* Dessine le graphe vers lequel pointe GZ */
void dessine_graphe(Graphe_zone *GZ, int dim);

#endif //FONCTIONS_EXO4_H
