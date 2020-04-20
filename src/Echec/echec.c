
#include<stdio.h>
#include<stdlib.h>
#include"echec.h"

Plateau_t plateau;
Roque_t roque;
CoupPrecedent_t coupPrecedent;


void Initialiser() {
    InitialiserPlateau();
    InitialiserRoque();
    InitialiserCoupPrecedent();
}

void InitialiserPlateau() {
    plateau.N = 8;
    int * tab [plateau.N*plateau.N];
    plateau.tab = tab;
    RemiseAZero();
    plateau.couleurOrdi = "blanc";
}

void InitialiserRoque() {
    roque.peutGRJoueur = 1;
    roque.peutGROrdi = 1;
    roque.peutPRJoueur = 1;
    roque.peutPROrdi = 1;
}

void InitialiserCoupPrecedent() {
    coupPrecedent.xApres = -1;
    coupPrecedent.xAvant = -1;
    coupPrecedent.yApres = -1;
    coupPrecedent.yAvant = -1;
}

void InitialiserDebutPartie() {
    int N = plateau.N;
    int * PLATEAU = plateau.tab;

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
            roque.peutPROrdi = 1;
        // Joueur
            roque.peutPRJoueur = 1;
    
    // Grand Roque
        // Ordinateur
            roque.peutGROrdi = 1;
        // Joueur
            roque.peutGRJoueur = 1;
}

void RemiseAZero() {
    int N = plateau.N;
    for (int i=0; i<N*N; i++)
        plateau.tab[i] = 0;
}

