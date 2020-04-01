#include<stdlib.h>
#include<math.h>
#include"matrice.h"


void ProduitsMM(Matrice_t A, Matrice_t B, Matrice_t * R) {

    if (A.p == B.n) {

        if (!((*R).n == A.n && (*R).p == B.p)) {
            (*R).n = A.n;
            (*R).p = B.p;
            if ((*R).M != NULL)
                free((*R).M);

            (*R).M = malloc((*R).n*(*R).p * sizeof(double));
        }

        int i, j, k;
        double somme;
        for (i=0; i<A.n; i++)
            for (j=0; j<B.p; j++) {
                somme = 0;
                for (k=0; k<A.p; k++)
                    somme += *(A.M + i*A.n + k) * *(B.M + k*B.n + j);
                *((*R).M + i*(*R).n + j);
            }
    }
}

void ProduitMTM(Matrice_t A, Matrice_t B, Matrice_t * R) {

    if (A.n == B.n) {

        if (!((*R).n == A.p && (*R).p == B.p)) {
            (*R).n = A.p;
            (*R).p = B.p;
            if ((*R).M != NULL)
                free((*R).M);
        
            (*R).M = malloc((*R).n*(*R).p * sizeof(double));
        }

        int i, j, k;
        double somme;
        for (i=0; i<A.p; i++) {
            for (j=0; j<B.p; j++) {
                somme = 0;
                for (k=0; k<A.n; k++)
                    somme += *(A.M + k*A.n + i) * *(B.M + k*B.n + j);
                *((*R).M + i*(*R).n + j);
            }
        }
    }
}

void ProduitMMT(Matrice_t A, Matrice_t B, Matrice_t * R) {

    if (!((*R).n == A.n && (*R).p == B.n)) {
        (*R).n = A.n;
        (*R).p = B.n;

        if ((*R).M != NULL)
            free((*R).M);
    
        (*R).M = malloc((*R).n*(*R).p * sizeof(double));
    }

    int i, j, k;
    double somme;
    for (i=0; i<A.n; i++) {
        for (j=0; j<B.n; j++) {
            somme = 0;
            for (k=0; k<A.p; k++)
                somme += *(A.M + i*A.n + k) * *(B.M + j*B.n + k);
            *((*R).M + i*(*R).n + j);
        }
    }
}

void ProduitsMV(Matrice_t A, Vecteur_t U, Vecteur_t * R) {

    if (A.p == U.n){

        if (!(*R).n == A.n) {
            (*R).n = A.n;

            if ((*R).V != NULL)
                free((*R).V);
        
            (*R).V = malloc((*R).n * sizeof(double));
        }

        int i, k;
        double somme;
        for (i=0; i<A.n; i++) {
            somme = 0;
            for (k=0; k<U.n; k++)
                somme += *(A.M + i*A.n + k) * *(U.V + k);
            *((*R).V + i ) = somme;
        }
    }
}

void ProduitVTV(Vecteur_t U, Vecteur_t V, double * r) {

    if (U.n == V.n) {

        *r = 0;
        
        int i;
        for (i=0; i<U.n; i++)
            *r += *(U.V + i) * *(V.V + i);
    }
}

void ProduitVVT(Vecteur_t U, Vecteur_t V, Matrice_t * R) {

    if (!((*R).n == U.n && (*R).p == V.n))

        (*R).n = U.n;
        (*R).p = V.n;

    if ( (*R).M != NULL)
        free((*R).M);

    (*R).M = malloc((*R).n*(*R).p * sizeof(double));

    int i, j;
    for (i=0; i<U.n; i++) {
        for (j=0; j<V.n; j++)
            *((*R).M + i*(*R).n + j ) = *(U.V + i ) * *(V.V + j);
    }
}


void SommeMM(Matrice_t A, Matrice_t B, Matrice_t * R) {

    if (!(A.n == B.n && A.p == B.p)) {
        
        if (!((*R).n == A.n && (*R).p == A.p)) {
            (*R).n = A.n;
            (*R).p = A.p;

            if ((*R).M != NULL)
                free((*R).M);

            (*R).M = malloc((*R).n * (*R).p * sizeof(double));
        }

        for (int i=0; i<A.n; i++)
            for (int j=0; j<A.p; j++)
                (*R).M[i,j] = A.M[i,j] + B.M[i,j];
    }
}

void SommeVV(Vecteur_t U, Vecteur_t V, Vecteur_t * W) {

    if (U.n == V.n) {

        if (!((*W).n == U.n)) {
            (*W).n = U.n;

            if ((*W).V != NULL)
             free((*W).V);

             (*W).V = malloc(U.n * sizeof(double));
        }

        for (int i=0; i<U.n; i++)
            (*W).V[i] = U.V[i] + V.V[i];

    }

}


void Norme1V (Vecteur_t V, double * ps) {
    ps = 0;

    for (int i=0; i<V.n; i++)
        *ps += fabs(V.V[i]);
}

void Norme2V (Vecteur_t V, double * ps) {
    ps = 0;
    for (int i=0; i<V.n; i++) 
        *ps += V.V[i] * V.V[i];
    *ps = sqrt(*ps);
}


void NormeIV (Vecteur_t V, double * ps) {
    double max = V.V[0];
    for (int i=1; i<V.n; i++)
        if (max < V.V[i])
            max = V.V[i];
    *ps = max;
}

/*
void Norme1M (Matrice_t, double *);
void Norme2M (Matrice_t, double *);
void NormeIM (Matrice_t, double *);
*/