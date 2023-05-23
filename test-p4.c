#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

#define ROWS 10 //box width
#define COLONNE 8 //box height


void displayer(int colonne, int rows, char **tab){ //fix esthétique ═ ║ ═ ╔ ╦ ╗ ╠ ╬ ╣ ╚ ╩ ╝
    printf("╔═══");
    for (int i=0; i<rows-1; i++){
        printf("╦═══");              //first line
    }
    printf("╗\n");


    for (int i=0; i<colonne-1; i++){
        for (int j=0; j<rows; j++){    //loop for tab values + colors (between lines)
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
        for (int i=0; i<rows-1; i++){
            printf("╬═══");              //loop for middle width lines
        }
        printf("╣\n");
    }

    for (int j=0; j<rows; j++){    //loop for tab values + colors (between lines) (last line)
        if(tab[colonne-1][j]=='x'){
            printf("║ \033[31m%c\033[0m ",tab[colonne-1][j]); //red
        }
        else if(tab[colonne-1][j]=='+'){
            printf("║\033[40m %c \033[0m",tab[colonne-1][j]); //red
        }
        else{
            printf("║ \033[36m%c\033[0m ",tab[colonne-1][j]); //light blue
        }
    }
    printf("║\n");

    printf("╚═══");
    for (int i=0; i<rows-1; i++){
        printf("╩═══");              //last line
    }
    printf("╝\n");

    int count=0; 
    for (int i=0; i<rows; i++){
        count++;
        printf("| %2d",count);
    }
    printf("|\n");           //number of colones
}

int endgame(char case, int colonne, int rows, char** tab){
    ///temporory function : for rows follow, case by case to highlight winning cases
    displayer(colonne, rows, tab);
    if(case=='x'){
        printf("joueur 1 (\033[31mx\033[0m) a gagné !\n");
    }
    else{
        printf("joueur 2 (\033[36mo\033[0m) a gagné !\n");
    }
    return 0;
}

int notfull(int colonne, int rows, char ** tab){ //checks every round if the array is fully filled
    for (int j=0; j<rows; j++){
        if(tab[0][j]==32){
            return 1;
        }
    }
    displayer(colonne, rows, tab);
    printf("Equality !\n");
    return 0;
}

int align4(int n, int colonne, int rows, char **tab) {
    int count = 0;

    for (int i = 0; i < colonne; i++) {
        for (int j = 0; j < rows; j++) {
            if (tab[i][j] != ' ') {
                count = 0;

                // Horizontale verification
                for (int k = 0; k < n && j + k < rows; k++) {
                    if (tab[i][j] == tab[i][j + k]) {
                        count++;
                    }
                }
                if (count == n) {
                    endgame(tab[i][j], colonne, rows, tab);
                    return 0;
                }

                count = 0;

                // Vertical verification
                for (int k = 0; k < n && i + k < colonne; k++) {
                    if (tab[i][j] == tab[i + k][j]) {
                        count++;
                    }
                }
                if (count == n) {
                    endgame(tab[i][j], colonne, rows, tab);
                    return 0;
                }

                count = 0;

                // Down Right Diagonal Check
                for (int k = 0; k < n && i + k < colonne && j + k < rows; k++) {
                    if (tab[i][j] == tab[i + k][j + k]) {
                        count++;
                    }
                }
                if (count == n) {
                    endgame(tab[i][j], colonne, rows, tab);
                    return 0;
                }

                count = 0;

                // Top Right Diagonal Check
                for (int k = 0; k < n && i - k >= 0 && j + k < rows; k++) {
                    if (tab[i][j] == tab[i - k][j + k]) {
                        count++;
                    }
                }
                if (count == n) {
                    endgame(tab[i][j], colonne, rows, tab);
                    return 0;
                }
            }
        }
    }

    return 1;
}

int choice(int round, int colonne, int rows, char **tab){ //takes player's column choice (for x's turn or o's turn)
    int column;
    if(round%2!=0){
        do{
            printf("\nTime to player 1 to play (\033[31mx\033[0m)\nwhich colonne are you playing ?\n");
            scanf(" %d",&column);
            column-=1; //mismatch btw array index and display (range 0-6 and range 1-7)
        }while((column<0 || column>=rows) || tab[0][column]!=' ');
        tab[0][column]='x';
    }
    if(round%2==0){
        do{
            printf("\nTime to player 2 to play (\033[36mo\033[0m)\nwhich colonne are you playing ?\n");
            scanf(" %d",&column);
            column-=1;
        }while((column<0 || column>=rows) || tab[0][column]!=' ');
        tab[0][column]='o';
    }
    return column;
}

void fill(int colonne, int rows, char** tab, int column){ //applies gravity on ONE COLUMN ONLY
    int buffer, cond;
    do{
        cond=0;
        for (int i=0; i<colonne-1; i++){
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
    int rows, colonne; // Variables for rows width and rows height of the tray
    char nogravity; // if nogravity = y, then there will be the 4 nogravity slots
    printf("\nWelcome to \033[31mCY-Connect\033[0m ! Let's begin by choosing the game settings. \nLittle peculiarity in this program  : there is rows possibility to play with squares \033[35msans gravité\033[0m (symbolisées par '\033[40m + \033[0m'). \nSouhaites-tu jouer avec ces cases ?\ny: oui          n: non\n");
    do{ //play with or without nograv slots
        scanf(" %c", &nogravity);
        if (nogravity != 'y' && nogravity != 'n') {
            printf("Please enter a valid value ('y' ou 'n').\n"); 
        }
    }while(nogravity!='y' && nogravity!='n');


    printf("\nYou can choose the number of \033[35msquares to align\033[0m to win:\n");
    scanf("%d",&n);


    printf("\nThe width must be between \033[31m8\033[0m and \033[31m%d\033[0m.", ROWS);
    do{
        printf("\nChoose the number of rows \033[35mwidth\033[0m of the tray : \n");
        scanf("%d", &rows);
    } while(rows < 8 || rows > ROWS);

    printf("\nThe height must be between \033[31m6\033[0m and \033[31m%d\033[0m.", COLONNE);
    do{
        printf("\nChoose rows \033[35mhauteur\033[0m of the tray : \n");
        scanf("%d", &colonne);
    } while(colonne < 6 || colonne > COLONNE);


    #if 0
    char* addr=malloc(sizeof(char)*colonne*rows);
    char (*tab)[rows] = (char (*)[rows])addr;
    #endif

    char** tab = malloc(sizeof(char*)*colonne);     //creates the array for the game

    if (tab == NULL) {
        printf("malloc error\n");
        return 0;
    }

    for (int j=0; j<colonne; j++){
        tab[j] = malloc(sizeof(char)*rows);  
        if (tab == NULL) {
            printf("malloc error\n");
            return 0;  
        }
    }

    for (int i=0; i<colonne; i++){
        for (int j=0; j<rows; j++){
            tab[i][j]=' ';          //initializes the entire array with spaces, then puts the no-gravity slots
        }
    }

    if (nogravity == 'y'){
        tab[0][0]='+';
        tab[0][rows-1]='+';
        tab[colonne-1][0]='+';
        tab[colonne-1][rows-1]='+';
    }

    printf("\n\n\n\nLet's go ! The game is about to start. Have fun ;)\n\n\n\n");
    sleep(3);

    do{
        displayer(colonne, rows, tab);
        fill(colonne, rows, tab, choice(round, colonne, rows ,tab));
        round++;
    }while(align4(n, colonne, rows, tab) && notfull(colonne, rows, tab)); //verifies the two conditions to end the game

    return 0;
}