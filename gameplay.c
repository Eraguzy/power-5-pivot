#include "header.h"


int choice(int round, int lines, int columns, int n, char **tab){ //asks the player (1 or 2) what columns he wants to play and returns this column //needs 'line' and 'column' parameters to check is the column is playable
    int column, checkscanf;
    if(round%2!=0){
        do{
            printf("\nIt's player 1's turn ! (\033[31mx\033[0m)\nwhich column are you choosing ?\n");
            checkscanf=scanf(" %d",&column);
            emptybuffer();

            if (column == 999){
                saveGame(lines, columns, round, n, tab);
                printf("Game saved. Exiting...\n");
                exit(0);
            }

            column-=1; //mismatch btw array index and display (range 0-6 and range 1-7)
        }while(checkscanf!=1 || ((column<0 || column>=columns) || tab[0][column]!=' ')); //only plays if very top slot is not filled
        tab[0][column]='x';
    }
    if(round%2==0){
        do{
            printf("\nIt's player 1's turn ! (\033[36mo\033[0m)\nwhich column are you choosing ?\n");
            checkscanf=scanf(" %d",&column);
            emptybuffer();

            if (column == 999){
                saveGame(lines, columns, round, n, tab);
                printf("Game saved. Exiting...\n");
                exit(0);
            }

            column-=1;

        }while(checkscanf!=1 || (column<0 || column>=columns) || tab[0][column]!=' ');
        tab[0][column]='o';
    }


    return column;
}

