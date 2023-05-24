#include "header.h"

void displayer(int lines, int columns, char **tab){ 
    printf("╔═══");
    for (int i=0; i<columns-1; i++){
        printf("╦═══");              //first line
    }
    printf("╗\n");


    for (int i=0; i<lines-1; i++){
        for (int j=0; j<columns; j++){    //loop for tab values + colors (between lines)
            if(tab[i][j]=='x'){
                printf("║ \033[31m%c\033[0m ",tab[i][j]); //red
            }
            else if(tab[i][j]=='+'){ 
                printf("║\033[40m %c \033[0m",tab[i][j]); //black bg
            }
            else{ 
                printf("║ \033[36m%c\033[0m ",tab[i][j]); //light blue
            }
        }
        printf("║\n");

        printf("╠═══");
        for (int i=0; i<columns-1; i++){
            printf("╬═══");              //loop for middle width lines
        }
        printf("╣\n");
    }

    for (int j=0; j<columns; j++){    //loop for tab values + colors (between lines) (last line)
        if(tab[lines-1][j]=='x'){
            printf("║ \033[31m%c\033[0m ",tab[lines-1][j]); //red
        }
        else if(tab[lines-1][j]=='+'){
            printf("║\033[40m %c \033[0m",tab[lines-1][j]); //red
        }
        else{
            printf("║ \033[36m%c\033[0m ",tab[lines-1][j]); //light blue
        }
    }
    printf("║\n");

    printf("╚═══");
    for (int i=0; i<columns-1; i++){
        printf("╩═══");              //last line
    }
    printf("╝\n");

    int count=0; 
    for (int i=0; i<columns; i++){
        count++;
        printf("| %2d",count);
    }
    printf("|\n");           //number of colones
}
