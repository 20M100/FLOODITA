#include<stdlib.h>
#include "S_Zsg.h"

/* Initialise une Zsg et sa bordure */
void init_Zsg(S_Zsg *zone, int dim, int nbcl){
    zone->dim = dim;
    zone->nbcl = nbcl;
    zone->Lzsg = NULL;
    zone->B = (ListeCase *) malloc(nbcl * sizeof(ListeCase));
    int i, j;
    for (i = 0; i < nbcl; i++) zone->B[i] = NULL;

    for (i = 0; i < dim; i++){

        for (j = 0; j < dim; j++){

            zone->App[i][j] = -2;
        }
    }
}

/* Ajoute un element dans la liste Lzsg */
void ajoute_Lzsg(S_Zsg *zone, int i, int j){
    ajoute_en_tete(&(zone->Lzsg), i, j);
    zone->App[i][j] = -1;
}

/* Ajoute une case dans la bordure d'une couleur cl donnée */
void ajoute_bordure(S_Zsg *zone, int i, int j, int cl){
    ListeCase bordure = zone->B[cl];
    ajoute_en_tete(&bordure, i, j);
    zone->App[i][j] = cl;
}

/* Renvoie vrai si une case est dans Lzsg */
int appartient_Zsg(S_Zsg *zone, int i, int j){
    return (zone->App[i][j] == -1);
}

/* Renvoie vrai si une case est dans la bordure de couleur cl donnée */
int appartient_Bordure(S_Zsg *zone, int i, int j, int cl){
    return (zone->App[i][j] == cl);
}

/* Met à jour les champs Lzsg et B de Z lorsqu'une case k,l de couleur cl, qui est dans la bordure B[cl], doit basculer dans Lzsg */
int agrandit_Zsg(int **M, S_Zsg *Z, int cl, int k, int l){

    ListeCase *P = (ListeCase *) malloc(sizeof (ListeCase));
    *P = NULL;                                                           // On initialise un pointeur P vers une Liste vide qu'on appellera pile
    int *a = NULL;
    int *b = NULL;
    int cmp = 0;

    ajoute_en_tete(P, k, l);                                             // On empile (i,j)

    while (test_liste_vide(P)!= 0){                                      /* Tant que la pile n'est pas vide, on enlève le haut de la pile,
                                                                           on l'ajoute à L et on lui affecte la valeur -1, puis on ajoute
                                                                           à la pile toute case existante adjacente à l'élément du haut
                                                                           et de même couleur que (i,j) */
        enleve_en_tete(P, a, b);
        if (Z->App[*a][*b] != -1) ajoute_Lzsg(Z, *a, *b);
        cmp++;
        if (*b < Z->dim -1 && cl == M[*a][*b+1] && Z->App[*a][*b+1] != -1){

            ajoute_en_tete(P, *a, *b+1);

        } else if (*b < Z->dim -1 && Z->App[*a][*b+1] != M[*a][*b+1] && Z->App[*a][*b+1] != -1){

            ajoute_bordure(Z, *a, *b+1, M[*a][*b+1]);
        }

        if (*b > 0 && cl == M[*a][*b-1] && Z->App[*a][*b-1] != -1){

            ajoute_en_tete(P, *a, *b-1);

        } else if (*b > 0 && (Z->App[*a][*b-1] != M[*a][*b-1] && Z->App[*a][*b-1] != -1)){

            ajoute_bordure(Z, *a, *b-1, M[*a][*b-1]);
        }

        if (*a < Z->dim -1 && cl == M[*a+1][*b] && Z->App[*a+1][*b] != -1){

            ajoute_en_tete(P, *a+1, *b);

        } else if (*a < Z->dim -1 && Z->App[*a+1][*b] != M[*a+1][*b] && Z->App[*a+1][*b] != -1){

            ajoute_bordure(Z, *a+1, *b, M[*a+1][*b]);
        }

        if (*a > 0 && cl == M[*a-1][*b] && Z->App[*a-1][*b] != -1){

            ajoute_en_tete(P, *a-1, *b);

        } else if (*a > 0 && Z->App[*a-1][*b] != M[*a-1][*b] && Z->App[*a-1][*b] != -1){

            ajoute_bordure(Z, *a-1, *b, M[*a-1][*b]);
        }
    }
    return cmp;
}

int sequence_aleatoire_rapide(int **M, Grille *G, int dim, int nbcl){
    S_Zsg Z;
    init_Zsg(&Z, dim, nbcl);
    int t = agrandit_Zsg(M, &Z, M[0][0], 0, 0);
    int c;
    int cpt = 0;
    ListeCase it;

    while (t < dim*dim){
        c=rand()%(nbcl);
        if (c != M[0][0]) {
            cpt++;
            it = Z.Lzsg;
            while (it != NULL) {
                Grille_attribue_couleur_case(G, it->i, it->j, c);
                M[it->i][it->j] = c;
                it = it->suiv;
            }
            while (Z.B[c] != NULL) {
                t += agrandit_Zsg(M, &Z, c, Z.B[c]->i, Z.B[c]->j);
                Z.B[c] = Z.B[c]->suiv;
            }
            detruit_liste(&(Z.B[c]));
        }
    }
    return cpt;
}

