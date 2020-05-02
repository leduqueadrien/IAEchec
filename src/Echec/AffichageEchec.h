
#ifndef AFFICHAGEECHEC
#define AFFICHAGEECHEC

#include "echec.h"

#define couleur(couleur, fond, text) printf("\033[%s;%sm%s\033[0m", fond, param, text)
#define clrScreen() printf("\033[H\033[2J")

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


#endif