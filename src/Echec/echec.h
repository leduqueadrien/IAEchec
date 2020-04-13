
/* echec.h : entete definissant toutes les fonctions necessaire au jeux d'echec */

#ifndef ECHEC
#define ECHEC

/* Enumeration pour l'association piece numero */
enum piece {
    Pion = 1,
    Tour = 2,
    Cavalier = 3,
    Fou = 4,
    Dame = 5,
    Roi = 10,
};

/* Liste chaine pour le stockage des cases ou une piece peut etre jouer */
typedef struct ListPossibiliter
{
    int x;
    int y;
    struct ListPossibiliter * suivant;
} ListePossibiliter;


/* -------------------------------------------------------- */
/* Plateau de jeu. ATTENTION : Il est en une seul dimension */
/* ordinateur toujours en haut                              */
/* -------------------------------------------------------- */
int PLATEAU [64];
int N;

int peutPRJoueur;
int peutPROrdi;
int peutGRJoueur;
int peutGROrdi;


/* -------------------------------------------------------------------------- */
/* InitialiserPlateau : Initialise le plateau d'echec pour debuter une partie */
/* Entree : void                                                              */
/* Sortie : void                                                              */
/* -------------------------------------------------------------------------- */
void InitialiserPlateau();

/* -------------------------------------------------------------------------- */
/* RemiseAZero : Met a zero toutes les cases du plateau                       */
/* Entree : void                                                              */
/* Sortie : void                                                              */
/* -------------------------------------------------------------------------- */
void RemiseAZero();

/* -------------------------------------------------------------------------- */
/* AfficherPlateau : Affiche le plateau de jeu dans la console                */
/* Entree : void                                                              */
/* Sortie : void                                                              */
/* -------------------------------------------------------------------------- */
void AfficherPlateau();

/* -------------------------------------------------------------------------- */
/* AfficherPlateau : Affiche la piece dans la console                         */
/* Entree : int x : ligne de la piece                                         */
/*          int y : colenne de la piece                                       */
/* Sortie : char piece : Lettre coresspondant a la piece (P,T,C,F,R,D)        */
/* -------------------------------------------------------------------------- */
char AfficherPiece();

/* ----------------------------------------------------------------------------- */
/* PossibiliterPION : Renvoit toutes les coordonnes ou le pions peut se deplacer */
/* Entree : int x : ligne de la piece                                            */
/*          int y : colenne de la piece                                          */
/* Sortie : void                                                                 */
/* ----------------------------------------------------------------------------- */
int * PossibiliterPION(int, int);

/* ----------------------------------------------------------------------------- */
/* PossibiliterTOUR : Renvoit toutes les coordonnes ou la tour peut se deplacer  */
/* Entree : int x : ligne de la piece                                            */
/*          int y : colenne de la piece                                          */
/* Sortie : void                                                                 */
/* ----------------------------------------------------------------------------- */
int * PossibiliterTOUR(int, int);

/* ------------------------------------------------------------------------------------- */
/* PossibiliterCAVALIER : Renvoit toutes les coordonnes ou le cavalier peut se deplacer  */
/* Entree : int x : ligne de la piece                                                    */
/*          int y : colenne de la piece                                                  */
/* Sortie : void                                                                         */
/* ------------------------------------------------------------------------------------- */
int * PossibiliterCAVALIER(int, int);

/* ----------------------------------------------------------------------------- */
/* PossibiliterFOU : Renvoit toutes les coordonnes ou la fou peut se deplacer    */
/* Entree : int x : ligne de la piece                                            */
/*          int y : colenne de la piece                                          */
/* Sortie : void                                                                 */
/* ----------------------------------------------------------------------------- */
int * PossibiliterFOU(int, int);

/* ----------------------------------------------------------------------------- */
/* PossibiliterROI : Renvoit toutes les coordonnes ou la roi peut se deplacer    */
/* Entree : int x : ligne de la piece                                            */
/*          int y : colenne de la piece                                          */
/* Sortie : void                                                                 */
/* ----------------------------------------------------------------------------- */
int * PossibiliterROI(int, int);

/* ----------------------------------------------------------------------------- */
/* PossibiliterDAME : Renvoit toutes les coordonnes ou la dame peut se deplacer  */
/* Entree : int x : ligne de la piece                                            */
/*          int y : colenne de la piece                                          */
/* Sortie : void                                                                 */
/* ----------------------------------------------------------------------------- */
int * Possibiliter(int, int);

/* ----------------------------------------------------------------------- */
/* Lecture de fichier PGN ou l'entete a ete enlever                        */
/* Entree : char * nomFichier : nom du fichier ou sont stocker les parties */
/* Sortie : void                                                           */
/* ----------------------------------------------------------------------- */
void LectureFichierPGN(char *);



#endif