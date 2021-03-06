
#include <stdio.h>
#include "AffichageEchec.h"
#include <stdlib.h>

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

    // On affiche le numero du tour

    system("clear");

    printf("Tour numero : %d\n", plateau.numTour);
    printf("C'est a \"%s\" de jouer %c\n", (*plateau.JoueurTrait).nom, (*plateau.JoueurTrait).couleur);
	
	// Joueur2 en blanc
	if (plateau.couleurJoueurHaut == 'B') {
		for (int i=0; i<8; i++) {
			for (int j=0; j<8; j++) {
                int fond = (i*9+j)%2 == 0?47:40;
                AfficherCouleur(0, fond, ' ');
            }
            printf("\n");
			for (int j=0; j<8; j++) {
                int couleur = plateau.tab[i*plateau.N + j]>0?31:34;
                int fond = (i*9+j)%2 == 0?47:40;
                AfficherCouleur(couleur, fond, AfficherPiece(i, j));
            }
			printf("\n");
		}
	} else {
		for (int i=7; i>=0; i--) {
            for (int j=7; j>=0; j--) {
                int fond = (i*9+j)%2 == 0?47:40;
                AfficherCouleur(0, fond, ' ');
            }
            printf("\n");
			for (int j=7; j>=0; j--){
                int couleur = plateau.tab[i*plateau.N + j]>0?31:32;
                int fond = (i*9+j)%2 == 0?47:40;
                AfficherCouleur(couleur, fond, AfficherPiece(i, j));
            }
			printf("\n");
		}
	}
    printf("\n");
    printf("\n");

	
	if ((*(*plateau.JoueurTrait).adversaire).EstEnEchec == 1)
		printf("%s est en Echec\n", (*(*plateau.JoueurTrait).adversaire).nom);

	if ((*(*plateau.JoueurTrait).adversaire).EstEnEchec == 1)
		printf("%s est en Echec et Mat\n", (*(*plateau.JoueurTrait).adversaire).nom);
    
    printf("\n");
}
