#include <stdio.h>
#include "Entete_Fonctions.h"

void trouve_zone_rec(int **M, int nbcase, int i, int j, int *taille, ListeCase *L){

    ajoute_en_tete(L, i, j);                                             // Affection de la case (i,j) dans L 
    *taille += 1;                                                        // On incrémente taille de 1 
    int tmp = M[i][j];
    M[i][j] = -1;                                                        // Valeur de (i,j) mise à -1 

    // On ré-exécute la fonction pour toute case de la grille adjacente à (i,j) et de même couleur

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


void trouve_zone_imp(int **M, int nbcase, int i, int j, int *taille, ListeCase *L){

    ListeCase *P = malloc(sizeof (ListeCase));
    *P = NULL;                                                           // On initialise un pointeur P vers une Liste vide qu'on appellera pile
    int a = 0;
    int b = 0;
    int cl = M[i][j];                                                    // On affecte à cl la valeur de la couleur de (i,j)
    M[i][j] = -1;

    ajoute_en_tete(P, i, j);                                             // On empile (i,j)

                                                                         /* Tant que la pile n'est pas vide, on enlève le haut de la pile,
                                                                          * on l'ajoute à L, on incrémente la taille de la zone de 1 puis
                                                                          * pour chaque case existante adjacente à l'élément du haut de la pile
                                                                          * si elle est de meme couleur que la zone, on l'empile et on passe
                                                                          * sa valeur à -1 pour éviter de l'empiler plusieurs fois. */
    while(test_liste_vide(P) != 1) {
        enleve_en_tete(P, &a, &b);
        ajoute_en_tete(L, a, b);
        *taille += 1;
        if (b < nbcase -1 && cl == M[a][b+1]){
            ajoute_en_tete(P, a, b+1);
            M[a][b+1] = -1;

        }
        if (b > 0 && cl == M[a][b-1]){
            ajoute_en_tete(P, a, b-1);
            M[a][b-1] = -1;
        }
        if (a < nbcase -1 && cl == M[a+1][b]){
            ajoute_en_tete(P, a+1, b);
            M[a+1][b] = -1;
        }
        if (a > 0 && cl == M[a-1][b]){
            ajoute_en_tete(P, a-1, b);
            M[a-1][b] = -1;
        }
    }
}



int sequence_aleatoire_rec(int **M, Grille *G, int dim, int nbcl, int aff){

    int cpt=0;                                                           // Nombre de changements de couleur (!= Zsg) nécessaires pour gagner
    int t = 0;                                                           // Taille de la Zsg
    int c;                                                               // Numéro de la nouvelle couleur attribuée
    int cl;
    ListeCase L;
    ListeCase it;
    init_liste(&L);
    trouve_zone_rec(M, dim, 0, 0, &t, &L);                          // On calcule la taille de la Zsg et on affecte ses cases  dans L

    while (t < dim*dim) {                                                // Tant que la Zsg ne remplit pas la grille, on affecte une nouvelle couleur


        t = 0;
        c=rand()%(nbcl);
        cl = M[0][0];                                                    // On affecte à cl la valeur de la couleur de la case (0,0)

        it = L;
        if (c != cl) {
            cpt++;                                                       // On augmente cpt si la nouvelle couleur est différente de celle de la Zsg
            while (it != NULL) {
               if (aff == 1) Grille_attribue_couleur_case(G, it->i, it->j, c);        // On change la couleur des cases de la Zsg si nécessaire
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


int sequence_aleatoire_imp(int **M, Grille *G, int dim, int nbcl, int aff) {

    int cpt=0;                                                           // Nombre de changements de couleur (!= Zsg) nécessaires pour gagner
    int t = 0;                                                           // Taille de la Zsg
    int c;                                                               // Numéro de la nouvelle couleur attribuée
    int cl;
    ListeCase L;
    ListeCase it;
    init_liste(&L);
    trouve_zone_imp(M, dim, 0, 0, &t, &L);                          // On calcule la taille de la Zsg et on affecte ses cases  dans L

    while (t < dim*dim) {                                                // Tant que la Zsg ne remplit pas la grille, on affecte une nouvelle couleur


        t = 0;
        c=rand()%(nbcl);
        cl = M[0][0];                                                    // On affecte à cl la valeur de la couleur de la case (0,0)

        it = L;
        if (c != cl) {
            cpt++;                                                       // On augmente cpt si la nouvelle couleur est différente de celle de la Zsg
            while (it != NULL) {
                if (aff == 1) Grille_attribue_couleur_case(G, it->i, it->j, c);        // On change la couleur des cases de la Zsg si nécessaire
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




// Fonction récursive terminale que j'ai faite par accident pour l'exercice 2


void trouve_zone_derec(int **M, int nbcase, int i, int j, int *taille, ListeCase *L, ListeCase *B, int cl){

    if (test_liste_vide(B) == 1) {          // Cas où c'est la première itération de la fonction
        ajoute_en_tete(B, i, j);            // On ajoute i,j  dans B
        cl = M[i][j];                      // On affecte à tmp la valeur de la couleur de i,j, soit la couleur de notre zone
        ajoute_en_tete(L, i, j);            // On ajoute i,j dans la liste des cases de la zone
        *taille += 1;                       // On incrémente la taille de la zone de 1
        M[i][j] = -1;                       // La case i,j passe à -1
    }

    ListeCase S = NULL;                     // On initialise la liste qui contiendra les bords de notre zone dont la couleur est la bonne

    // Pour chaque case dans B, si ses cases adjacentes (lorsqu'elles existent) sont de même couleur que la zone et ne sont pas déjà dans L ou S,
    // on les ajoute à L (donc à la zone) et à S, puis on leur affecte la valeur -1 (pour empêcher les doublons)

    while ((*B) != NULL){
        if ((*B)->j < nbcase -1 && cl == M[(*B)->i][(*B)->j+1]) {
            ajoute_en_tete(L, (*B)->i, (*B)->j+1);
            *taille += 1;
            ajoute_en_tete(&S, (*B)->i, (*B)->j+1);
            M[(*B)->i][(*B)->j+1] = -1;
        }
        if ((*B)->j > 0 && cl == M[(*B)->i][(*B)->j-1]) {
            ajoute_en_tete(L, (*B)->i, (*B)->j-1);
            *taille += 1;
            ajoute_en_tete(&S, (*B)->i, (*B)->j-1);
            M[(*B)->i][(*B)->j-1] = -1;
        }
        if ((*B)->i < nbcase -1 && cl == M[(*B)->i+1][(*B)->j]) {
            ajoute_en_tete(L, (*B)->i+1, (*B)->j);
            *taille += 1;
            ajoute_en_tete(&S, (*B)->i+1, (*B)->j);
            M[(*B)->i+1][(*B)->j] = -1;
        }
        if ((*B)->i > 0 && cl == M[(*B)->i-1][(*B)->j]) {
            ajoute_en_tete(L, (*B)->i-1, (*B)->j);
            *taille += 1;
            ajoute_en_tete(&S, (*B)->i-1, (*B)->j);
            M[(*B)->i-1][(*B)->j] = -1;
        }

        (*B) = (*B)->suiv;
    }

    // S contient donc les cases de la bordure de notre zone à l'itération actuelle ayant la même couleur que i,j
    // Si S est vide, alors les bordures de notre zone actuelle sont entièrement d'une couleur différente
    // A celle de la zone. Notre zone est donc complète

    if (test_liste_vide(&S) == 0) {
        trouve_zone_derec(M, nbcase, i, j, taille, L, &S, cl);   // Sinon, il reste des cases adjacentes à notre zone et de même couleur qu'elle,
        // la zone doit donc être mise à jour ainsi que sa bordure
    }
}