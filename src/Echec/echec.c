
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"echec.h"

Plateau_t plateau;
Joueur_t joueur1;
Joueur_t joueur2;   /* Ordinateur */


void InitialiserPlateau() {
    int N = 8;
    plateau.N = N;
    int * tab = (int*)malloc(N*N*sizeof(int));
    plateau.tab = tab;
    plateau.joueur1 = &joueur1;
    plateau.joueur2 = &joueur2;
    plateau.JoueurTrait = &joueur1;
    RemiseAZero();
    InitialiserCoupPrecedent();
}

void InitialiserJoueur() {

    // Joueur1
    joueur1.nom = "Joueur1";
    joueur1.EstEnEchec = 0;
    joueur1.EstEnEchecMat = 0;
    joueur1.peutPetitRoque = 1;
    joueur1.peutGrandRoque = 1;
    joueur1.couleur = 'N';
    joueur1.signe = -1;
    joueur1.adversaire = &joueur2;

    // Joueur2
    joueur2.nom = "Joueur2";
    joueur2.EstEnEchec = 0;
    joueur2.EstEnEchecMat = 0;
    joueur2.peutPetitRoque = 1;
    joueur2.peutGrandRoque = 1;
    joueur2.couleur = 'B';
    joueur2.signe = 1;
    joueur2.adversaire = &joueur1;
}

void InitialiserCoupPrecedent() {
    plateau.coupPrecedent.xApres = -1;
    plateau.coupPrecedent.xAvant = -1;
    plateau.coupPrecedent.yApres = -1;
    plateau.coupPrecedent.yAvant = -1;
}

void InitialiserDebutPartie() {
    int N = plateau.N;
    int * PLATEAU = plateau.tab;
    /* Si signe = 1,  le joueur 2 est en haut car il joue blanc */
    /* Si signe = -1, le joueur 2 est en bas  car il joue noir  */
    int signe = 1;
    if (joueur2.couleur == 'N')
        signe = -1;

    // Placement des pions
        // Ordinateur
            for (int i=0; i<N; i++)
                PLATEAU[N+i] = signe*Pion;
        // Joueur
            for (int i=0; i<N; i++)
                PLATEAU[6*N+i] = -signe*Pion;

    // Placement des tours
        // Ordinateur
            PLATEAU[0] = signe*Tour;
            PLATEAU[7] = signe*Tour;
        // Joueur
            PLATEAU[N*7] = -signe*Tour;
            PLATEAU[N*7+7] = -signe*Tour;
    
    // Placement des cavaliers
        // Ordinateur
            PLATEAU[1] = signe*Cavalier;
            PLATEAU[6] = signe*Cavalier;
        // Joueur
            PLATEAU[N*7+1] = -signe*Cavalier;
            PLATEAU[N*7+6] = -signe*Cavalier;
    
    // Placement des fous
        // Ordinateur
            PLATEAU[2] = signe*Fou;
            PLATEAU[5] = signe*Fou;
        // Joueur
            PLATEAU[N*7+2] = -signe*Fou;
            PLATEAU[N*7+5] = -signe*Fou;

    // Placement des dames
        // Ordinateur
            PLATEAU[4] = signe*Dame;
        // Joueur
            PLATEAU[N*7+4] = -signe*Dame;
    
    // Placement des roi
        // Ordinateur
            PLATEAU[3] = signe*Roi;
        // Joueur
            PLATEAU[N*7+3] = -signe*Roi;
}

void RemiseAZero() {
    int N = plateau.N;
    for (int i=0; i<N*N; i++)
        plateau.tab[i] = 0;
}

void Initialiser() {
    InitialiserPlateau();
    InitialiserJoueur();
    InitialiserDebutPartie();
}

