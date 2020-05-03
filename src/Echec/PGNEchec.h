
#ifndef PGNECHEC
#define PGNECHEC

#include "echec.h"

void LectureFichierPGN(char *);
int EstCeFinPartie(char *);
int ConvertirCharPiece(char);
int ConvertirColonneInt(char);
int ConvertLigneInt(char);
void LireCoup(char *);

void DeduirCoup(int * xAvant, int * yAvant, int xApres, int yApres, int piece, int prisePiece);
void DeduirROI(int * xAvant, int * yAvant, int xApres, int yApres);
void DeduirDAME(int * xAvant, int * yAvant, int xApres, int yApres);
void DeduirFOU(int * xAvant, int * yAvant, int xApres, int yApres, int estDame);
void DeduirCAVALIER(int * xAvant, int * yAvant, int xApres, int yApres);
void DeduirTOUR(int * xAvant, int * yAvant, int xApres, int yApres, int estDame);
void DeduirPOIN(int * xAvant, int * yAvant, int xApres, int yApres, int prisePiece);

/* ----------------------------------------------------------------------------- */
/* LireCoup : Interprete le coup au format PGN                                   */
/* Entree : char * coup : chaine de caractere contenant le coup a interpreter    */
/* Sortie : void                                                                 */
/* ----------------------------------------------------------------------------- */

/* ----------------------------------------------------------------------- */
/* Lecture de fichier PGN dans lequel les entetes ont ete enlever          */
/* Entree : char * nomFichier : nom du fichier ou sont stocker les parties */
/* Sortie : void                                                           */
/* ----------------------------------------------------------------------- */

#endif