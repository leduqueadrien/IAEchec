#include<stdlib.h>
#include"matrice.h"


void ProduitsMM (Matrice_t A, Matrice_t B, Matrice_t * R){
    if (A.p == B.n){
        (*R).n = A.n;
        (*R).p = B.p;

        if ( (*R).M != NULL)
            free((*R).M);
        (*R).M = malloc((*R).n*(*R).p * sizeof(double));

        int i, j, k;
        double somme;
        for (i=0; i<A.n; i++){
            for (j=0; j<B.p; j++){
                somme = 0;
                for (k=0; k<A.p; k++){
                    somme += *(A.M + i*A.n + k) * *(B.M + k*B.n + j);
                }
                *( (*R).M + i*(*R).n + j);
            }
        }

    }
}

void ProduitMTM (Matrice_t A, Matrice_t B, Matrice_t * R){
        if (A.n == B.n){
        (*R).n = A.p;
        (*R).p = B.p;

        if ( (*R).M != NULL)
            free((*R).M);
        (*R).M = malloc((*R).n*(*R).p * sizeof(double));

        int i, j, k;
        double somme;
        for (i=0; i<A.p; i++){
            for (j=0; j<B.p; j++){
                somme = 0;
                for (k=0; k<A.n; k++){
                    somme += *(A.M + k*A.n + i) * *(B.M + k*B.n + j);
                }
                *( (*R).M + i*(*R).n + j);
            }
        }

    }
}

void ProduitMMT (Matrice_t A, Matrice_t B, Matrice_t * R){
        if (A.p == B.p){
        (*R).n = A.n;
        (*R).p = B.n;

        if ( (*R).M != NULL)
            free((*R).M);
        (*R).M = malloc((*R).n*(*R).p * sizeof(double));

        int i, j, k;
        double somme;
        for (i=0; i<A.n; i++){
            for (j=0; j<B.n; j++){
                somme = 0;
                for (k=0; k<A.p; k++){
                    somme += *(A.M + i*A.n + k) * *(B.M + j*B.n + k);
                }
                *( (*R).M + i*(*R).n + j);
            }
        }

    }
}

void ProduitsMV (Matrice_t A, Vecteur_t V, Vecteur_t * R){
    if (A.p == V.n){
        (*R).n = A.n;

        if ( (*R).V != NULL)
            free((*R).V);
        (*R).V = malloc((*R).n * sizeof(double));

        int i, k;
        double somme;
        for (i=0; i<A.n; i++){
            somme = 0;
            for (k=0; k<V.n; k++){
                somme += *(A.M + i*A.n + k) * *(V.V + k);
            }
            *( (*R).V + i ) = somme;
        }
    }
}

void ProduitVTV (Vecteur_t V, Vecteur_t W, double * r){
    if (V.n == W.n){
        *r = 0;
        
        int i;
        for (i=0; i<V.n; i++)
            *r += *( V.V + i) * *( W.V + i);
    }
}

void ProduitVVT (Vecteur_t V, Vecteur_t W, Matrice_t * R){
    (*R).n = V.n;
    (*R).p = W.n;

    if ( (*R).M != NULL)
        free((*R).M);
    (*R).M = malloc((*R).n*(*R).p * sizeof(double));

    int i, j;
    for (i=0; i<V.n; i++){
        for (j=0; j<W.n; j++){
            *( (*R).M + i*(*R).n + j ) = *( V.V + i ) * *(W.V + j);
        }
    }
}

void SommeMM (Matrice_t, Matrice_t, Matrice_t);
void SommeVV (Vecteur_t, Vecteur_t, Vecteur_t);

void Norme1V (Vecteur_t, double);
void Norme2V (Vecteur_t, double);
void NormeIV (Vecteur_t, double);

void Norme1M (Matrice_t, double);
void Norme2M (Matrice_t, double);
void NormeIM (Matrice_t, double);