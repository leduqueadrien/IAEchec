
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "echec.h"
#include "AffichageEchec.h"




void InitialiserPlateau(char couleurJouerHaut) {
	int N = 8;
	plateau.N = N;
	int * tab = (int*)malloc(N*N*sizeof(int));
	plateau.tab = tab;
	plateau.couleurJoueurHaut = couleurJouerHaut;
	plateau.joueur1 = &joueur1;
	plateau.joueur2 = &joueur2;
	plateau.JoueurTrait = &joueur1;
	RemiseAZero();
	InitialiserCoupPrecedent();
}

void InitialiserJoueur(char couleurJoueur1) {

	// Joueur1
	joueur1.nom = "Joueur1";
	joueur1.EstEnEchec = 0;
	joueur1.EstEnEchecMat = 0;
	joueur1.peutPetitRoque = 1;
	joueur1.peutGrandRoque = 1;
	joueur1.couleur = couleurJoueur1;
	joueur1.signe = -1;
	joueur1.adversaire = &joueur2;

	// Joueur2
	joueur2.nom = "Joueur2";
	joueur2.EstEnEchec = 0;
	joueur2.EstEnEchecMat = 0;
	joueur2.peutPetitRoque = 1;
	joueur2.peutGrandRoque = 1;
	joueur2.couleur = couleurJoueur1=='B'?'N':'B';
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

void Initialiser(char couleurJoueur1, char couleurJoueurHaut) {
	InitialiserPlateau(couleurJoueurHaut);
	InitialiserJoueur(couleurJoueur1);
	InitialiserDebutPartie();
}

int PossibiliterPION(int * tabPossibiliter, int x, int y) {
	int nb = 0; /* compteur du nombre de possibilite trouve */
	int priseRoi = 0;   /* Est ce que le pion peut prendre le roi (valeur de retour) */
	int N = plateau.N;
	int * PLATEAU = plateau.tab;
	CoupPrecedent_t cp = plateau.coupPrecedent;
	char coleurJTrait = (*plateau.JoueurTrait).couleur;
	int signe = (*plateau.JoueurTrait).signe;   /* signe de la piece */
	int dir = (*plateau.JoueurTrait).couleur == 'B'?1:-1;   /* Direction du deplacement */
															/* dir=1 : deplacement vers le bas */
															/* dir=-1 : deplacement vers le haut */

	// Deplacement normal (deplacement d'une case)
	if (x+1 < N && PLATEAU[N*(x+dir*1) + y] == 0) {
		tabPossibiliter[2*nb] = x+dir*1;
		tabPossibiliter[2*nb+1] = y;
		nb ++;
	}


	// Deplacement premier coup (deplacement de deux cases)
	if ((x == 1 && dir == 1) || (x == 6 && dir == -1)) {
		if (x == 1 && PLATEAU[N*(x+dir*2) + y] == 0) {
			tabPossibiliter[2*nb] = x+dir*2;
			tabPossibiliter[2*nb+1] = y;
			nb ++;
		}
	}

	// Prise normal (deplacement diagonal)
	if (x+dir*1 < N) {
		// Diagonal Gauche
		if (y-1 >= 0 && signe*PLATEAU[(x+dir*1)*N + y-1] <= 0) {
			if (PLATEAU[(x+dir*1)*N + y-1] == -signe*Roi) {
				priseRoi = 1;
			} else {
				tabPossibiliter[2*nb] = x+dir*1;
				tabPossibiliter[2*nb+1] = y-1;
				nb ++;
			}
		}
		// Diagonal Droite
		if (y+1 < N && signe*PLATEAU[(x+dir*1)*N + y+1] <= 0) {
			if (PLATEAU[(x+dir*1)*N + y+1] == -signe*Roi) {
				priseRoi = 1;
			} else {
				tabPossibiliter[2*nb] = x+dir*1;
				tabPossibiliter[2*nb+1] = y+1;
				nb ++;
			}
		}
	}

	// Prise en passant
	// Il faut que l'adversaire ait joue un pion de 2 cases depuis sa case initial
	if (cp.valeurPieceJouer == -signe*Pion) {
		if ((coleurJTrait == 'N' && cp.xAvant == 1 && cp.xApres == 3) 
		 || (coleurJTrait == 'B' && cp.xAvant == 6 && cp.xApres == 4)) {
			// Il faut en plus que le pion se situe en bon endroit pour prendre la piece
			if (x == cp.xApres && y+1 == cp.yApres) {
				tabPossibiliter[2*nb] = x+dir*1;
				tabPossibiliter[2*nb+1] = y+1;
				nb++;
			}
			if (x == cp.xApres && y-1 == cp.yApres) {
				tabPossibiliter[2*nb] = x+dir*1;
				tabPossibiliter[2*nb+1] = y-1;
				nb++;
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
