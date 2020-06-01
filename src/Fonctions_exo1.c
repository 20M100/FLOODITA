#include<stdio.h>
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

//Fonction dérécursifiée construisant la zone itération par itération ; la zone sera complète une fois la dernière itération terminée

void trouve_zone_imp(int **M, int nbcase, int i, int j, int *taille, ListeCase *L, ListeCase *B, int tmp){

    if (test_liste_vide(B) == 1) {          // Cas où c'est la première itération de la fonction
        ajoute_en_tete(B, i, j);            // On ajoute i,j  dans B
        tmp = M[i][j];                      // On affecte à tmp la valeur de la couleur de i,j, soit la couleur de notre zone
        ajoute_en_tete(L, i, j);            // On ajoute i,j dans la liste des cases de la zone
        *taille += 1;                       // On incrémente la taille de la zone de 1
        M[i][j] = -1;                       // La case i,j passe à -1
    }

    ListeCase S = NULL;                     // On initialise la liste qui contiendra les bords de notre zone dont la couleur est la bonne

    /* Pour chaque case dans B, si ses cases adjacentes (lorsqu'elles existent) sont de même couleur que la zone et ne sont pas déjà dans L ou S,
     * on les ajoute à L (donc à la zone) et à S, puis on leur affecte la valeur -1 (pour empêcher les doublons) */

    while ((*B) != NULL){
        if ((*B)->j < nbcase -1 && tmp == M[(*B)->i][(*B)->j+1]) {
            ajoute_en_tete(L, (*B)->i, (*B)->j+1);
            *taille += 1;
            ajoute_en_tete(&S, (*B)->i, (*B)->j+1);
            M[(*B)->i][(*B)->j+1] = -1;
        }
        if ((*B)->j > 0 && tmp == M[(*B)->i][(*B)->j-1]) {
            ajoute_en_tete(L, (*B)->i, (*B)->j-1);
            *taille += 1;
            ajoute_en_tete(&S, (*B)->i, (*B)->j-1);
            M[(*B)->i][(*B)->j-1] = -1;
        }
        if ((*B)->i < nbcase -1 && tmp == M[(*B)->i+1][(*B)->j]) {
            ajoute_en_tete(L, (*B)->i+1, (*B)->j);
            *taille += 1;
            ajoute_en_tete(&S, (*B)->i+1, (*B)->j);
            M[(*B)->i+1][(*B)->j] = -1;
        }
        if ((*B)->i > 0 && tmp == M[(*B)->i-1][(*B)->j]) {
            ajoute_en_tete(L, (*B)->i-1, (*B)->j);
            *taille += 1;
            ajoute_en_tete(&S, (*B)->i-1, (*B)->j);
            M[(*B)->i-1][(*B)->j] = -1;
        }

        (*B) = (*B)->suiv;
    }

    /* S contient donc les cases de la bordure de notre zone à l'itération actuelle ayant la même couleur que i,j
     * Si S est vide, alors les bordures de notre zone actuelle sont entièrement d'une couleur différente
     * A celle de la zone. Notre zone est donc complète */

    if (test_liste_vide(&S) == 0) {
        trouve_zone_imp(M, nbcase, i, j, taille, L, &S, tmp);   /* Sinon, il reste des cases adjacentes à notre zone et de même couleur qu'elle,
                                                                 * la zone doit donc être mise à jour ainsi que sa bordure */
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
    ListeCase B;
    init_liste(&B);
    int onsenfout = 5;
    trouve_zone_imp(M, dim, 0, 0, &t, &L, &B, onsenfout);                // On calcule la taille de la Zsg et on affecte ses cases  dans L

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
        detruit_liste(&B);                                               // Idem pour B
        trouve_zone_imp(M, dim, 0, 0, &t, &L, &B, onsenfout);            // On ré-exécute trouve_zone_imp avec la nouvelle matrice
    }

    return cpt;
}


