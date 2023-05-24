#include "header.h"


int choice(int round, int lines, int columns, char **tab){ 
    int column;
    if(round%2!=0){
        do{
            printf("\nIt's player 1's turn ! (\033[31mx\033[0m)\nwhich column are you choosing ?\n");
            scanf(" %d",&column);
            column-=1; //mismatch btw array index and display (range 0-6 and range 1-7)
        }while((column<0 || column>=columns) || tab[0][column]!=' ');
        tab[0][column]='x';
    }
    if(round%2==0){
        do{
            printf("\nIt's player 1's turn ! (\033[36mo\033[0m)\nwhich column are you choosing ?\n");
            scanf(" %d",&column);
            column-=1;
        }while((column<0 || column>=columns) || tab[0][column]!=' ');
        tab[0][column]='o';
    }
    return column;
}

void fill(int lines, int columns, char** tab, int column){ 
    int buffer, cond;
    do{
        cond=0;
        for (int i=0; i<lines-1; i++){
            if(tab[i+1][column]==' ' && tab[i][column]!=' ' && tab[i][column]!= '+'){ //no gravity for '+'
                cond=1;
                buffer=tab[i+1][column];
                tab[i+1][column]=tab[i][column];
                tab[i][column]=buffer;
            }
        }
    } while(cond);
}