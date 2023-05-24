#include "header.h"


int choice(int round, int lines, int columns, char **tab){ 
    int column;
    if(round%2!=0){
        do{
            printf("\nIt's player 1's turn ! (\033[31mx\033[0m)\nwhich column are you choosing ?\n");
            scanf(" %d",&column);
            emptybuffer();
            column-=1; //mismatch btw array index and display (range 0-6 and range 1-7)
        }while((column<0 || column>=columns) || tab[0][column]!=' ');
        tab[0][column]='x';
    }
    if(round%2==0){
        do{
            printf("\nIt's player 1's turn ! (\033[36mo\033[0m)\nwhich column are you choosing ?\n");
            scanf(" %d",&column);
            emptybuffer();
            column-=1;
        }while((column<0 || column>=columns) || tab[0][column]!=' ');
        tab[0][column]='o';
    }
    printf("Do you want to save the game ? (y/n) : ");
    char saveChoice;
    scanf(" %c", &saveChoice);

    if (saveChoice == 'y'){
        saveGame(round, lines, columns, tab);
        printf("Game saved. Exiting...\n");
        exit(0);
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

void pivotBoard(int lines, int columns, char** tab) {
    int pivotSize;
    int pivotRow, pivotColumn;
    char pivotDirection;
    int i, j;

    printf("\nDo you want to pivot the board?\n");
    printf("Choose the size of the pivot (3 or 5): ");
    scanf("%d", &pivotSize);

    printf("Choose the row index of the pivot (0-%d): ", lines - 1);
    scanf("%d", &pivotRow);

    printf("Choose the column index of the pivot (0-%d): ", columns - 1);
    scanf("%d", &pivotColumn);

    printf("Choose the direction to rotate the pieces:\n");
    printf("Enter 'r' for right or 'l' for left: ");
    scanf(" %c", &pivotDirection);

    if (pivotSize == 3 || pivotSize == 5) {
        // Calculate the boundaries of the pivot square
        int pivotStartRow = pivotRow - pivotSize / 2;
        int pivotEndRow = pivotStartRow + pivotSize;
        int pivotStartColumn = pivotColumn - pivotSize / 2;
        int pivotEndColumn = pivotStartColumn + pivotSize;

        if (pivotDirection == 'r') {
            // Rotate the pieces outside the pivot square to the right
            for (i = 0; i < lines; i++) {
                for (j = 0; j < columns; j++) {
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
            for (i = 0; i < lines; i++) {
                for (j = 0; j < columns; j++) {
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
        } else {
            printf("Invalid pivot direction. Board not rotated.\n");
        }
    } else {
        printf("Invalid pivot size. Board not rotated.\n");
    }
}
