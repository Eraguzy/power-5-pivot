#include "header.h"

void saveGame(int lines, int columns, int round, int align, char withpivot, char** tab) {
    FILE* file = fopen("savegame.txt", "w");  // opens the save file (write)

    fprintf(file, " %d %d %d %d %c \n", lines, columns, align, round, withpivot);

    for (int i = 0; i < lines; i++) { // writes the array
        for (int j = 0; j < columns; j++) {
            fprintf(file, "%c", tab[i][j]);
        }
    }

    fclose(file);
    printf("File saved. You will be able to load the game later.\n");
    exit(0);
}

void loadGame(int* lines, int* columns, int* round, int* align, char* withpivot, char*** tab) {
    FILE* file = fopen("savegame.txt", "r");  // ouvre le fichier de sauvegarde en lecture
    if (file == NULL) {
        printf("No saved game found. Please put your save file in the right directory and reload the game.\n");
        exit(0);
    }

    fscanf(file, " %d %d %d %d %c \n", lines, columns, align, round, withpivot);

    *tab = malloc(sizeof(char*) * (*lines));  // alloue de l'espace pour le tableau
    if (*tab == NULL) {
        printf("malloc error\n");
        exit(0);
    }

    for (int j = 0; j < *lines; j++) {
        (*tab)[j] = malloc(sizeof(char) * (*columns));
        if ((*tab)[j] == NULL) {
            printf("malloc error\n");
            exit(0);
        }
    }

    for (int i = 0; i < *lines; i++) {
        for (int j = 0; j < *columns; j++) {
            fscanf(file, "%c", &((*tab)[i][j]));
        }
    }

    fclose(file);

    printf("\nPrevious game loaded.\nSize : %dx%d.\nWin condition : %d slots.\n",*columns, *lines, *align);
}