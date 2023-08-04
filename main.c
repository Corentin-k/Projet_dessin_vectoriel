
#include "commands.h"
#include "stdio.h"
/*
 * Boucle principale du jeu qui
 * 1- creer la zone de dessin
 * 2- En boucle demande une commande
 *    la lis et l'éxécute
 */
int main() {
    unsigned int taille,largeur=20;
    printf("Bienvenue dans ce projet en C de dessin vectoriel  !!");
    int input;
    do{
        printf("\nTout d'abord choisissez une taille pour votre zone de dessin : ");
        input= scanf("%d", &taille);
        if (input != 1 || taille <= 0){
            printf("Veuillez entrez un entier positif uniquement");
            while (getchar() != '\n');
        }
    }while (input != 1 || taille <= 0);

    while (getchar() != '\n');
    Area* area=create_area(taille, taille);
    clear_area(area);
    int quit=0;

    while (quit==0) {
        Command *cmd = create_command();
        read_from_stdin(cmd);
        quit=read_exec_command( cmd,area);

    }

    delete_area(area);
    return 0;
}
