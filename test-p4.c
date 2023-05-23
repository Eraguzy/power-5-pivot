#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

#define ROWO 10 //box width
#define COLO 8 //box height


void displayer(int lines, int columns, char **tab){ //fix esthétique ═ ║ ═ ╔ ╦ ╗ ╠ ╬ ╣ ╚ ╩ ╝
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

int endgame(char slot, int lines, int columns, char** tab){
    displayer(lines, columns, tab);
    if(slot=='x'){
        printf("player 1 (\033[31mx\033[0m) wins !\n");
    }
    else{
        printf("player 2 (\033[36mo\033[0m) wins !\n");
    }
    return 0;
}

int notfull(int lines, int columns, char ** tab){ //checks every round if the array is fully filled
    for (int j=0; j<columns; j++){
        if(tab[0][j]==32){
            return 1;
        }
    }
    displayer(lines, columns, tab);
    printf("Draw !\n");
    return 0;
}

int align4(int n, int lines, int columns, char **tab) {
    int count = 0;

    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            if (tab[i][j] != ' ') {
                count = 0;

                // Horizontal check
                for (int k = 0; k < n && j + k < columns; k++) {
                    if (tab[i][j] == tab[i][j + k]) {
                        count++;
                    }
                }
                if (count == n) {
                    endgame(tab[i][j], lines, columns, tab);
                    return 0;
                }

                count = 0;

                // Vertical check
                for (int k = 0; k < n && i + k < lines; k++) {
                    if (tab[i][j] == tab[i + k][j]) {
                        count++;
                    }
                }
                if (count == n) {
                    endgame(tab[i][j], lines, columns, tab);
                    return 0;
                }

                count = 0;

                // Down Right Diagonal Check
                for (int k = 0; k < n && i + k < lines && j + k < columns; k++) {
                    if (tab[i][j] == tab[i + k][j + k]) {
                        count++;
                    }
                }
                if (count == n) {
                    endgame(tab[i][j], lines, columns, tab);
                    return 0;
                }

                count = 0;

                // Top Right Diagonal Check
                for (int k = 0; k < n && i - k >= 0 && j + k < columns; k++) {
                    if (tab[i][j] == tab[i - k][j + k]) {
                        count++;
                    }
                }
                if (count == n) {
                    endgame(tab[i][j], lines, columns, tab);
                    return 0;
                }
            }
        }
    }

    return 1;
}

int choice(int round, int lines, int columns, char **tab){ //takes player's column choice (for x's turn or o's turn)
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

void fill(int lines, int columns, char** tab, int column){ //applies gravity on ONE COLUMN ONLY
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

int main(){
    int n;
    int round=1; //allows you to alternate the player
    int columns, lines; // Variables for columns width and columns height of the tray
    char nogravity; // if nogravity = y, then there will be the 4 nogravity slots
    printf("\nWelcome to \033[31mCY-Connect\033[0m ! Let's start by choosing the game settings. \n\nSpecial feature in this program  : you can play with squares that have \033[35mno gravity\033[0m (looks like this : '\033[40m + \033[0m'). \nWould you like to play with these ?\ny: yes          n: no\n");
    do{ //play with or without nograv slots
        scanf(" %c", &nogravity);
        if (nogravity != 'y' && nogravity != 'n') {
            printf("Please enter a valid value ('y' ou 'n').\n"); 
        }
    }while(nogravity!='y' && nogravity!='n');


    printf("\nYou can choose the number of \033[35mslots to align\033[0m to win:\n");
    scanf("%d",&n);


    printf("\nThe width must be between \033[31m8\033[0m and \033[31m%d\033[0m.", ROWO);
    do{
        printf("\nChoose the number of \033[35mcolumns\033[0m of the tray : \n");
        scanf("%d", &columns);
    } while(columns < 8 || columns > ROWO);

    printf("\nThe height must be between \033[31m6\033[0m and \033[31m%d\033[0m.", COLO);
    do{
        printf("\nChoose the number of \033[35mlines\033[0m of the tray : \n");
        scanf("%d", &lines);
    } while(lines < 6 || lines > COLO);


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

    if (nogravity == 'y'){
        tab[0][0]='+';
        tab[0][columns-1]='+';
        tab[lines-1][0]='+';
        tab[lines-1][columns-1]='+';
    }

    printf("\n\n\n\nLet's go ! The game is about to start. Have fun ;)\n\n\n\n");
    sleep(3);

    do{
        displayer(lines, columns, tab);
        fill(lines, columns, tab, choice(round, lines, columns ,tab));
        round++;
    }while(align4(n, lines, columns, tab) && notfull(lines, columns, tab)); //verifies the two conditions to end the game

    return 0;
}