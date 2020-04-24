
/* echec.h : entete definissant toutes les fonctions necessaire au jeux d'echec */

#ifndef ECHEC
#define ECHEC

/* -------------------------------------------------------------------------- */
/* Enumeration pour l'association piece numero                                */
/* Rmq : Les pieces de l'IA sont positives et les pieces                      */            
/*       de l'adversaire sont negatives                                       */
/* -------------------------------------------------------------------------- */
enum piece {
    Pion = 1,
    Tour = 2,
    Cavalier = 3,
    Fou = 4,
    Dame = 5,
    Roi = 10,
};

typedef struct Joueur
{
    char * nom;
    int EstEnEchec;
    int EstEnEchecMat;
    int peutPetitRoque;
    int peutGrandRoque;
    char couleur;
    struct Joueur * adversaire;
} Joueur_t;


/* -------------------------------------------------------------------------- */
/* Structure memorisant si les roques peuvent etre realise                    */
/* Rmq : on peut faire le roque a partir du moment                            */
/*        ou le roi et la tour n'ont pas encore bouger                        */
/* -------------------------------------------------------------------------- */


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
    int valeurPieceJouer;
} CoupPrecedent_t;


/* -------------------------------------------------------------------------- */
/* Structure memorisant les informations sur le plateu de jeux                */
/* Rmq : Blanc toujours en Haut                                               */
/* -------------------------------------------------------------------------- */
typedef struct Plateau
{
    int * tab;          /* Plateau de jeu. ATTENTION : Il est en une seul dimension */
    int N;              /* Taille de la plateau : 8 */
    int aOrdiDeJouer;   /* Est ce a l'ordinateur de jouer */
    struct Joueur * joueur1;
    struct Joueur * joueur2;
    struct Joueur * JoueurTrait;
    struct CoupPrecedent coupPrecedent;
} Plateau_t;

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

void DeduirPOIN(int *, int *, int, int, int);

void DeduirTOUR(int *, int *, int, int);

void DeduirCAVALIER(int *, int *, int, int);

void DeduirFOU(int *, int *, int, int);

void DeduirDAME(int *, int *, int, int);

void DeduirROI(int *, int *, int, int);

void DeduirCoup(int *, int *, int, int, int, int);

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

/* ----------------------------------------------------------------------------- */
/* MAJRoque : fait la mise a jour des possibilites de jouer les roques           */
/* Entree : int x : ligne ou se situe la piece qui vient d'etre joue             */
/*          int y : colonne ou se situe la piece qui vient d'etre joue           */
/* Sortie : void                                                                 */
/* ----------------------------------------------------------------------------- */
void MAJRoque(int, int);

int ConvertirColonneInt(char carac);

int ConvertirCharPiece(char carac);

int ConvertLigneInt(char carac);

/* ----------------------------------------------------------------------------- */
/* LireCoup : Interprete le coup au format PGN                                   */
/* Entree : char * coup : chaine de caractere contenant le coup a interpreter    */
/*          int aOrdiDeJouer : booleen qui vaut 1 si c'est a l'ordi de jouer     */
/* Sortie : void                                                                 */
/* ----------------------------------------------------------------------------- */
void LireCoup(char *);

/* ----------------------------------------------------------------------- */
/* Lecture de fichier PGN dans lequel les entetes ont ete enlever          */
/* Entree : char * nomFichier : nom du fichier ou sont stocker les parties */
/* Sortie : void                                                           */
/* ----------------------------------------------------------------------- */
void LectureFichierPGN(char *);



#endif