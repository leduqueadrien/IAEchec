#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// commande a executer : 
// wget https://chesstempo.com/requests/download_game_pgn.php?gameids= + ID

//commande a executer dans le terminal : nohup ./prog > sortieStandard

#define TAILLEID 8

char * CreationCommande (char * URL, char * ID);

int main() {
    
    char fileName [25] = "IDPartieTest.txt";
    char URL [100] = "https://old.chesstempo.com/requests/download_game_pgn.php?gameids=";
    
    FILE * file = fopen(fileName, "r");

    if (file == NULL) {
        printf("Le fichier \"%s\" n'a pu être ouvert\n", fileName);
    } else {
        printf("Le fichier \"%s\" est ouvert\n", fileName);

        printf("Création du répertoire\n");

        if (system("mkdir dataBaseChess") == 1) {
            printf("Le répertoire n'a pas pu être créé\n");
        } else {
            printf("Le répertoire a été créé\n\n");

            char strID [TAILLEID];
            char * commandecomplete;
            int cpt = 0;
            while (feof(file) == 0) {
                cpt++;
                fgets(strID, TAILLEID, file);

                commandecomplete = CreationCommande(URL, strID);
                //printf("Telechargement du fichier \"%s\"\n", strID);
                //printf("%s\n", commandecomplete);
                
                system( commandecomplete );
                //printf("Telechargement terminé\n\n");
                                
                fscanf(file, "%c", strID);

                if (cpt%10 == 0)
                    printf("%d parties\n", cpt);

            }
            free(commandecomplete);
            printf("\nFIN\n%d parties telechargées\n", cpt);
        }
        fclose(file);
    }
        

    return 0;
}


char * CreationCommande (char * URL, char * ID){
    int tailleURL = strlen(URL);
    char commande [] =  "wget -P ./dataBaseChess ";
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
