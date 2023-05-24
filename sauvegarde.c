#include "header.h"

int loadGame(int lines, int columns, char** tab) {
    FILE* file = fopen("savegame.txt", "r");  // Ouvre le fichier de sauvegarde en lecture
    if (file == NULL) {
        printf("No saved game found.\n");
        return 0;  // Aucune partie sauvegardée n'a été trouvée
    }

    // Lit le tableau à partir du fichier
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            fscanf(file, " %c", &tab[i][j]);
        }
    }

    fclose(file);  // Ferme le fichier

    printf("Previous game loaded.\n");
    return 1;  // Partie chargée avec succès
}

void saveGame(int lines, int columns, char** tab, int round) {
    FILE* file = fopen("savegame.txt", "w");  // Ouvre le fichier de sauvegarde en écriture
}
    // Enregistre le tableau dans le fichier.