void fill(int lines, int columns, char** tab, int column){ //applies gravity on one column only
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

int pivotBoard(int lines, int columns, char** tab) {
    int checkscanf; //debug scanf
    int pivotSize; // 3 or 5
    int pivotRow, pivotColumn; //rows and columns index
    int buff; //buffer for rotation
    char pivotDirection; //left or right

    printf("\nTime to rotate !\nChoose the size of the pivot (3 or 5):\n");
    do{
        checkscanf = scanf(" %d", &pivotSize);
        emptybuffer();
        if(checkscanf != 1 || (pivotSize != 3 && pivotSize != 5)) { //this part avoids bugs from scanf inputs
            printf("Please choose a valid entry ('3' or '5').\n"); 
        }
    } while(checkscanf != 1 || (pivotSize != 3 && pivotSize != 5));


    printf("Choose the row index of the pivot : it cannot be outside the game (%d-%d) \n", (pivotSize/2)+1, lines-(pivotSize/2));
    do {
        checkscanf = scanf("%d", &pivotRow);
        emptybuffer();
        if(checkscanf != 1 || (pivotRow < (pivotSize/2)+1 || pivotRow > lines-(pivotSize/2))) { //this part avoids bugs from scanf inputs
            printf("Please choose a valid entry (between %d and %d).\n",(pivotSize/2)+1, lines-(pivotSize/2)); 
        }
    } while(checkscanf != 1 || (pivotRow < (pivotSize/2)+1 || pivotRow > lines-(pivotSize/2)));
    pivotRow--;


    printf("Choose the column index of the pivot : it cannot be outside the game (%d-%d) \n", (pivotSize/2)+1, columns-(pivotSize/2));
    do {
        checkscanf = scanf("%d", &pivotColumn);
        emptybuffer();
        if(checkscanf != 1 || (pivotColumn < (pivotSize/2)+1 || pivotColumn > columns-(pivotSize/2))) { //this part avoids bugs from scanf inputs
            printf("Please choose a valid entry (between %d and %d).\n",(pivotSize/2)+1, columns-(pivotSize/2)); 
        }
    } while(checkscanf != 1 || (pivotColumn < (pivotSize/2)+1 || pivotColumn > columns-(pivotSize/2)));
    pivotColumn--;

    printf("Choose the direction to rotate the slots:\nr: right (clockwise)          l: left (anticlockwise)\n");
    do {
        checkscanf = scanf(" %c", &pivotDirection);
        emptybuffer();
        if(checkscanf != 1 || (pivotDirection != 'r' && pivotDirection != 'l')) { //this part avoids bugs from scanf inputs
            printf("Please choose a valid entry ('r' or 'l').\n"); 
        }
    } while(checkscanf != 1 || (pivotDirection != 'r' && pivotDirection != 'l'));



    char** buffer = malloc(sizeof(char*) * pivotSize); //malloc for buffer tab
    if (buffer == NULL) {
        printf("malloc error\n");
        exit(0);
    }
    for (int j = 0; j < pivotSize; j++) {
        buffer[j] = malloc(sizeof(char) * pivotSize);
        if (buffer[j] == NULL) {
            printf("malloc error\n");
            exit(0);
        }
    }

    for (int k = 0, i=pivotRow-(pivotSize/2); k < pivotSize; k++, i++) {
        for (int l = 0, j=pivotColumn-(pivotSize/2); l < pivotSize; l++, j++) {
            buffer[k][l] = tab[i][j]; // copy to the buffer
        }
    }

    if(pivotSize==3){
        if(pivotDirection=='r'){
            tab[pivotRow-1][pivotColumn-1]=buffer[2][0];
            tab[pivotRow-1][pivotColumn]=buffer[1][0];
            tab[pivotRow-1][pivotColumn+1]=buffer[0][0];

            tab[pivotRow][pivotColumn-1]=buffer[2][1];
            tab[pivotRow][pivotColumn+1]=buffer[0][1];

            tab[pivotRow+1][pivotColumn-1]=buffer[2][2];
            tab[pivotRow+1][pivotColumn]=buffer[1][2];
            tab[pivotRow+1][pivotColumn+1]=buffer[0][2];
        }
        else if(pivotDirection=='l'){ //3 times
        #if 0
            tab[pivotRow-1][pivotColumn-1]=buffer[][];
            tab[pivotRow-1][pivotColumn]=buffer[][];
            tab[pivotRow-1][pivotColumn+1]=buffer[][];

            tab[pivotRow][pivotColumn-1]=buffer[][];
            tab[pivotRow][pivotColumn+1]=buffer[][];

            tab[pivotRow+1][pivotColumn-1]=buffer[][];
            tab[pivotRow+1][pivotColumn]=buffer[][];
            tab[pivotRow+1][pivotColumn+1]=buffer[][];
        #endif
        }
    }
    else if(pivotSize==5){
        if(pivotDirection=='r'){
            
        }
        else if(pivotDirection=='l'){
            
        }
    }
    return pivotColumn;


    #if 0
    if (pivotSize == 3 || pivotSize == 5) {
        // Calculate the boundaries of the pivot square
        int pivotStartRow = pivotRow - pivotSize / 2;
        int pivotEndRow = pivotStartRow + pivotSize;
        int pivotStartColumn = pivotColumn - pivotSize / 2;
        int pivotEndColumn = pivotStartColumn + pivotSize;

        // Creates buffer
        char** buffer = malloc(sizeof(char*) * pivotSize);
        if (buffer == NULL) {
            printf("malloc error\n");
            exit(0);
        }
        for (int j = 0; j < pivotSize; j++) {
            buffer[j] = malloc(sizeof(char) * pivotSize);
            if (buffer[j] == NULL) {
                printf("malloc error\n");
                exit(0);
            }
        }

        // Initialize i and j
        int i = pivotStartRow;
        int j = pivotStartColumn;

        for (int k = 0; k < pivotSize; k++) {
            for (int l = 0; l < pivotSize; l++) {
                buffer[k][l] = tab[i][j]; // Copy to the buffer
                j++; // Increment j to move to the next column of tab
            }
            i++; // Increment i to move to the next row of tab
            j = pivotStartColumn; // Reset j to the value of pivotStartColumn to go back to the first column of the pivot
        }

        i = pivotStartRow;
        j = pivotStartColumn;
        
        if (pivotDirection == 'r') {
            // Rotate the pieces inside the pivot square to the right
            for (int k = 0; k < pivotSize; k++, i++) {
                for (int l = 0; l < pivotSize; l++, j++) {
                    // Calculate the new coordinates after rotation
                    int newRow = pivotRow + (l - pivotColumn);
                    int newColumn = pivotColumn - (k - pivotRow);
                    // Move the piece to the new coordinates
                    tab[newRow][newColumn] = buffer[i][j];
                }
                j = pivotStartColumn; // Reset j to the value of pivotStartColumn for each new row
            }
        }
        else if (pivotDirection == 'l') {
            // Rotate the pieces inside the pivot square to the left
            for (int k = 0; k < pivotSize; k++, i++) {
                for (int l = 0; l < pivotSize; l++, j++) {
                    // Calculate the new coordinates after rotation
                    int newRow = pivotRow - (l - pivotColumn);
                    int newColumn = pivotColumn + (k - pivotRow);
                    // Move the piece to the new coordinates
                    tab[newRow][newColumn] = buffer[i][j];
                }
                j = pivotStartColumn; // Reset j to the value of pivotStartColumn for each new row
            }
        }
        for (int j = 0; j < pivotSize; j++) { // free buffer
            free(buffer[j]);
        }
        free(buffer);
    }

    return pivotSize;
    #endif
}