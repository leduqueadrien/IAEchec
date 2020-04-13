
#include<stdio.h>
#include<stdlib.h>
#include"echec.h"

void InitialiserPlateau() {
    RemiseAZero();
    int N = 8;
    // Placement des pions
        // Ordinateur
            for (int i=0; i<N; i++)
                PLATEAU[N+i] = Pion;
        // Joueur
            for (int i=0; i<N; i++)
                PLATEAU[6*N+i] = -Pion;

    // Placement des tours
        // Ordinateur
            PLATEAU[0] = Tour;
            PLATEAU[7] = Tour;
        // Joueur
            PLATEAU[N*7] = -Tour;
            PLATEAU[N*8-1] = -Tour;
    
    // Placement des cavaliers
        // Ordinateur
            PLATEAU[1] = Cavalier;
            PLATEAU[N-2] = Cavalier;
        // Joueur
            PLATEAU[N*7+1] = -Cavalier;
            PLATEAU[N*8-2] = -Cavalier;
    
    // Placement des fous
        // Ordinateur
            PLATEAU[2] = Fou;
            PLATEAU[N-3] = Fou;
        // Joueur
            PLATEAU[N*7+2] = -Fou;
            PLATEAU[N*8-3] = -Fou;

    // Placement des dames
        // Ordinateur
            PLATEAU[3] = Dame;
        // Joueur
            PLATEAU[N*7+3] = -Dame;
    
    // Placement des roi
        // Ordinateur
            PLATEAU[N-4] = Roi;
        // Joueur
            PLATEAU[N*8-4] = -Roi;

    // Petit Roque
        // Ordinateur
            peutPROrdi = 1;
        // Joueur
            peutPRJoueur = 1;
    
    // Grand Roque
        // Ordinateur
            peutGROrdi = 1;
        // Joueur
            peutGRJoueur = 1;
}

void RemiseAZero() {
    for (int i=0; i<N*N; i++)
        PLATEAU[i] = 0;
}

char AfficherPiece(int x, int y) {
    switch (abs(PLATEAU[x*N + y]))
    {
    case Pion:
        return 'P';
        break;
    case Tour:
        return 'T';
        break;
    case Cavalier:
        return 'C';
        break;
    case Fou:
        return 'F';
        break;
    case Dame:
        return 'D';
        break;
    case Roi:
        return 'R';
        break;
    default:
        return ' ';
        break;
    }
}

void AfficherPlateau() {

    printf("-----------------\n");

    for (int i=0; i<8; i++) {
        printf("|");
        for (int j=0; j<8; j++)
            printf("%c|",AfficherPiece(i,j));
        printf("\n-----------------\n");
    }
    printf("\n");
}

int * PossibiliterPION(int x, int y) {

    int tabPossibiliter [4][2];
    int nb = 0;

    // Deplacement normal
    if (x+1 < N && PLATEAU[N*(x+1) + y] == 0) {
        tabPossibiliter[nb][0] = x+1;
        tabPossibiliter[nb][1] = y;
        nb ++;
    }

    // Prise normal


    // Deplacement premier coup
    if (x == 1 && PLATEAU[N*(x+2) + y] == 0) {
        tabPossibiliter[nb][0] = x+2;
        tabPossibiliter[nb][1] = y;
        nb ++;
    }

    // Prise normal + Prise en passant
    if (x+1 < N && y-1 >= 0 && (PLATEAU[(x+1)*N+y] == 0 || PLATEAU[x*N+y-1] == 0)) {
        tabPossibiliter[nb][0] = x+1;
        tabPossibiliter[nb][1] = y-1;
        nb++;
    }
    
    if (x+1 < N && y+1 >= 0 && (PLATEAU[(x+1)*N+y] == 0 || PLATEAU[x*N+y+1] == 0)) {
        tabPossibiliter[nb][0] = x+1;
        tabPossibiliter[nb][1] = y+1;
        nb++;
    }

    tabPossibiliter[nb][0] = -1;
    tabPossibiliter[nb][1] = -1;

    return tabPossibiliter;
}

int * PossibiliterTOUR(int x, int y) {
    int tabPossibiliter [4][2];
    int nb = 0;
    int i;
    int j;

    // Haut
    i = x;
    do {
        i--;
        // Si la piece n'est pas une piece allier
        if (PLATEAU[N*i+y] <= 0) {
            tabPossibiliter[nb][0] = i;
            tabPossibiliter[nb][1] = y;
            nb++;
        }
    } while (i>=0 && PLATEAU[N*i+y] == 0);


    // Bas
    i = x;
    do {
        i++;
        // Si la piece n'est pas une piece allier
        if (PLATEAU[N*i+y] <= 0) {
            tabPossibiliter[nb][0] = i;
            tabPossibiliter[nb][1] = y;
            nb++;
        }
    } while (i<N && PLATEAU[N*i+y]);

    // Gauche
    j = y;
    do {
        j--;
        // Si la piece n'est pas une piece allier
        if (PLATEAU[N*x+j]) {
            tabPossibiliter[nb][0] = x;
            tabPossibiliter[nb][1] = j;
            nb++;
        }
    } while (j>=0 && PLATEAU[N*x+j]);

    // Droite
    j = y;
    do {
        j++;
        // Si la piece n'est pas une piece allier
        if (PLATEAU[N*i+j]) {
            tabPossibiliter[nb][0] = x;
            tabPossibiliter[nb][1] = j;
            nb++;
        }
    } while (j<N && PLATEAU[N*x+j]);


    tabPossibiliter[nb][0] = -1;
    tabPossibiliter[nb][1] = -1;

    return tabPossibiliter;
}

