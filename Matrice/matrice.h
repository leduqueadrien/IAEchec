#ifndef MATRICE
#define MATRICE

typedef struct Matrice {
    int n;
    int p;
    double *M;
} Matrice_t;

typedef struct Vecteur {
    int n;
    double *V;
} Vecteur_t;

void AfficherM(Matrice_t);
void AfficherV(Vecteur_t);

void ProduitsMM(Matrice_t, Matrice_t, Matrice_t *);
void ProduitMTM(Matrice_t, Matrice_t, Matrice_t *);
void ProduitMMT(Matrice_t, Matrice_t, Matrice_t *);
void ProduitsMV(Matrice_t, Vecteur_t, Vecteur_t *);
void ProduitVTV(Vecteur_t, Vecteur_t, double *);
void ProduitVVT(Vecteur_t, Vecteur_t, Matrice_t *);

/* -------------------------------------------------------- */
/* Somme de 2 matrices de même taille                       */
/* En entrée : A (Matrice_t) : premiere matrice de la somme */
/*             B (Matrice_t) : deuxieme matrice de la somme */
/* -------------------------------------------------------- */
void SommeMM(Matrice_t, Matrice_t, Matrice_t *);

/* -------------------------------------------------------- */
/* Somme de 2 vecteurs de même taille                       */
/* En entrée : V (Vecteur_t) : premier vecteur de la somme  */
/*             W (Vecteur_t) : deuxieme vecteur de la somme */
/* -------------------------------------------------------- */
void SommeVV(Vecteur_t, Vecteur_t, Vecteur_t *);

void Norme1V(Vecteur_t, double *);
void Norme2V(Vecteur_t, double *);
void NormeIV(Vecteur_t, double *);

void Norme1M(Matrice_t, double *);
void Norme2M(Matrice_t, double *);
void NormeIM(Matrice_t, double *);

#endif