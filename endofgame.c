#include "header.h"


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