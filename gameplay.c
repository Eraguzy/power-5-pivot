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
        checkscanf=scanf(" %d", &pivotSize);
        emptybuffer();
        if(checkscanf!=1 || (pivotSize != 3 && pivotSize != 5)) { //this part avoids bugs from scanf inputs
            printf("Please enter a valid entry ('3' or '5').\n"); 
        }
    }while(checkscanf!=1 || (pivotSize != 3 && pivotSize != 5));


    printf("Choose the row index of the pivot (0-%d): \n", lines-1);
    do{
        checkscanf=scanf("%d", &pivotRow);
        emptybuffer();
        if(checkscanf!=1 || (pivotSize < 0 && pivotSize >= lines)) { //this part avoids bugs from scanf inputs
            printf("Please enter a valid entry (between 0 and %d).\n", lines-1); 
        }
    }while(checkscanf!=1 || (pivotSize < 0 && pivotSize >= lines));


    printf("Choose the column index of the pivot (0-%d): ", columns-1);
    do{
        checkscanf=scanf("%d", &pivotColumn);
        emptybuffer();
        if(checkscanf!=1 || (pivotSize < 0 && pivotSize >= columns)) { //this part avoids bugs from scanf inputs
            printf("Please enter a valid entry (between 0 and %d).\n", columns-1); 
        }
    }while(checkscanf!=1 || (pivotSize < 0 && pivotSize >= columns));

    printf("Choose the direction to rotate the slots:\nr: right (clockwise)          l: left (anticlockwise)\n");
        do{
        checkscanf=scanf(" %c", &pivotDirection);
        emptybuffer();
        if(checkscanf!=1 || (pivotDirection != 'r' && pivotDirection != 'l')) { //this part avoids bugs from scanf inputs
            printf("Please enter a valid entry ('r' or 'l').\n"); 
        }
    }while(checkscanf!=1 || (pivotDirection != 'r' && pivotDirection != 'l'));

    if (pivotSize == 3 || pivotSize == 5) {
        // Calculate the boundaries of the pivot square
        int pivotStartRow = pivotRow - pivotSize / 2;
        int pivotEndRow = pivotStartRow + pivotSize;
        int pivotStartColumn = pivotColumn - pivotSize / 2;
        int pivotEndColumn = pivotStartColumn + pivotSize;

        if (pivotDirection == 'r') {
            // Rotate the pieces outside the pivot square to the right
            for (int i = 0; i < lines; i++) {
                for (int j = 0; j < columns; j++) {
                    if ((i < pivotStartRow || i >= pivotEndRow) || (j < pivotStartColumn || j >= pivotEndColumn)) {
                        // Calculate the new coordinates after rotation
                        int newRow = pivotRow + (j - pivotColumn);
                        int newColumn = pivotColumn - (i - pivotRow);

                        // Check if the new coordinates are within the bounds of the board
                        if (newRow >= 0 && newRow < lines && newColumn >= 0 && newColumn < columns) {
                            // Move the piece to the new coordinates
                            tab[newRow][newColumn] = tab[i][j];
                            // Clear the original position
                            tab[i][j] = ' ';
                        }
                    }
                }
            }
        } else if (pivotDirection == 'l') {
            // Rotate the pieces outside the pivot square to the left
            for (int i = 0; i < lines; i++) {
                for (int j = 0; j < columns; j++) {
                    if ((i < pivotStartRow || i >= pivotEndRow) || (j < pivotStartColumn || j >= pivotEndColumn)) {
                        // Calculate the new coordinates after rotation
                        int newRow = pivotRow - (j - pivotColumn);
                        int newColumn = pivotColumn + (i - pivotRow);

                        // Check if the new coordinates are within the bounds of the board
                        if (newRow >= 0 && newRow < lines && newColumn >= 0 && newColumn < columns) {
                            // Move the piece to the new coordinates
                            tab[newRow][newColumn] = tab[i][j];
                            // Clear the original position
                            tab[i][j] = ' ';
                        }
                    }
                }
            }
        }
    }
    return pivotSize;
}