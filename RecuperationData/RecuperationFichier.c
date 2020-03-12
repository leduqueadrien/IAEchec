#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// commande a executer : 
// wget https://chesstempo.com/requests/download_game_pgn.php?gameids= + ID

char * CreationCommande (char * URL, char * ID);

int main() {
    
    char fileName [25] = "IDPartieTest.txt";
    char URL [100] = "https://chesstempo.com/requests/download_game_pgn.php?gameids=";
    
    int tailleID = 7;
    FILE * file = NULL;
    file = fopen(fileName, "r");

    if (file == NULL) {
        printf("Le fichier \"%s\" n'a pu être ouvert\n", fileName);
    } else {
        printf("Le fichier \"%s\" est ouvert\n", fileName);

        printf("Création du répertoir\n");

        if (system("mkdir dataBasChess") == 1) {
            printf("Le répertoir n'a pas pu être créé\n");
        } else {
            printf("Le répertoir a été créé\n");

            char * strID = malloc(sizeof(char)*tailleID);
            char * commandecomplete;
            while (feof(file) == 0) {
                int i;
                for (i=0; i<tailleID; i++) {
                    fscanf(file, "%c", (strID+i));  // A changer. fgets ?
                }
                commandecomplete = CreationCommande(URL, strID);
                printf("%s\n", commandecomplete);
                printf("Telechargement du fichier \"%s\"\n", strID);

                system( commandecomplete );
                printf("Telechargement terminé\n");
                                
                fscanf(file, "%c", strID);
                
            }
            free(strID);
            free(commandecomplete);
        }
        
        fclose(file);
    }
        

    return 0;
}


char * CreationCommande (char * URL, char * ID){
    int tailleURL = strlen(URL);
    char commande [] =  "wget ./dataBasChess ";
    int taillecommande = strlen(commande);
    char * CommandeComplete = malloc(sizeof(char)*(taillecommande + tailleURL + 7));
    int i;
    for (i=0; i<taillecommande; i++)
        *(CommandeComplete+i) = *(commande+i);
    for (i=0; i<tailleURL; i++)
        *(CommandeComplete+taillecommande+i) = *(URL+i);
    for (i=0; i<7; i++)
        *(CommandeComplete+taillecommande+tailleURL+i) = *(ID+i);
    return CommandeComplete;
}
