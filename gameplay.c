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
    char pivotDirection; //left or right

    printf("Choose the size of the pivot (3 or 5):\n");
    do{
        checkscanf = scanf(" %d", &pivotSize);
        emptybuffer();
        if(checkscanf != 1 || (pivotSize != 3 && pivotSize != 5)) { //this part avoids bugs from scanf inputs
            printf("Please enter a valid entry ('3' or '5').\n"); 
        }
    } while(checkscanf != 1 || (pivotSize != 3 && pivotSize != 5));


    printf("Choose the row index of the pivot (1-%d): \n", lines);
    do {
        checkscanf = scanf("%d", &pivotRow);
        emptybuffer();
        pivotRow--;
        if(checkscanf != 1 || (pivotRow < 0 && pivotRow >= lines)) { //this part avoids bugs from scanf inputs
            printf("Please enter a valid entry (between 1 and %d).\n", lines); 
        }
    } while(checkscanf != 1 || (pivotRow < 0 || pivotRow >= lines));


    printf("Choose the column index of the pivot (1-%d): ", columns);
    do {
        checkscanf = scanf("%d", &pivotColumn);
        pivotColumn--;
        emptybuffer();
        if(checkscanf != 1 || (pivotColumn < 0 && pivotColumn >= columns)) { //this part avoids bugs from scanf inputs
            printf("Please enter a valid entry (between 1 and %d).\n", columns); 
        }
    } while(checkscanf != 1 || (pivotColumn < 0 || pivotColumn >= columns));

    printf("Choose the direction to rotate the slots:\nr: right (clockwise)          l: left (anticlockwise)\n");
    do {
        checkscanf = scanf(" %c", &pivotDirection);
        emptybuffer();
        if(checkscanf != 1 || (pivotDirection != 'r' && pivotDirection != 'l')) { //this part avoids bugs from scanf inputs
            printf("Please enter a valid entry ('r' or 'l').\n"); 
        }
    } while(checkscanf != 1 || (pivotDirection != 'r' && pivotDirection != 'l'));

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
}