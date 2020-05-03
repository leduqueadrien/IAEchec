
#ifndef AFFICHAGEECHEC
#define AFFICHAGEECHEC

#include "echec.h"

#define AfficherCouleur(couleur, fond, text) printf("\033[%d;%dm  %c \033[0m", couleur, fond, text)
#define ClrScreen() printf("\033[H\033[2J")

enum CouleurText {
	Black_T	= 30,
	Red_T	= 31,
	Green_T	= 32,
	Yellow_T= 33,
	Blue_T	= 34,
	Purple_T= 35,
	Cyan_T	= 36,
	Grey_T	= 37,
};

enum CouleurFond {
	Black_F	= 40,
	Red_F	= 41,
	Green_F	= 42,
	Yellow_F= 43,
	Blue_F	= 44,
	Purple_F= 45,
	Cyan_F	= 46,
	Grey_F	= 47,
};

char AfficherPiece(int, int);
void AfficherPlateau();

/* -------------------------------------------------------------------------- */
/* AfficherPlateau : Affiche le plateau de jeu dans la console                */
/* Entree : void                                                              */
/* Sortie : void                                                              */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* AfficherPlateau : Affiche la piece dans la console                         */
/* Entree : int x : ligne de la piece                                         */
/*          int y : colenne de la piece                                       */
/* Sortie : char piece : Lettre coresspondant a la piece (P,T,C,F,R,D)        */
/* -------------------------------------------------------------------------- */


#endif