#include<stdlib.h>
#include "S_Zsg.h"

/* Initialise une Zsg et sa bordure */
void init_Zsg(S_Zsg *zone, int dim, int nbcl){
    zone->dim = dim;
    zone->nbcl = nbcl;
    zone->Lzsg = NULL;
    zone->B = (ListeCase *) malloc(nbcl * sizeof(ListeCase));
    zone->App = malloc(dim * sizeof(int *));
    int i, j;
    for (i=0; i < dim; i++) zone->App[i] = malloc (dim * sizeof(int));
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
void ajoute_bordure(S_Zsg *zone, int i, int j, int cl) {
    ajoute_en_tete(&(zone->B[cl]), i, j);
    zone->App[i][j] = cl;
}

/* Renvoie vrai si une case est dans Lzsg */
int appartient_Zsg(S_Zsg *zone, int i, int j) {
    return (zone->App[i][j] == -1);
}

/* Renvoie vrai si une case est dans la bordure de couleur cl donnée */
int appartient_Bordure(S_Zsg *zone, int i, int j, int cl) {
    return (zone->App[i][j] == cl);
}

/* Met à jour les champs Lzsg et B de Z lorsqu'une case k,l de couleur cl, qui est dans la bordure B[cl], doit basculer dans Lzsg */
int agrandit_Zsg(int **M, S_Zsg *Z, int cl, int k, int l) {

    ListeCase *P = (ListeCase *) malloc(sizeof (ListeCase));
    *P = NULL;                                                           // On initialise un pointeur P vers une Liste vide qu'on appellera pile
    int a = 0;
    int b = 0;
    int cmp = 0;

    ajoute_en_tete(P, k, l);                                             // On empile (i,j)

    while (test_liste_vide(P) != 1){                                      /* Tant que la pile n'est pas vide, on enlève le haut de la pile, on l'ajoute à L
                                                                           et on lui affecte la valeur -1, puis pour toute case existante adjacente à l'élément
                                                                           du haut : si elle est de meme couleur que (i,j), on l'ajoute à la pile si ça n'a pas déjà été fait.
                                                                           Sinon, si elle n'appartient pas encore à la bordure, on l'ajoute. */
        enleve_en_tete(P, &a, &b);
        if (!appartient_Zsg(Z, a, b)) ajoute_Lzsg(Z, a, b);
        cmp++;
        if (b < Z->dim -1 && cl == M[a][b+1] && !appartient_Zsg(Z, a, b+1)){

            ajoute_en_tete(P, a, b+1);
            Z->App[a][b+1] = -1;

        } else if (b < Z->dim -1 && !appartient_Bordure(Z, a, b+1, M[a][b+1]) && !appartient_Zsg(Z, a, b+1)){

            ajoute_bordure(Z, a, b+1, M[a][b+1]);
        }

        if (b > 0 && cl == M[a][b-1] && !appartient_Zsg(Z, a, b-1)){

            ajoute_en_tete(P, a, b-1);
            Z->App[a][b-1] = -1;

        } else if (b > 0 && !appartient_Bordure(Z, a, b-1, M[a][b-1]) && !appartient_Zsg(Z, a, b-1)){

            ajoute_bordure(Z, a, b-1, M[a][b-1]);
        }

        if (a < Z->dim -1 && cl == M[a+1][b] && !appartient_Zsg(Z, a+1, b)){

            ajoute_en_tete(P, a+1, b);
            Z->App[a+1][b] = -1;

        } else if (a < Z->dim -1 && !appartient_Bordure(Z, a+1, b, M[a+1][b]) && !appartient_Zsg(Z, a+1, b)){

            ajoute_bordure(Z, a+1, b, M[a+1][b]);
        }

        if (a > 0 && cl == M[a-1][b] && !appartient_Zsg(Z, a-1, b)){

            ajoute_en_tete(P, a-1, b);
            Z->App[a-1][b] = -1;

        } else if (a > 0 && !appartient_Bordure(Z, a-1, b, M[a-1][b]) && !appartient_Zsg(Z, a-1, b)){

            ajoute_bordure(Z, a-1, b, M[a-1][b]);
        }
    }
    return cmp;
}

int sequence_aleatoire_rapide(int **M, Grille *G, int dim, int nbcl){
    S_Zsg Z;
    init_Zsg(&Z, dim, nbcl);                                                        // On initie une structure Zsg appelée Z
    int t = agrandit_Zsg(M, &Z, M[0][0], 0, 0);                            // On affecte à un entier t la taille de la Zsg au départ
    int cl;
    int cpt = 0;
    ListeCase it;

    while (t < dim*dim){                                                            // Tant que la taille de la Zsg n'est pas celle de la grille, on change aléatoirement la couleur de la Zsg et on met la zone à jour
        cl=rand()%(nbcl);
        if (cl != M[0][0]) {
            cpt++;
            it = Z.Lzsg;                                                            // On affecte à it la liste des cases de la Zsg
            while (it != NULL) {
                M[it->i][it->j] = cl;
                it = it->suiv;
            }
            while (Z.B[cl] != NULL) {
                t += agrandit_Zsg(M, &Z, cl, Z.B[cl]->i, Z.B[cl]->j);               // On met à jour la Zsg en y ajoutant la bordure de couleur cl et toutes les cases adjacentes de couleur cl
                Z.B[cl] = Z.B[cl]->suiv;
            }
            detruit_liste(&(Z.B[cl]));
        }
    }
    return cpt;
}

