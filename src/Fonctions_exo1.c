#include <stdio.h>
#include "Entete_Fonctions.h"

void trouve_zone_rec(int **M, int nbcase, int i, int j, int *taille, ListeCase *L){

    ajoute_en_tete(L, i, j);                                             // Affection de la case (i,j) dans L 
    *taille += 1;                                                        // On incrémente taille de 1 
    int tmp = M[i][j];
    M[i][j] = -1;                                                        // Valeur de (i,j) mise à -1 

    // On ré-exécute la fonction pour toute case adjacente à (i,j) et de même couleur 

    if (j < nbcase -1 && tmp == M[i][j+1]) {
        trouve_zone_rec(M, nbcase, i, j+1, taille, L);
    }

    if (j > 0 && tmp == M[i][j-1]) {
        trouve_zone_rec(M, nbcase, i, j-1, taille, L);
    }

    if (i < nbcase -1 && tmp == M[i+1][j]) {
        trouve_zone_rec(M, nbcase, i+1, j, taille, L);
    }

    if (i > 0 && tmp == M[i-1][j]) {
        trouve_zone_rec(M, nbcase, i-1, j, taille, L);
    }
}

void print_mat(int** M, int taille) {

    for(int i = 0; i < taille; ++i) {
        printf("-");
    }
    printf("\n");

    for(int i = 0; i < taille; ++i) {
        printf("|");
        for(int j = 0; j < taille; ++j) {
            if(M[i][j] == -1) {
                printf("#");
            } else {
                printf("O");
            }
        }
        printf("|\n");
    }

    for(int i = 0; i < taille; ++i) {
        printf("-");
    }
    printf("\n");
}

void trouve_zone_imp(int **M, int nbcase, int i, int j, int *taille, ListeCase *L){

    ListeCase *P = malloc(sizeof (ListeCase));
    *P = NULL;                                                           // On initialise un pointeur P vers une Liste vide qu'on appellera pile
    int a = 0;
    int b = 0;
    int tmp = M[i][j];                                                   // On affecte à tmp la valeur de la couleur de (i,j)
    M[i][j] = -1;

    ajoute_en_tete(P, i, j);                                             // On empile (i,j)

    while(test_liste_vide(P) != 1) {                                      /* Tant que la pile n'est pas vide, on enlève le haut de la pile,0.*/
        enleve_en_tete(P, &a, &b);
        ajoute_en_tete(L, a, b);
        *taille += 1;
        if (b < nbcase -1 && tmp == M[a][b+1]){
            ajoute_en_tete(P, a, b+1);
            M[a][b+1] = -1;

        }
        if (b > 0 && tmp == M[a][b-1]){
            ajoute_en_tete(P, a, b-1);
            M[a][b-1] = -1;
        }
        if (a < nbcase -1 && tmp == M[a+1][b]){
            ajoute_en_tete(P, a+1, b);
            M[a+1][b] = -1;
        }
        if (a > 0 && tmp == M[a-1][b]){
            ajoute_en_tete(P, a-1, b);
            M[a-1][b] = -1;
        }
    }
}



int sequence_aleatoire_rec(int **M, Grille *G, int dim, int nbcl, int aff){

    int cpt=0;                                                           // Nombre de changements de couleur (!= Zsg) nécessaires pour gagner
    int t = 0;                                                           // Taille de la Zsg
    int c;                                                               // Numéro de la nouvelle couleur attribuée
    int tmp;
    ListeCase L;
    ListeCase it;
    init_liste(&L);
    trouve_zone_rec(M, dim, 0, 0, &t, &L);                               // On calcule la taille de la Zsg et on affecte ses cases  dans L

    while (t < dim*dim) {                                                // Tant que la Zsg ne remplit pas la grille, on affecte une nouvelle couleur


        t = 0;
        c=rand()%(nbcl);
        tmp = M[0][0];

        it = L;
        if (c != tmp) {
            cpt++;                                                       // On augmente cpt si la nouvelle couleur est différente de celle de la Zsg
            while (it != NULL) {
                Grille_attribue_couleur_case(G, it->i, it->j, c);        // On change la couleur des cases de la Zsg si nécessaire
                M[it->i][it->j] = c;                                     // On met à jour la matrice de la grille
                it = it->suiv;
            }
        } else {
            while (it != NULL) {
                M[it->i][it->j] = c;
                it = it->suiv;
            }
        }

        if (aff == 1) {                                                  // On réaffiche la grille après modif. si demandé
            Grille_redessine_Grille(G);
            Grille_attente_touche(G);
        }

        detruit_liste(&L);                                               // On détruit la liste contenant l'ancienne Zsg
        trouve_zone_rec(M, dim, 0, 0, &t, &L);                           // On ré-exécute trouve_zone_rec avec la nouvelle matrice
    }

    return cpt;
}


int sequence_aleatoire_imp(int **M, Grille *G, int dim, int nbcl, int aff){

    int cpt=0;                                                           // Nombre de changements de couleur (!= Zsg) nécessaires pour gagner
    int t = 0;                                                           // Taille de la Zsg
    int c;                                                               // Numéro de la nouvelle couleur attribuée
    int tmp;
    ListeCase L;
    ListeCase it;
    init_liste(&L);
    trouve_zone_imp(M, dim, 0, 0, &t, &L);                               // On calcule la taille de la Zsg et on affecte ses cases  dans L

    while (t < dim*dim) {                                                // Tant que la Zsg ne remplit pas la grille, on affecte une nouvelle couleur


        t = 0;
        c=rand()%(nbcl);
        tmp = M[0][0];

        it = L;
        if (c != tmp) {
            cpt++;                                                       // On augmente cpt si la nouvelle couleur est différente de celle de la Zsg
            while (it != NULL) {
                Grille_attribue_couleur_case(G, it->i, it->j, c);        // On change la couleur des cases de la Zsg si nécessaire
                M[it->i][it->j] = c;                                     // On met à jour la matrice de la grille
                it = it->suiv;
            }
        } else {
            while (it != NULL) {
                M[it->i][it->j] = c;
                it = it->suiv;
            }
        }

        if (aff == 1) {                                                  // On réaffiche la grille après modif. si demandé
            Grille_redessine_Grille(G);
            Grille_attente_touche(G);
        }

        detruit_liste(&L);                                               // On détruit la liste contenant l'ancienne Zsg
        trouve_zone_imp(M, dim, 0, 0, &t, &L);                           // On ré-exécute trouve_zone_rec avec la nouvelle matrice
    }

    return cpt;
}
