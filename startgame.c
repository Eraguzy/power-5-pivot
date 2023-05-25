#include "header.h"

void parameters(int* lines,int* columns,int* round, int* n, char*** tab){

    char nogravity, entry; // if nogravity = y, then there will be the 4 nogravity slots 
    int checkscanf;

    printf("Would you like to resume a previous game? \ny: yes          n: no\n"); //ask the user if he wants to load a save
    do{
        checkscanf=scanf(" %c",&entry);
        emptybuffer();
        if(checkscanf!=1 || (entry != 'y' && entry != 'n')){
            printf("Please enter a valid value ('y' ou 'n').\n"); 
        }
    }while(checkscanf!=1 || (entry != 'y' && entry != 'n'));

    if(entry == 'y'){
        loadGame(lines, columns, round, n, tab);
        if(*tab == NULL){
            // If no game has been loaded, we start a new game
            printf("malloc error\n");
            exit(0);
        }
    }
    else{
        printf("\nStarting a new game...\n");
        sleep(2);
        printf("\nWelcome to \033[31mCY-Connect\033[0m ! Let's start by setting up the game settings. \n\nSpecial feature in this program  : you can play with squares that have \033[35mno gravity\033[0m (looks like this : '\033[40m + \033[0m'). \nWould you like to play with these ?\ny: yes          n: no\n");

        *round=1;

        do{ //play with or without nograv slots
            checkscanf=scanf(" %c", &nogravity);
            emptybuffer();
            if(checkscanf!=1 || (nogravity != 'y' && nogravity != 'n')) { //this part avoids bugs from scanf inputs
                printf("Please enter a valid entry ('y' ou 'n').\n"); 
            }
        }while(checkscanf!=1 || (nogravity != 'y' && nogravity != 'n'));



        printf("\nYou can choose the number of \033[35mslots to align\033[0m to win: (Protip : you should choose \033[31m4\033[0m or \033[31m5\033[0m !).\n");
        do{ //win condition choice for the player : cannot be <=0
            checkscanf=scanf(" %d",n);
            emptybuffer();
            if(checkscanf!=1 || *n<=0){
                printf("Please enter a valid value (any positive integer).\n"); //this part avoids bugs from scanf inputs
            }
            else if(*n>500){
                printf("Wow ! That escalated quickly. But I think you should use a lower number...\n"); // Well huh
            }
        }while(checkscanf!=1 || (*n<=0 || *n>500));

        printf("\nLet's play Connect %d !\nThe width must be between \033[31m8\033[0m and \033[31m%d\033[0m.", *n, ROWO);
        
        do{ //width choice
            printf("\nChoose the number of \033[35mcolumns\033[0m of the tray : \n");
            checkscanf=scanf(" %d", columns);
            emptybuffer();
            if(checkscanf!=1|| (*columns < 8 || *columns > ROWO)){
                printf("\nPlease enter a valid value (between \033[31m8\033[0m and \033[31m10\033[0m)."); //this part avoids bugs from scanf inputs
            }
        } while(checkscanf!=1 || (*columns < 8 || *columns > ROWO));

        printf("\nThe height must be between \033[31m6\033[0m and \033[31m%d\033[0m.", COLO);

        do{ //height choice
            printf("\nChoose the number of \033[35mlines\033[0m of the tray : \n");
            checkscanf=scanf(" %d", lines);
            emptybuffer();
            if(checkscanf!=1|| (*columns < 8 || *columns > ROWO)){
                printf("\nPlease enter a valid value (between \033[31m6\033[0m and \033[31m8\033[0m)."); //this part avoids bugs from scanf inputs
            }
        } while(checkscanf!=1 || (*lines < 6 || *lines > COLO));


    
        *tab = malloc(sizeof(char*) * (*lines));     //creates the array for the game
        if (*tab == NULL) {
            printf("malloc error\n");
            exit(0);
        }
        for (int j=0; j< *lines; j++){
            (*tab)[j] = malloc(sizeof(char) * (*columns));  
            if ((*tab)[j] == NULL) {
                printf("malloc error\n");
                exit(0);  
            }
        }
        for (int i=0; i< *lines; i++){
            for (int j=0; j< *columns; j++){
                (*tab)[i][j]=' ';          //initializes the whole array with spaces, then puts the no-gravity slots
            }
        }

        if (nogravity == 'y'){ //applies nogravity slots if chosen by user
            (*tab)[0][0]='+';
            (*tab)[0][(*columns)-1]='+';
            (*tab)[(*lines)-1][0]='+';
            (*tab)[(*lines)-1][(*columns)-1]='+';
        }

        printf("\n\n\n\nLet's go ! The game is about to start. Have fun ;)\n(You can save your game at any moment of the game by typing '\033[31m999\033[0m')\n\n\n");
        sleep(3);
    }
}