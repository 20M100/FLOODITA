#include <stdlib.h>
#include "Fonctions_exo4.h"
#include "Entete_Fonctions.h"

void ajoute_liste_sommet(Sommet *S, Cellule_som **L){
    Cellule_som *C = malloc(sizeof (Cellule_som));
    C->sommet = S;
    C->suiv = *L;
    *L = C;
}


void detruit_liste_sommet(Cellule_som *L){
    Cellule_som *tmp;
    while (L != NULL){
        tmp = L;
        L = L->suiv;
        free(tmp);
    }
}


void ajoute_voisin(Sommet *s1, Sommet *s2){
    ajoute_liste_sommet(s2, &(s1->sommet_adj));
    ajoute_liste_sommet(s1, &(s2->sommet_adj));
}


int adjacent(Sommet *s1, Sommet *s2){
    int i = 0;
    Cellule_som *cour = s1->sommet_adj;
    while (cour != NULL){
        if (cour->sommet->num == s2->num) i = 1;
        cour = cour->suiv;
    }
    return (i == 1);
}


void cree_graphe_zone(int **M, int dim, Graphe_zone *GZ){
    int i, j;
    GZ->nbsom = 0;                                                           // L41-51 : on initie GZ avec 0 sommet
    GZ->som = NULL;
    GZ->mat = malloc(dim * sizeof(Sommet**));

    for (i = 0; i < dim; i++){
        GZ->mat[i] = malloc(dim * sizeof(Sommet*));
        for (j = 0; j < dim; j++){

            GZ->mat[i][j] = NULL;
        }
    }

    int num = 0;                                                            // Numéro d'affichage des sommets
    int t;                                                                  // Taille d'un sommet
    ListeCase L;                                                            // Liste des cases d'un sommet
    init_liste(&L);
    int **M2 = malloc(dim * sizeof(int *));                                 // Matrice à 2 dimensions qui évitera de modifier M
    for (i = 0; i < dim; i++) M2[i] = malloc(dim * sizeof (int));
    for (i = 0; i < dim; i++){

        for (j = 0; j < dim; j++){
            M2[i][j] = M[i][j];
        }
    }

    for (i = 0; i < dim; i++){                                              // on crée les sommets de la zone

        for (j = 0; j < dim; j++){

            if (GZ->mat[i][j] == NULL){                                      // Si une case n'appartient pas à un sommet
                Sommet *S = malloc(sizeof(Sommet));                         // On le crée
                t = 0;                                                      // On initie sa taille à 0
                trouve_zone_rec(M2, dim, i, j, &t, &L);                      // On détermine la liste des cases de sa zone ainsi que sa taille

                    S->num = num;                                               // On lui affecte les valeurs (sauf la liste de ses voisins)
                    S->cl = M[i][j];
                    S->nbcase_som = t;
                    S->cases = L;
                    S->sommet_adj = NULL;

                    ajoute_liste_sommet(S, &GZ->som);                             // On ajoute le sommet à la liste du graphe
                    GZ->nbsom++;                                                 // Le nombre de sommets augmente donc de 1
                    while (L != NULL) {                                          // On met à jour mat tout en détruisant L pour la prochaine itération
                        GZ->mat[L->i][L->j] = S;
                        L = L->suiv;
                    }
                num++;                                                      // On incrémente num de 1 pour la prochaine itération
            }
        }
    }

    for (i = 1; i < dim; i++){                                             // on indique les sommets voisins

        for (j = 1; j < dim; j++){                                         // On parcourt la partie de la grille allant de (0,1) à (dim-2, dim-1)

/* Pour chacune des cases parcourues, on compare les sommets de la case en question et de celle "au-dessus" ainsi que celle "à droite" */

            if (GZ->mat[i-1][j-1] != GZ->mat[i-1][j] && !adjacent(GZ->mat[i-1][j-1], GZ->mat[i-1][j])){ // comparaison "case du dessus"
                ajoute_voisin(GZ->mat[i-1][j-1], GZ->mat[i-1][j]);      // Ajout dans la liste si sommets différents et pas déjà dans la liste
            }
            if (GZ->mat[i-1][j] != GZ->mat[i][j] && !adjacent(GZ->mat[i-1][j], GZ->mat[i][j])){ // idem avec la "case de droite"
                ajoute_voisin(GZ->mat[i-1][j], GZ->mat[i][j]);
            }
        }
    }
/* Reste a comparer deux à deux les cases allant de (0,0) à (dim-1, 0) puis celles allant de (dim-1, 0) à (dim-1, dim-1) */
    for (i = 1; i < dim; i++){

        if (GZ->mat[i-1][0] != GZ->mat[i][0] && !adjacent(GZ->mat[i-1][0], GZ->mat[i][0])){
            ajoute_voisin(GZ->mat[i-1][0], GZ->mat[i][0]);
        }
    }

    for (j = 1; j < dim; j++){

        if (GZ->mat[dim-1][j-1] != GZ->mat[dim-1][j] && !adjacent(GZ->mat[dim-1][j-1], GZ->mat[dim-1][j])){
            ajoute_voisin(GZ->mat[dim-1][j-1], GZ->mat[dim-1][j]);
        }
    }
}



void dessine_graphe(Graphe_zone *GZ, int dim){
    printf("Le graphe contient %d sommets\n", GZ->nbsom);
    for(Cellule_som *cour= GZ->som; cour != NULL; cour = cour->suiv) {
        Sommet *som = cour->sommet;

        printf("Sommet numero %d\n", som->num);
        printf("Couleur : %d\n", som->cl);
        printf("Nombre de cases : %d\n", som->nbcase_som);

        ListeCase cases = som->cases;

        while(cases != NULL){
            printf("(%d,%d), ", cases->i, cases->j);
            cases = cases->suiv;
        }

        printf("Sommets adjacents : ");

        Cellule_som *adj = som->sommet_adj;

        while(adj != NULL){
            printf("%d, ", adj->sommet->num);
            adj = adj->suiv;
        }
        puts("\n");
    }
}







