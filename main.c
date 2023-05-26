#include "header.h"

int main(){
    int n; //alignment to win
    int round; //allows you to alternate the player
    int columns, lines; // Variables for columns width and columns height of the tray
    char** tab;

    parameters(&lines, &columns, &round, &n, &tab); //setup the game

    do{ //game starts here
        displayer(lines, columns, tab);
        fill(lines, columns, tab, choice(round, lines, columns , n, tab)); //gravity after player's choice
        if(align(n, lines, columns, tab)==0 || notfull(lines,columns, tab)==0){ //end of game if there is an end condition
            return 0;
        }

        displayer(lines, columns, tab);
        pivotBoard(lines, columns, tab);
        for(int i=0;i<columns;i++){
            fill(lines, columns, tab, i); //gravity after pivot
        }

        round++;
    }while(align(n, lines, columns, tab) && notfull(lines, columns, tab)); //verifies the two conditions to end the game after 
    return 0;
}