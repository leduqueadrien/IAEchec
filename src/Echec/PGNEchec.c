
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "PGNEchec.h"
#include "AffichageEchec.h"


void DeduirPOIN(int * xAvant, int * yAvant, int xApres, int yApres, int prisePiece) {
	int * PLATEAU = plateau.tab;
	int N = plateau.N;
	/* Permet de changer le signe de la valeur des pieces en fonction du joueur qui a le trait */
    int signe = (*plateau.JoueurTrait).signe;
	/* Permet de changer la dir des pions en fonction de qui a le trait et de ca couleur */
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
        Initialiser('N', 'B');
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

            //printf("tap n to continue\n\n");
            //scanf("%s", coup);

			// Je recupere le prochaine coup et je regarde si c'est la fin
			fscanf(file, "%s", coup);
            finPartie = EstCeFinPartie(coup);
        } while (finPartie == 0);

    } else {
        printf("Fichier %s ne peut pas etre ouvert\n", nomFichier);
    }
}