
/* echec.h : entete definissant toutes les fonctions necessaire au jeux d'echec */

#ifndef ECHEC
#define ECHEC

/* Enumeration pour l'association piece numero                                    */
/* Les pieces de l'IA sont positives et les pieces de l'adversaire sont negatives */
enum piece {
    Pion = 1,
    Tour = 2,
    Cavalier = 3,
    Fou = 4,
    Dame = 5,
    Roi = 10,
};

/* -------------------------------------------------------------------------- */
/* Structure memorisant les informations sur le plateu de jeux                */
/* Rmq : ordinateur toujours en haut                                          */
/* -------------------------------------------------------------------------- */
typedef struct Plateau
{
    int * tab;          /* Plateau de jeu. ATTENTION : Il est en une seul dimension */
    int N;              /* Taille de la plateau : 8 */
    char * couleurOrdi  /* "Blanc" ou "Noir" */
} Plateau_t;

/* -------------------------------------------------------------------------- */
/* Structure memorisant si les roques peuvent etre realise                    */
/* Rmq : on peut faire le roque a partir du moment                            */
/*        ou le roi et la tour n'ont pas encore bouger                        */
/* -------------------------------------------------------------------------- */
typedef struct Roque
{
    int peutPRJoueur;   /* Est ce que le joueur peut faire le petit roque */
    int peutPROrdi;     /* Est ce que l'ordinateur peut faire le petit roque */
    int peutGRJoueur;   /* Est ce que le joueur peut faire le grand roque */
    int peutGROrdi;     /* Est ce que l'ordinateur peut faire le grand roque */
} Roque_t;

/* -------------------------------------------------------------------------- */
/* Structure memorisant le dernier coup qui a ete jouer                       */
/* Rmq : permet principalement de faire la prise en passant                   */
/* -------------------------------------------------------------------------- */
typedef struct CoupPrecedent
{
    int xAvant;
    int yAvant;
    int xApres;
    int yApres;
} CoupPrecedent_t;


/* -------------------------------------------------------------------------- */
/* Initialiser : Initialisation du plateu, des roque et du coup precedent     */
/* Entree : void                                                              */
/* Sortie : void                                                              */
/* -------------------------------------------------------------------------- */
void Initialiser();

/* -------------------------------------------------------------------------- */
/* InitialiserPlateau : Initialise le plateau                                 */
/* Entree : void                                                              */
/* Sortie : void                                                              */
/* -------------------------------------------------------------------------- */
void InitialiserPlateau();

/* -------------------------------------------------------------------------- */
/* InitialiserRoque : Initialise tous les roques, ils peuvent tous etre jouer */
/* Entree : void                                                              */
/* Sortie : void                                                              */
/* -------------------------------------------------------------------------- */
void InitialiserRoque();

/* -------------------------------------------------------------------------- */
/* InitialiserRoque : Initialise tous les roques, ils peuvent tous etre jouer */
/* Entree : void                                                              */
/* Sortie : void                                                              */
/* -------------------------------------------------------------------------- */
void InitialiserCoupPrecedent();

/* -------------------------------------------------------------------------- */
/* InitialiserRoque : Initialise le plateau pour debuter une partie           */
/* Entree : void                                                              */
/* Sortie : void                                                              */
/* -------------------------------------------------------------------------- */
void InitialiserDebutPartie();

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
int PossibiliterPION(int *, int, int);

/* ----------------------------------------------------------------------------- */
/* PossibiliterTOUR : Renvoit toutes les coordonnes ou la tour peut se deplacer  */
/* Entree : int * tab : tableau des coordonnes ou la piece peut se deplacer      */
/*          int x : ligne de la piece                                            */
/*          int y : colenne de la piece                                          */
/* Sortie : void                                                                 */
/* ----------------------------------------------------------------------------- */
int PossibiliterTOUR(int *, int, int);

/* ------------------------------------------------------------------------------------- */
/* PossibiliterCAVALIER : Renvoit toutes les coordonnes ou le cavalier peut se deplacer  */
/* Entree : int * tab : tableau des coordonnes ou la piece peut se deplacer              */
/*          int x : ligne de la piece                                                    */
/*          int y : colenne de la piece                                                  */
/* Sortie : void                                                                         */
/* ------------------------------------------------------------------------------------- */
int PossibiliterCAVALIER(int *, int, int);

/* ----------------------------------------------------------------------------- */
/* PossibiliterFOU : Renvoit toutes les coordonnes ou la fou peut se deplacer    */
/* Entree : int * tab : tableau des coordonnes ou la piece peut se deplacer      */
/*          int x : ligne de la piece                                            */
/*          int y : colenne de la piece                                          */
/* Sortie : void                                                                 */
/* ----------------------------------------------------------------------------- */
int PossibiliterFOU(int *, int, int);

/* ----------------------------------------------------------------------------- */
/* PossibiliterROI : Renvoit toutes les coordonnes ou la roi peut se deplacer    */
/* Entree : int * tab : tableau des coordonnes ou la piece peut se deplacer      */
/*          int x : ligne de la piece                                            */
/*          int y : colenne de la piece                                          */
/* Sortie : void                                                                 */
/* ----------------------------------------------------------------------------- */
int PossibiliterROI(int *, int, int);

/* ----------------------------------------------------------------------------- */
/* PossibiliterDAME : Renvoit toutes les coordonnes ou la dame peut se deplacer  */
/* Entree : int * tab : tableau des coordonnes ou la piece peut se deplacer      */
/*          int x : ligne de la piece                                            */
/*          int y : colenne de la piece                                          */
/* Sortie : void                                                                 */
/* ----------------------------------------------------------------------------- */
int PossibiliterDAME(int *, int, int);

/* ------------------------------------------------------------------------------- */
/* JouerCoup : Joue le coup dont l'emplacement de depart et d'arriver sont donnees */
/* Entree : int xAvant : ligne de la piece qui doit etre joue                      */
/*          int yAvant : colonne de la piece qui doit etre joue                    */
/*          int xApres : ligne ou la piece doit etre joue                          */
/*          int yApres : colonne ou la piece doit etre joue                        */
/* Sortie : int piecePrise : 1 si une piece a ete prise, 0 sinon                   */
/* ------------------------------------------------------------------------------- */
int JouerCoup(int, int, int, int);

/* ----------------------------------------------------------------------------- */
/* JouerPetitRoque : Joue le petit roque                                         */
/* Entree : int ligne : ligne ou se situe le roi et la tour                      */
/* Sortie : void                                                                 */
/* ----------------------------------------------------------------------------- */
void JouerPetitRoque(int);

/* ----------------------------------------------------------------------------- */
/* JouerGrandRoque : Joue le grand roque                                         */
/* Entree : int ligne : ligne ou se situe le roi et la tour                      */
/* Sortie : void                                                                 */
/* ----------------------------------------------------------------------------- */
void JouerGrandRoque(int);

/* ----------------------------------------------------------------------- */
/* Lecture de fichier PGN dans lequel les entetes ont ete enlever          */
/* Entree : char * nomFichier : nom du fichier ou sont stocker les parties */
/* Sortie : void                                                           */
/* ----------------------------------------------------------------------- */
void LectureFichierPGN(char *);



#endif