char AfficherPiece(int x, int y) {
    switch (abs(plateau.tab[x*plateau.N + y]))
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

int PossibiliterPION(int * tabPossibiliter, int x, int y) {
    int nb = 0;
    int priseRoi = 0;
    int N = plateau.N;
    int * PLATEAU = plateau.tab;

    // Deplacement normal
    if (x+1 < N && PLATEAU[N*(x+1) + y] == 0) {
        tabPossibiliter[2*nb] = x+1;
        tabPossibiliter[2*nb+1] = y;
        nb ++;
    }

    // Prise normal


    // Deplacement premier coup
    if (x == 1 && PLATEAU[N*(x+2) + y] == 0) {
        tabPossibiliter[2*nb] = x+2;
        tabPossibiliter[2*nb+1] = y;
        nb ++;
    }

    // Prise normal
    if (x+1 < N) {
        if (y-1 >= 0 && PLATEAU[(x+1)*N + y-1] <= 0) {
            if (PLATEAU[(x+1)*N + y-1] == -Roi) {
                priseRoi = 1;
            } else {
                tabPossibiliter[2*nb] = x+1;
                tabPossibiliter[2*nb+1] = y-1;
                nb ++;
            }
        }
        if (y+1 < N && PLATEAU[(x+1)*N + y+1] <+ 0) {
            if (PLATEAU[(x+1)*N + y+1] == -Roi) {
                priseRoi = 1;
            } else {
                tabPossibiliter[2*nb] = x+1;
                tabPossibiliter[2*nb+1] = y+1;
                nb ++;
            }
        }
    }

    tabPossibiliter[2*nb] = -1;
    tabPossibiliter[2*nb+1] = -1;

    return priseRoi;
}

int PossibiliterTOUR(int * tabPossibiliter, int x, int y) {
    int nb = 0;
    int priseRoi = 0;
    int N = plateau.N;
    int * PLATEAU = plateau.tab;

    // Haut et Bas
    // Si signe=-1 alors, on parcour vers le Haut
    // Si signe=1 alors, on parcour cers le Bas
    for (int signe=-1; signe<=1; signe+=2) {
        int i = x;
        do {
            i+=signe;
            // Si la piece n'est pas une piece allier
            if (i>=0 && i<N && PLATEAU[N*i+y] <= 0) {
                if (PLATEAU[N*i+y] == -Roi) {
                    priseRoi = 1;
                } else {
                    tabPossibiliter[2*nb] = i;
                    tabPossibiliter[2*nb+1] = y;
                    nb++;
                }
            }
        } while (i>=0 && i<N && PLATEAU[N*i+y] == 0);
    }

    // Gauche et Droite
    // Si signe=-1 alors, on parcour vers la Gauche
    // Si signe=1 alors, on parcour vers la Droite
    for (int signe=-1; signe<+1; signe+=2) {
        int j = y;
        do {
            j+=signe;
            // Si la piece n'est pas une piece allier
            if (j>=0 && j<N && PLATEAU[N*x+j]) {
                if (PLATEAU[N*x+j] == -Roi) {
                    priseRoi = 1;
                } else {
                    tabPossibiliter[2*nb] = x;
                    tabPossibiliter[2*nb+1] = j;
                    nb++;
                }
            }
        } while (j>=0 && j<N && PLATEAU[N*x+j]);
    }

    tabPossibiliter[2*nb] = -1;
    tabPossibiliter[2*nb+1] = -1;

    return priseRoi;
}

int PossibiliterCAVALIER(int * tabPossibiliter, int x, int y) {
    int nb = 0;
    int priseRoi = 0;
    int N = plateau.N;
    int * PLATEAU = plateau.tab;

    for (int i=-2; i<=2; i+=4) {
        for (int j=-1; j<=1; j+=2) {
            if (x+i >= 0 && x+i < N && y+j >= 0 && y+j < N) {
                if (PLATEAU[(x+i)*N + y+j]) {
                    if (PLATEAU[(x+i)*N + y+j] == -Roi) {
                        priseRoi = 1;
                    } else {
                        tabPossibiliter[2*nb] = x+i;
                        tabPossibiliter[2*nb+1] = y+j;
                        nb++;
                    }
                }
            }
        }
    }

    for (int j=-2; j<=2; j+=4) {
        for (int i=-1; i<=1; i+=2) {
            if (x+i >= 0 && x+i < N && y+j >= 0 && y+j < N) {
                if (PLATEAU[(x+i)*N + y+j]) {
                    if (PLATEAU[(x+i)*N + y+j] == -Roi) {
                        priseRoi = 1;
                    } else {
                        tabPossibiliter[2*nb] = x+i;
                        tabPossibiliter[2*nb+1] = y+j;
                        nb++;
                    }
                }
            }
        }
    }
    
    tabPossibiliter[2*nb] = -1;
    tabPossibiliter[2*nb+1] = -1;

    return priseRoi;
}

int PossibiliterFOU(int * tabPossibiliter, int x, int y) {
    int nb = 0;
    int priseRoi = 0;
    int N = plateau.N;
    int * PLATEAU = plateau.tab;

    // Haut
    // Si signe=-1 alors, Haut Gauche
    // Si signe=1 alors, Haut Droite
    for (int signe=-1; signe<=1; signe+=2) {
        int i = x;
        int j = y;
        do {
            x--;
            y += signe;
            if (i>=0 && j>=0 && j<N && PLATEAU[i*N + j] <= 0) {
                if (PLATEAU[i*N + j] == -Roi) {
                    priseRoi = 1;
                } else {
                    tabPossibiliter[2*nb] = i;
                    tabPossibiliter[2*nb+1] = j;
                    nb++;
                }
            }
        } while (i>=0 && j>=0 && j<N && PLATEAU[i*N + j] == 0);
    }

    // Bas
    // Si signe=-1 alors, Bas Gauche
    // Si signe=1 alors, Bas Droite
    for (int signe=-1; signe<=1; signe+=2) {
        int i = x;
        int j = y;
        do {
            i++;
            j += signe;
            if (i<N && j>=0 && j<N && PLATEAU[i*N + j] <= 0) {
                if (PLATEAU[i*N + y] == -Roi) {
                    priseRoi = 1;
                } else {
                    tabPossibiliter[2*nb] = i;
                    tabPossibiliter[2*nb+1] = j;
                    nb++;
                }
            }
        } while (i<N && j>=0 && j<N && PLATEAU[i*N + j] == 0);
    }
    
    tabPossibiliter[2*nb] = -1;
    tabPossibiliter[2*nb+1] = -1;

    return priseRoi;
}

int PossibiliterROI(int * tabPossibiliter, int x, int y) {
    int nb = 0;
    int priseRoi = 0;
    int N = plateau.N;
    int * PLATEAU = plateau.tab;

    for (int i=x-1; i<=x+1; i++) {
        for (int j=y-1; j<=y+1; j++){
            if (i>=0 && i<N && j>=0 && j<N) {
                if (PLATEAU[i*N + j] <=  0) {
                    if (PLATEAU[i*N + j] == -Roi) {
                        priseRoi = 1;
                    } else {
                        tabPossibiliter[2*nb] = i;
                        tabPossibiliter[2*nb+1] = j;
                        nb++;
                    }
                }
            }
        }
    }

    return priseRoi;
}

int PossibiliterDAME(int * tabPossibiliter, int x, int y) {
    int nb = 0;
    int priseRoi = 0;
    int N = plateau.N;
    int * PLATEAU = plateau.tab;

    // Haut et Bas
    // Si signe=-1 alors, on parcour vers le Haut
    // Si signe=1 alors, on parcour cers le Bas
    for (int signe=-1; signe<=1; signe+=2) {
        int i = x;
        do {
            i+=signe;
            // Si la piece n'est pas une piece allier
            if (i>=0 && i<N && PLATEAU[N*i+y] <= 0) {
                if (PLATEAU[N*i+y] == -Roi) {
                    priseRoi = 1;
                } else {
                    tabPossibiliter[2*nb] = i;
                    tabPossibiliter[2*nb+1] = y;
                    nb++;
                }
            }
        } while (i>=0 && i<N && PLATEAU[N*i+y] == 0);
    }

    // Gauche et Droite
    // Si signe=-1 alors, on parcour vers la Gauche
    // Si signe=1 alors, on parcour vers la Droite
    for (int signe=-1; signe<+1; signe+=2) {
        int j = y;
        do {
            j+=signe;
            // Si la piece n'est pas une piece allier
            if (j>=0 && j<N && PLATEAU[N*x+j]) {
                if (PLATEAU[N*x+j] == -Roi) {
                    priseRoi = 1;
                } else {
                    tabPossibiliter[2*nb] = x;
                    tabPossibiliter[2*nb+1] = j;
                    nb++;
                }
            }
        } while (j>=0 && j<N && PLATEAU[N*x+j]);
    }

    // Haut
    // Si signe=-1 alors, Haut Gauche
    // Si signe=1 alors, Haut Droite
    for (int signe=-1; signe<=1; signe+=2) {
        int i = x;
        int j = y;
        do {
            x--;
            y += signe;
            if (i>=0 && j>=0 && j<N && PLATEAU[i*N + j] <= 0) {
                if (PLATEAU[i*N + j] == -Roi) {
                    priseRoi = 1;
                } else {
                    tabPossibiliter[2*nb] = i;
                    tabPossibiliter[2*nb+1] = j;
                    nb++;
                }
            }
        } while (i>=0 && j>=0 && j<N && PLATEAU[i*N + j] == 0);
    }

    // Bas
    // Si signe=-1 alors, Bas Gauche
    // Si signe=1 alors, Bas Droite
    for (int signe=-1; signe<=1; signe+=2) {
        int i = x;
        int j = y;
        do {
            i++;
            j += signe;
            if (i<N && j>=0 && j<N && PLATEAU[i*N + j] <= 0) {
                if (PLATEAU[i*N + y] == -Roi) {
                    priseRoi = 1;
                } else {
                    tabPossibiliter[2*nb] = i;
                    tabPossibiliter[2*nb+1] = j;
                    nb++;
                }
            }
        } while (i<N && j>=0 && j<N && PLATEAU[i*N + j] == 0);
    }
    
    tabPossibiliter[2*nb] = -1;
    tabPossibiliter[2*nb+1] = -1;

    return priseRoi;
}

int JouerCoup(int xAvant, int yAvant, int xApres, int yApres) {
    int piecePrise = 0;
    int N = plateau.N;
    int * PLATEAU = plateau.tab;

    if (PLATEAU[xApres*N + yApres] != 0)
        piecePrise = 1;
    
    PLATEAU[xApres*N + yApres] = PLATEAU[xAvant*N + yAvant];
    PLATEAU[xAvant*N + yAvant] = 0;

    return piecePrise;
}

void JouerPetitRoque(int x) {
}

void JouerGrandRoque(int x) {
}

void LectureFichierPGN(char * nomFichier) {
    FILE * file = fopen(nomFichier, "r");
    char * coup;
    
    if (file != NULL) {
        int xAvant;
        int yAvant;
        int xApres;
        int yApres;
    } else {
        printf("Fichier %s ne peut pas etre ouvert\n", nomFichier);
    }
}