#include<stdio.h>
#include "Entete_Fonctions.h"

void trouve_zone_rec(int **M, int nbcase, int i, int j, int *taille, ListeCase *L){

    ajoute_en_tete(L, i, j);                                             // Affection de la case (i,j) dans L 
    *taille += 1;                                                        // On incrémente taille de 1 
    int tmp = M[i][j];
    M[i][j] = -1;                                                        // Valeur de (i,j) mise à -1 

    // On ré-exécute la fonction pour toute case adjacente à (i,j) et de même couleur 

    if (j < nbcase && tmp == M[i][j+1]) {
        trouve_zone_rec(M, nbcase, i, j+1, taille, L);
    }

    if (j > 0 && tmp == M[i][j-1]) {
        trouve_zone_rec(M, nbcase, i, j-1, taille, L);
    }

    if (i < nbcase && tmp == M[i+1][j]) {
        trouve_zone_rec(M, nbcase, i+1, j, taille, L);
    }

    if (i > 0 && tmp == M[i-1][j]) {
        trouve_zone_rec(M, nbcase, i-1, j, taille, L);
    }
}
/*
int nop_sequence_aleatoire_rec(int **M, Grille *G, int dim, int nbcl, int aff) {
    return 0;
}*/

int sequence_aleatoire_rec(int **M, Grille *G, int dim, int nbcl, int aff){

    int cpt=0;                                                           // Nombre de changements de couleur (!= Zsg) nécessaires pour gagner
    int t = 0;                                                           // Taille de la Zsg 
    int c;                                                               // Numéro de la nouvelle couleur attribuée 
    int tmp;
    ListeCase L;
    ListeCase TMP;
    init_liste(&L);
    trouve_zone_rec(M, dim, 0, 0, &t, &L);                                // On calcule la taille de la Zsg et on affecte ses cases  dans L

    while (t < dim*dim) {                                                // Tant que la Zsg ne remplit pas la grille, on affecte une nouvelle couleur
        t = 0;
        TMP = L;
        c=rand()%(nbcl);
        tmp = M[0][0];

        if (c != tmp) {
            cpt++;                                                       // On augmente cpt si la nouvelle couleur est différente de celle de la Zsg 
            while (L != NULL) {
                Grille_attribue_couleur_case(G, L->i, L->j, c);    // On change la couleur des cases de la Zsg si nécessaire
                M[L->i][L->j] = c;                                 // On met à jour la matrice de la grille 
                L = L->suiv;
            }
        } else {
            while (L != NULL) {
                M[L->i][L->j] = c;
                L =L->suiv;
            }
        }

        if (aff == 1) {                                                  // On réaffiche la grille après modif. si demandé
            Grille_redessine_Grille(G);
            Grille_attente_touche(G);
            Grille_ferme_fenetre();
        }

        L = TMP;
        detruit_liste(&L);                                                // On détruit la liste contenant l'ancienne Zsg
        trouve_zone_rec(M, dim, 0, 0, &t, &L);                            // On ré-exécute trouve_zone_rec avec la nouvelle matrice
    }

    return cpt;
}