char AfficherPiece(int x, int y) {
    int valPiece = abs(plateau.tab[x*plateau.N + y]);
    switch (valPiece)
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
	/* RAPPEL : En memoire, le joueur blanc est toujours en haut */
	/* 			MAIS a l'affichage, c'est le joueur2 qui est en Haut */
    system("clear");
    printf("-------------------------\n");
	
	// Joueur2 en blanc
	if (joueur2.couleur == 'B') {
		for (int i=0; i<8; i++) {
			printf("|");
			for (int j=0; j<8; j++)
				printf("%c |", AfficherPiece(i,j));
			printf("\n-------------------------\n");
		}
	} else {
		for (int i=7; i>=0; i--) {
			printf("|");
			for (int j=7; j>=0; j--)
				printf("%c |", AfficherPiece(i,j));
			printf("\n-------------------------\n");
		}
	}
	
	if ((*(*plateau.joueur1).adversaire).EstEnEchec == 1)
		printf("%s est en Echec\n", (*(*plateau.JoueurTrait).adversaire).nom);

	if ((*(*plateau.joueur1).adversaire).EstEnEchec == 1)
		printf("%s est en Echec et Mat\n", (*(*plateau.JoueurTrait).adversaire).nom);
    
    printf("\n");
}

int PossibiliterPION(int * tabPossibiliter, int x, int y) {
    int nb = 0;
    int priseRoi = 0;
    int N = plateau.N;
    int * PLATEAU = plateau.tab;
    int signe = (*plateau.JoueurTrait).signe;


    // Deplacement vers le bas
    if ((*plateau.JoueurTrait).couleur == 'B' ) {
        // Deplacement normal
        if (x+1 < N && PLATEAU[N*(x+1) + y] == 0) {
            tabPossibiliter[2*nb] = x+1;
            tabPossibiliter[2*nb+1] = y;
            nb ++;
        }

        // Deplacement premier coup
        if (x == 1 && PLATEAU[N*(x+2) + y] == 0) {
            tabPossibiliter[2*nb] = x+2;
            tabPossibiliter[2*nb+1] = y;
            nb ++;
        }

        // Prise normal
        if (x+1 < N) {
            if (y-1 >= 0 && signe*PLATEAU[(x+1)*N + y-1] <= 0) {
                if (PLATEAU[(x+1)*N + y-1] == -signe*Roi) {
                    priseRoi = 1;
                } else {
                    tabPossibiliter[2*nb] = x+1;
                    tabPossibiliter[2*nb+1] = y-1;
                    nb ++;
                }
            }
            if (y+1 < N && signe*PLATEAU[(x+1)*N + y+1] <+ 0) {
                if (PLATEAU[(x+1)*N + y+1] == -signe*Roi) {
                    priseRoi = 1;
                } else {
                    tabPossibiliter[2*nb] = x+1;
                    tabPossibiliter[2*nb+1] = y+1;
                    nb ++;
                }
            }
        }
    } else {
        // Deplacement normal
        if (x-1 >= 0 && PLATEAU[N*(x-1) + y] == 0) {
            tabPossibiliter[2*nb] = x-1;
            tabPossibiliter[2*nb+1] = y;
            nb ++;
        }

        // Deplacement premier coup
        if (x == 6 && PLATEAU[N*(x-2) + y] == 0) {
            tabPossibiliter[2*nb] = x-2;
            tabPossibiliter[2*nb+1] = y;
            nb ++;
        }

        // Prise normal
        if (x-1 >= 0) {
            if (y-1 >= 0 && signe*PLATEAU[(x-1)*N + y-1] <= 0) {
                if (PLATEAU[(x-1)*N + y-1] == -signe*Roi) {
                    priseRoi = 1;
                } else {
                    tabPossibiliter[2*nb] = x-1;
                    tabPossibiliter[2*nb+1] = y-1;
                    nb ++;
                }
            }
            if (y+1 < N && signe*PLATEAU[(x-1)*N + y+1] <= 0) {
                if (PLATEAU[(x-1)*N + y+1] == -signe*Roi) {
                    priseRoi = 1;
                } else {
                    tabPossibiliter[2*nb] = x-1;
                    tabPossibiliter[2*nb+1] = y+1;
                    nb ++;
                }
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
    int signe = (*plateau.JoueurTrait).signe;

    // Haut et Bas
    // Si enBas=-1 alors, on parcour vers le Haut
    // Si enBas=1 alors, on parcour cers le Bas
    for (int enBas=-1; enBas<=1; enBas+=2) {
        int i = x;
        do {
            i+=enBas;
            // Si la piece n'est pas une piece allier
            if (i>=0 && i<N && signe*PLATEAU[N*i+y] <= 0) {
                if (PLATEAU[N*i+y] == -signe*Roi) {
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
    // Si aDroite=-1 alors, on parcour vers la Gauche
    // Si aDroite=1 alors, on parcour vers la Droite
    for (int aDroite=-1; aDroite<+1; aDroite+=2) {
        int j = y;
        do {
            j+=aDroite;
            // Si la piece n'est pas une piece allier
            if (j>=0 && j<N && signe*PLATEAU[N*x+j] <= 0) {
                if (PLATEAU[N*x+j] == -signe*Roi) {
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
    int signe = (*plateau.JoueurTrait).signe;

    for (int i=-2; i<=2; i+=4) {
        for (int j=-1; j<=1; j+=2) {
            if (x+i >= 0 && x+i < N && y+j >= 0 && y+j < N) {
                if (signe*PLATEAU[(x+i)*N + y+j] <= 0) {
                    if (PLATEAU[(x+i)*N + y+j] == -signe*Roi) {
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
                if (signe*PLATEAU[(x+i)*N + y+j] <= 0) {
                    if (PLATEAU[(x+i)*N + y+j] == -signe*Roi) {
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
    int signe = (*plateau.JoueurTrait).signe;

    // Haut
    // Si enHDroite=-1 alors, Haut Gauche
    // Si enHDroite=1 alors, Haut Droite
    for (int enHDroite=-1; enHDroite<=1; enHDroite+=2) {
        int i = x;
        int j = y;
        do {
            x--;
            y += enHDroite;
            if (i>=0 && j>=0 && j<N && signe*PLATEAU[i*N + j] <= 0) {
                if (PLATEAU[i*N + j] == -signe*Roi) {
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
    // Si enBDroite=-1 alors, Bas Gauche
    // Si enBDroite=1 alors, Bas Droite
    for (int enBDroite=-1; enBDroite<=1; enBDroite+=2) {
        int i = x;
        int j = y;
        do {
            i++;
            j += enBDroite;
            if (i<N && j>=0 && j<N && signe*PLATEAU[i*N + j] <= 0) {
                if (PLATEAU[i*N + y] == -signe*Roi) {
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
    int signe = (*plateau.JoueurTrait).signe;

    for (int i=x-1; i<=x+1; i++) {
        for (int j=y-1; j<=y+1; j++){
            if (i>=0 && i<N && j>=0 && j<N) {
                if (signe*PLATEAU[i*N + j] <=  0) {
                    if (signe*PLATEAU[i*N + j] == -Roi) {
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

    priseRoi = PossibiliterTOUR(tabPossibiliter, x, y);

    int * cour = tabPossibiliter;
    while (*cour != -1)
        cour++;
    
    priseRoi = priseRoi || PossibiliterFOU(cour, x, y);
    
    tabPossibiliter[2*nb] = -1;
    tabPossibiliter[2*nb+1] = -1;

    return priseRoi;
}

void PromotionPION(int x, int y, int valPiece) {
    plateau.tab[x*plateau.N + y] = valPiece;
}

void DeduirPOIN(int * xAvant, int * yAvant, int xApres, int yApres, int prisePiece) {
	int * PLATEAU = plateau.tab;
	int N = plateau.N;
	/* Permet de changer le signe de la valeur des pieces en fonction du joueur qui a le trait */
    int signe = (*plateau.JoueurTrait).signe;
	/* Permet de changer la direction des pions en fonction de qui a le trait et de ca couleur */
	int monter = (*plateau.JoueurTrait).couleur=='B'?-1:1;
    int valeurPiece = signe*Pion;

	// Prise en passant
	if (prisePiece == 1 && PLATEAU[xApres*N + yApres] == 0) {
		// 2 possibilites
		if (*xAvant == -1) {
			*xAvant = xApres+monter;
			if (*yAvant == -1) {
				if (yApres-1 >= 0 && PLATEAU[*xAvant*N + yApres-1] == valeurPiece)
					*yAvant = yApres-1;
				else
					*yAvant = yApres+1;
			}
		}
		return;
	}

	// Pas de prise en avant
	if (*xAvant == -1 && *yAvant != -1) {
		if (prisePiece == 1) {
			*xAvant = xApres+monter;
		} else {
			if (PLATEAU[(xApres+monter)*N + *yAvant] == valeurPiece)
				*xAvant = xApres + monter;
			else
				*xAvant = xApres + 2*monter;
		}
	} else {
		// *xAvant == -1 && *yAvant == -1 et *xAvant != -1 && *yAvant == -1
		// Quasiment meme test
		if (prisePiece == 1) {
			*xAvant = xApres + monter;
			if (yApres-1 >= 0 && PLATEAU[(*xAvant)*N + yApres-1] == valeurPiece)
				*yAvant = yApres - 1;
			else
				*yAvant = yApres + 1;
		} else {
			*yAvant = yApres;
			if (PLATEAU[(xApres+monter)*N + *yAvant] == valeurPiece)
				*xAvant = xApres + monter;
			else
				*xAvant = xApres + 2*monter;
		}
	}



}

void DeduirTOUR(int * xAvant, int * yAvant, int xApres, int yApres, int estDame) {
    int * PLATEAU = plateau.tab;
    int N = plateau.N;
    int signe = (*plateau.JoueurTrait).signe;
    int valeurPiece = signe*(estDame==1?Dame:Tour);

    if ( *xAvant != -1 && *xAvant != xApres) {
        *yAvant = yApres;
        return;
    }
    if (*yAvant != -1 && *yAvant != yApres) {
        *xAvant = xApres;
        return;
    }



    if (*xAvant == -1) {
        int i = 1;
        while (xApres-i >= 0 && PLATEAU[(xApres-i)*N + yApres] != valeurPiece)
            i++;
        if (xApres-i >= 0) {
            *xAvant = xApres - i;
            *yAvant = yApres;
            return;
        }

        i = 1;
        while (xApres+i < N && PLATEAU[(xApres+i)*N + yApres] != valeurPiece)
            i++;
        if ( xApres+i < N) {
            *xAvant = xApres + i;
            *yAvant = yApres;
            return;
        }
    }

    if (*yAvant == -1) {
        int j = 1;
        while (yApres-j >= 0 && PLATEAU[xApres*N + yApres-j] != valeurPiece)
            j++;
        if (yApres-j >= 0) {
            *xAvant = xApres;
            *yAvant = yApres - j;
            return;
        }

        j = 1;
        while (yApres+j < N && PLATEAU[xApres*N + yApres+j] != valeurPiece)
            j++;
        if (yApres+j < N) {
            *xAvant = xApres;
            *yAvant = yApres + j;
            return;
        }
    }


}

void DeduirCAVALIER(int * xAvant, int * yAvant, int xApres, int yApres) {
    int * PLATEAU = plateau.tab;
    int N = plateau.N;
    int signe = (*plateau.JoueurTrait).signe;
    int valeurPiece = signe*Cavalier;

    if (*xAvant != -1) {
        int yEcart = abs(*xAvant-xApres)==1?2:1;
        if (yApres-yEcart >= 0 && PLATEAU[*xAvant*N + yApres-yEcart] == valeurPiece)
            *yAvant = yApres-yEcart;
        else
            *yAvant = yApres+yEcart;
    }

    if (*yAvant != -1) {
        int xEcart = abs(*yAvant-yApres)==1?2:1;
        if (xApres-xEcart >= 0 && PLATEAU[(xApres-xEcart)*N + *yAvant] == valeurPiece)
            *xAvant = xApres-xEcart;
        else
            *xAvant = xApres+xEcart;
    }

    if (*xAvant == -1 && *yAvant == -1) {
        for (int i=-2; i<=2; i+=4) {
            for (int j=-1; j<=1; j+=2) {
                if (xApres+i >= 0 && xApres+i < N && yApres+j >= 0 && yApres+j < N) {
                    if (PLATEAU[(xApres+i)*N + yApres+j] == valeurPiece) {
                        *xAvant = xApres + i;
                        *yAvant = yApres + j;
                        return;
                    }
                }
            }
        }

        for (int j=-2; j<=2; j+=4) {
            for (int i=-1; i<=1; i+=2) {
                if (xApres+i >= 0 && xApres+i < N && yApres+j >= 0 && yApres+j < N) {
                    if (PLATEAU[(xApres+i)*N + yApres+j] == valeurPiece) {
                        *xAvant = xApres + i;
                        *yAvant = yApres + j;
                        return;
                    }
                }
            }
        }
    }

}

void DeduirFOU(int * xAvant, int * yAvant, int xApres, int yApres, int estDame) {
    int * PLATEAU = plateau.tab;
    int N = plateau.N;
    int signe = (*plateau.JoueurTrait).signe;
    int valeurPiece = signe*(estDame==1?Dame:Fou);

    if (*xAvant != -1) {
        // 2 possibilites
        if (yApres-1 >= 0 && PLATEAU[*xAvant*N + yApres-1] == valeurPiece)
            *yAvant = yApres-1;
        else
            *yAvant = yApres+1;
        return;
    }

    if (*yAvant != -1) {
        // 2 possibilites
        if (xApres-1 >= 0 && PLATEAU[(xApres-1)*N + *yAvant] == valeurPiece)
            *xAvant = xApres-1;
        else
            *xAvant = xApres+1;
        return;
    }

    // Il ne reste plus que le cas ou ni la ligne ni la colonne sont indique

    // Haut Gauche
    int i = 1;
    while (xApres-i >= 0 && yApres-i >= 0 && PLATEAU[(xApres-i)*N + yApres-i] != valeurPiece)
        i++;
    if (xApres-i >= 0 && yApres-i >= 0) {
        *xAvant = xApres-i;
        *yAvant = yApres-i;
        return;
    }

    // Haut Droite
    i = 1;
    while (xApres-i >= 0 && yApres+i < N && PLATEAU[(xApres-i)*N + yApres+i] != valeurPiece)
        i++;
    if (xApres-i >= 0 && yApres+i != N) {
        *xAvant = xApres-i;
        *yAvant = yApres+i;
        return;
    }

    // Bas Gauche
    i = 1;
    while (xApres+i < N && yApres-i >= 0 && PLATEAU[(xApres+i)*N + yApres-i] != valeurPiece)
        i++;
    if (xApres+i != N && yApres-i >= 0) {
        *xAvant = xApres+i;
        *yAvant = yApres-i;
        return;
    }

    // Bas Droite
    i = 1;
    while (xApres+i < N && yApres+i < N && PLATEAU[(xApres+i)*N + yApres+i] != valeurPiece)
        i++;
    if (xApres != N && yApres != N) {
        *xAvant = xApres+i;
        *yAvant = yApres+i;
        return;
    }


}

void DeduirDAME(int * xAvant, int * yAvant, int xApres, int yApres) {
    DeduirTOUR(xAvant, yAvant, xApres, yApres, 1);
    if (*xAvant == -1 || *yAvant == -1)
        DeduirFOU(xAvant, yAvant, xApres, yApres, 1);
}

void DeduirROI(int * xAvant, int * yAvant, int xApres, int yApres) {
    int * PLATEAU = plateau.tab;
    int N = plateau.N;
    int signe = (*plateau.JoueurTrait).signe;
    int valeurPiece = signe*Roi;

    if (*xAvant != -1) {
        if (yApres-1 >= 0 && PLATEAU[*xAvant*N + yApres-1] == valeurPiece)
            *yAvant = yApres - 1;
        else if (PLATEAU[*xAvant*N + yApres] == valeurPiece)
            *yAvant = yApres;
        else
            *yAvant = yApres + 1;
    }

    if (*yAvant != -1) {
        if (xApres-1 >= 0 && PLATEAU[(xApres-1)*N + *yAvant] != valeurPiece)
            *xAvant = xApres - 1;
        else if (PLATEAU[xApres*N + *yAvant] != valeurPiece)
            *xAvant = xApres;
        else
            *xAvant = xApres + 1;
    }

    if (*xAvant == -1 && *yAvant == -1) {
        for (int i=-1; i<=1; i+=1)
            for (int j=-1; j<=1; j+=1)
                if (xApres+i >= 0 && xApres+i < N && yApres+j >= 0 && yApres+j < N)
                    if (PLATEAU[(xApres+i)*N + yApres+j] == valeurPiece) {
                        *xAvant = xApres+i;
                        *yAvant = yApres+j;
                        return;
                    }
    }

}

void DeduirCoup(int * xAvant, int * yAvant, int xApres, int yApres, int piece, int prisePiece) {
    switch (abs(piece))
    {
    case Tour:
        DeduirTOUR(xAvant, yAvant, xApres, yApres, 0);
        break;
    case Cavalier:
        DeduirCAVALIER(xAvant, yAvant, xApres, yApres);
        break;
    case Fou:
        DeduirFOU(xAvant, yAvant, xApres, yApres, 0);
        break;
    case Dame:
        DeduirDAME(xAvant, yAvant, xApres, yApres);
        break;
    case Roi:
        DeduirROI(xAvant, yAvant, xApres, yApres);
        break;
    
    default:
    DeduirPOIN(xAvant, yAvant, xApres, yApres, prisePiece);
        break;
    }
}

int DeplacerPiece(int xAvant, int yAvant, int xApres, int yApres) {
    int piecePrise = 0;
    int N = plateau.N;
    int * PLATEAU = plateau.tab;
    

    // memorisation du coup
    plateau.coupPrecedent.xAvant = xAvant;
    plateau.coupPrecedent.yAvant = yAvant;
    plateau.coupPrecedent.xApres = xApres;
    plateau.coupPrecedent.yApres = yApres;
    plateau.coupPrecedent.valeurPieceJouer = PLATEAU[xAvant*N + yAvant];

    // Si une piece a ete prise, alors je renvoie 1
    if (PLATEAU[xApres*N + yApres] != 0)
        piecePrise = 1;
    
    PLATEAU[xApres*N + yApres] = PLATEAU[xAvant*N + yAvant];
    PLATEAU[xAvant*N + yAvant] = 0;

    return piecePrise;
}

int JouerCoup(int xAvant, int yAvant, int xApres, int yApres) {
    int piecePrise;

    // Deplacement de la piece
    piecePrise = DeplacerPiece(xAvant, yAvant, xApres, yApres);

    // Mise a jour du roque
    MAJRoque(xAvant,yAvant);

    return piecePrise;
}

void MAJRoque(int x, int y) {

    int valAbsoluPiece = abs(plateau.tab[x*plateau.N + y]);

    // Si une tour ou un roi a ete jouer, alors certain roque ne sont plus possible
    if (valAbsoluPiece != Roi && valAbsoluPiece != Tour)
        return;
    
    if (valAbsoluPiece == Roi) {
        (*plateau.JoueurTrait).peutPetitRoque = 0;
        (*plateau.JoueurTrait).peutGrandRoque = 0;
    } else {
        if (y == 0)
            (*plateau.JoueurTrait).peutPetitRoque = 0;
        else
            (*plateau.JoueurTrait).peutGrandRoque = 0;
    }

}

void JouerPetitRoque(int x) {
    int N = plateau.N;
    int * PLATEAU = plateau.tab;

    // Blanc toujours en Haut
    PLATEAU[x*N + 1] = PLATEAU[x*N + 3];
    PLATEAU[x*N + 3] = 0;
    PLATEAU[x*N + 2] = PLATEAU[x*N + 0];
    PLATEAU[x*N + 0] = 0;
}

void JouerGrandRoque(int x) {
    int N = plateau.N;
    int * PLATEAU = plateau.tab;

    // Blanc toujours en Haut
    PLATEAU[x*N + 5] = PLATEAU[x*N + 3];
    PLATEAU[x*N + 3] = 0;
    PLATEAU[x*N + 4] = PLATEAU[x*N + 7];
    PLATEAU[x*N + 7] = 0;
}

void LireCoup(char * coup) {
    char * cour = coup;
    int signe = (*plateau.JoueurTrait).signe;
    int valPiece;
    int xAvant = -1;
    int yAvant = -1;
    int xApres = -1;
    int yApres = -1;
    int prisePiece = 0;

	// MAJ du joueur qui a le trait
	(*plateau.JoueurTrait).EstEnEchec = 0;

    // On commence par regarder si c'est un roque
    if (*coup == 'O') {
        int x;  // ligne ou le roque est a faire
        if ((*plateau.JoueurTrait).couleur == 'B')
            x = 0;
        else
            x = 7;

        if (strcmp(coup, "O-O") <= 50)
            JouerPetitRoque(x); // Petit roque
        else
            JouerPetitRoque(x); // Grand roque
    } else {
        // Recuperation de la piece qui a ete jouer
        // decalage du pointeur courant si ce n'est pas un pion
        valPiece = signe*ConvertirCharPiece(*coup);
        if (valPiece != signe*Pion)
            cour = coup + 1;

        // Recuperation de la position apres avoir jouer le coup
        // Si indiquer, recuperation de la position initiale
        while (*cour != '\0' && *cour != '=' && *cour != '+' && *cour != '#'  ) {
            if (*cour < 57) {
                if (xApres != -1)
                    xAvant = xApres;
                xApres = ConvertLigneInt(*cour);
            } else if (*cour < 105) {
                if (yApres != -1)
                    yAvant = yApres;
                yApres = ConvertirColonneInt(*cour);
            } else {
                prisePiece = 1;
            }
            cour++;
        }

        // Deduction de la position initial de la piece
        if (xAvant == -1 || yAvant == -1)
            DeduirCoup(&xAvant, &yAvant, xApres, yApres, valPiece, prisePiece);

        // Deplacer la piece
        DeplacerPiece(xAvant, yAvant, xApres, yApres);

        // Si promotion, realisation de la promotion
        if (*cour == '=') {
            cour++;
            PromotionPION(xApres, yApres, signe*ConvertirCharPiece(*cour));
            cour++;
        }
    }

    if (*cour == '+')
		(*(*plateau.JoueurTrait).adversaire).EstEnEchec = 1;

    if (*cour == '#')
        (*(*plateau.JoueurTrait).adversaire).EstEnEchecMat = 1;
}

int ConvertirCharPiece(char carac) {
    switch (carac)
    {
    case 'K':
        return Roi;
        break;
    case 'Q':
        return Dame;
        break;
    case 'B':
        return Fou;
        break;
    case 'N':
        return Cavalier;
        break;
    case 'R':
        return Tour;
        break;
    
    default:
    return Pion;
        break;
    }
}

int ConvertirColonneInt(char carac) {
    return 104 - carac;
}

int ConvertLigneInt(char carac) {
    return carac - 49;
}

int EstCeFinPartie(char * coup) {
    
    // 3 cas : 0-1 ou 1-0 ou 1/2-1/2
    if ( *coup == '0' || *coup == '1') {
        coup++;
        if (*coup == '-' || *coup == '/') {
            coup++;
            if (*coup == '0' || *coup == '1' || *coup == '2')
                return 1;
        }
    }

    return 0;
}

void LectureFichierPGN(char * nomFichier) {
    FILE * file = fopen(nomFichier, "r");
    char coup [10];
    
    if (file != NULL) {
        int  finPartie = 0;
        Initialiser();
        AfficherPlateau();
        
        // Le joueur blanc est l'ordinateur
        plateau.JoueurTrait = &joueur1;


        // On enleve le "1." qui commence la partie
        fscanf(file, "%s", coup);

        do {
            // Je change le joueur qui a le trait
            plateau.JoueurTrait = (*plateau.JoueurTrait).adversaire;

            // Je recupere le coup si il n'a pas encore ete recupere pour le test de fin de partie
            if ((*plateau.JoueurTrait).couleur == 'B')
                fscanf(file, "%s", coup);

			LireCoup(coup);

			AfficherPlateau();

            printf("tap n to continue\n\n");
            scanf("%s", coup);

			// Je recupere le prochaine coup et je regarde si c'est la fin
			fscanf(file, "%s", coup);
            finPartie = EstCeFinPartie(coup);
        } while (finPartie == 0);

    } else {
        printf("Fichier %s ne peut pas etre ouvert\n", nomFichier);
    }
    system("clear");
}