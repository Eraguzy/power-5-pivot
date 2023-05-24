#include "header.h"

int main(){
    int n;
    int round=1; //allows you to alternate the player
    int columns, lines; // Variables for columns width and columns height of the tray
    char nogravity; // if nogravity = y, then there will be the 4 nogravity slots 
    int checkscanf;

    char chois;
    printf("Do you want to continue a previous game? \ny: yes          n: no\n");
    if (chois == 'y'){
        int success = loadGame(lines, columns, tab);
        if (!success){
            // If no game has been loaded, we start a new game
            printf("Starting a new game...\n");
        }
    } else{
        printf("Starting a new game...\n");
    }

    printf("\nWelcome to \033[31mCY-Connect\033[0m ! Let's start by choosing the game settings. \n\nSpecial feature in this program  : you can play with squares that have \033[35mno gravity\033[0m (looks like this : '\033[40m + \033[0m'). \nWould you like to play with these ?\ny: yes          n: no\n");

    do{ //play with or without nograv slots
        checkscanf=scanf(" %c", &nogravity);
        emptybuffer();
        if(checkscanf!=1 || (nogravity != 'y' && nogravity != 'n')) { //this part avoids bugs from scanf inputs
            printf("Please enter a valid value ('y' ou 'n').\n"); 
        }
    }while(checkscanf!=1 || nogravity!='y' && nogravity!='n');


    printf("\nYou can choose the number of \033[35mslots to align\033[0m to win: (Protip : you should choose \033[31m4\033[0m or \033[31m5\033[0m !).\n");
    do{ //win condition choice for the player : cannot be <=0
        checkscanf=scanf(" %d",&n);
        emptybuffer();
        if(checkscanf!=1 || n<=0){
            printf("Please enter a valid value (any positive integer).\n"); //this part avoids bugs from scanf inputs
        }
        else if(n>500){
            printf("Wow ! That escalated quickly. But I think you should use a lower number...\n"); // Well huh
        }
    }while(checkscanf!=1 || (n<=0 || n>500));



    printf("\nLet's play Connect %d !\nThe width must be between \033[31m8\033[0m and \033[31m%d\033[0m.",n, ROWO);
    do{
        printf("\nChoose the number of \033[35mcolumns\033[0m of the tray : \n");
        checkscanf=scanf(" %d", &columns);
        emptybuffer();
        if(checkscanf!=1|| (columns < 8 || columns > ROWO)){
            printf("\nPlease enter a valid value (between \033[31m8\033[0m and \033[31m10\033[0m)."); //this part avoids bugs from scanf inputs
        }
    } while(checkscanf!=1 || (columns < 8 || columns > ROWO));

    printf("\nThe height must be between \033[31m6\033[0m and \033[31m%d\033[0m.", COLO);
    do{
        printf("\nChoose the number of \033[35mlines\033[0m of the tray : \n");
        checkscanf=scanf(" %d", &lines);
        emptybuffer();
        if(checkscanf!=1|| (columns < 8 || columns > ROWO)){
            printf("\nPlease enter a valid value (between \033[31m6\033[0m and \033[31m8\033[0m)."); //this part avoids bugs from scanf inputs
        }
    } while(checkscanf!=1 || (lines < 6 || lines > COLO));


    #if 0
    char* addr=malloc(sizeof(char)*lines*columns);
    char (*tab)[columns] = (char (*)[columns])addr;
    #endif

    char** tab = malloc(sizeof(char*)*lines);     //creates the array for the game

    if (tab == NULL) {
        printf("malloc error\n");
        return 0;
    }

    for (int j=0; j<lines; j++){
        tab[j] = malloc(sizeof(char)*columns);  
        if (tab == NULL) {
            printf("malloc error\n");
            return 0;  
        }
    }

    for (int i=0; i<lines; i++){
        for (int j=0; j<columns; j++){
            tab[i][j]=' ';          //initializes the entire array with spaces, then puts the no-gravity slots
        }
    }

    if (nogravity == 'y'){ //applies nogravity slots if chosen by user
        tab[0][0]='+';
        tab[0][columns-1]='+';
        tab[lines-1][0]='+';
        tab[lines-1][columns-1]='+';
    }

    printf("\n\n\n\nLet's go ! The game is about to start. Have fun ;)\n\n\n\n");
    sleep(3);

    do{ //game starts here
        displayer(lines, columns, tab);
        fill(lines, columns, tab, choice(round, lines, columns ,tab));
        round++;
    }while(align(n, lines, columns, tab) && notfull(lines, columns, tab)); //verifies the two conditions to end the game

    return 0;
}