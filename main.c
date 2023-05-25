#include "header.h"

int main(){
    int n; //alignment to win
    int round; //allows you to alternate the player
    int columns, lines; // Variables for columns width and columns height of the tray
    char** tab;

    parameters(&lines, &columns, &round, &n, &tab);

    do{ //game starts here
        displayer(lines, columns, tab);
        fill(lines, columns, tab, choice(round, lines, columns , n, tab));
        round++;
    }while(align(n, lines, columns, tab) && notfull(lines, columns, tab)); //verifies the two conditions to end the game
    return 0;
}