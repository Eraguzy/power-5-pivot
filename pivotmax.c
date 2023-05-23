#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 10
#define MAX_INPUT_SIZE 10
#define WINNING_CONDITION 5
#define PIVOT_ROTATION_INTERVAL 3

bool isValidInput(int row, int col) {
    return row >= 0 && row < SIZE && col >= 0 && col < SIZE;
}

void rotatePieces(char board[SIZE][SIZE], int pivotRow, int pivotCol, int pivotSize, char direction) {
    int i, j;
    char tempBoard[SIZE][SIZE];

    // Copier le plateau dans une matrice temporaire
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            tempBoard[i][j] = board[i][j];
        }
    }

    // Vérifier et mettre à jour les pièces dans le rayon du pivot
    for (i = pivotRow - pivotSize / 2; i <= pivotRow + pivotSize / 2; i++) {
        for (j = pivotCol - pivotSize / 2; j <= pivotCol + pivotSize / 2; j++) {
            if (isValidInput(i, j)) {
                if (direction == 'D') {
                    board[i][j] = tempBoard[j][pivotRow - i + pivotCol];
                } else if (direction == 'G') {
                    board[i][j] = tempBoard[pivotCol - j + pivotRow][i];
                }
            }
        }
    }
}

void printBoard(char board[SIZE][SIZE]) {
    int i, j;

    printf("Plateau de jeu :\n");

    // Afficher les indices de colonnes
    printf("  ");
    for (j = 0; j < SIZE; j++) {
        printf("%2d ", j);
    }
    printf("\n");

    for (i = 0; i < SIZE; i++) {
        // Afficher l'indice de ligne
        printf("%2d ", i);

        for (j = 0; j < SIZE; j++) {
            char symbol;
            if (board[i][j] == ' ') {
                symbol = '+';
            } else {
                symbol = board[i][j];
            }
            printf("%2c ", symbol);
        }
        printf("\n");
    }
}

bool checkVictory(char board[SIZE][SIZE], int row, int col, char playerSymbol) {
    int count;

    // Vérifier l'horizontale
    count = 0;
    for (int i = col - WINNING_CONDITION + 1; i <= col; i++) {
        if (i < 0 || i >= SIZE || board[row][i] != playerSymbol) {
            count = 0;
        } else {
            count++;
        }
        if (count == WINNING_CONDITION) {
            return true;
        }
    }

    // Vérifier la verticale
    count = 0;
    for (int i = row - WINNING_CONDITION + 1; i <= row; i++) {
        if (i < 0 || i >= SIZE || board[i][col] != playerSymbol) {
            count = 0;
        } else {
            count++;
        }
        if (count == WINNING_CONDITION) {
            return true;
        }
    }

    // Vérifier la diagonale (haut gauche - bas droite)
    count = 0;
    for (int i = -WINNING_CONDITION + 1; i <= 0; i++) {
        int r = row + i;
        int c = col + i;
        if (r < 0 || r >= SIZE || c < 0 || c >= SIZE || board[r][c] != playerSymbol) {
            count = 0;
        } else {
            count++;
        }
        if (count == WINNING_CONDITION) {
            return true;
        }
    }

    // Vérifier la diagonale (haut droite - bas gauche)
    count = 0;
    for (int i = -WINNING_CONDITION + 1; i <= 0; i++) {
        int r = row + i;
        int c = col - i;
        if (r < 0 || r >= SIZE || c < 0 || c >= SIZE || board[r][c] != playerSymbol) {
            count = 0;
        } else {
            count++;
        }
        if (count == WINNING_CONDITION) {
            return true;
        }
    }

    return false;
}

int main() {
    char board[SIZE][SIZE];

    // Initialiser le plateau avec des espaces
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = ' ';
        }
    }

    int pivotSize;
    char input[MAX_INPUT_SIZE];
    int player = 1;
    int turnCount = 0;

    // Afficher le plateau vide
    printf("Plateau de jeu (vide) :\n");
    printBoard(board);

    // Remplir le plateau jusqu'à ce que l'utilisateur entre "stop"
    printf("Remplissez le plateau (entrez 'stop' pour terminer):\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            scanf("%s", input);
            if (strcmp(input, "stop") == 0) {
                break;
            }
            int row, col;
            scanf(input, "%d %d", &row, &col);
            if (!isValidInput(row, col)) {
                printf("Coordonnées invalides. Réessayez.\n");
                j--;
                continue;
            }
            if (board[row][col] != ' ') {
                printf("La case est déjà occupée. Réessayez.\n");
                j--;
                continue;
            }
            board[row][col] = player == 1 ? 'X' : 'O';

            // Afficher le plateau après chaque remplissage
            printf("Plateau de jeu :\n");
            printBoard(board);
        }
        if (strcmp(input, "stop") == 0) {
            break;
        }
    }

    // Demander à l'utilisateur s'il souhaite un pivot de 3x3 ou 5x5
    do {
        printf("Choisissez la taille du pivot (3 pour 3x3, 5 pour 5x5) : ");
        scanf("%d", &pivotSize);
    } while (pivotSize != 3 && pivotSize != 5);

    // Boucle principale du jeu
    while (true) {
        // Vérifier si le nombre de tours est un multiple de PIVOT_ROTATION_INTERVAL pour permettre la rotation
        bool canRotate = turnCount % PIVOT_ROTATION_INTERVAL == 0;

        // Demander à l'utilisateur de choisir le pivot
        int pivotRow, pivotCol;
        do {
            printf("Choisissez la position du pivot (ligne colonne) : ");
            scanf("%d %d", &pivotRow, &pivotCol);
        } while (!isValidInput(pivotRow, pivotCol) || board[pivotRow][pivotCol] == ' ');

        // Vérifier si le pivot est dans les limites du plateau
        if (pivotRow - pivotSize / 2 < 0 || pivotRow + pivotSize / 2 >= SIZE ||
            pivotCol - pivotSize / 2 < 0 || pivotCol + pivotSize / 2 >= SIZE) {
            printf("Le pivot est en dehors des limites du plateau.\n");
            continue;
        }

        // Demander à l'utilisateur de choisir le sens de rotation
        char direction;
        do {
            printf("Choisissez le sens de rotation (D pour droite, G pour gauche) : ");
            scanf(" %c", &direction);
        } while (direction != 'D' && direction != 'G');

        // Effectuer la rotation si possible
        if (canRotate) {
            rotatePieces(board, pivotRow, pivotCol, pivotSize, direction);
        } else {
            printf("La rotation n'est pas autorisée à ce tour.\n");
        }

        // Afficher le plateau mis à jour
        printf("Plateau de jeu après rotation :\n");
        printBoard(board);

        // Vérifier s'il y a une victoire
        if (checkVictory(board, pivotRow, pivotCol, player == 1 ? 'X' : 'O')) {
            printf("Le joueur %d a gagné !\n", player);
            break;
        }

        // Passer au prochain joueur
        player = player == 1 ? 2 : 1;
        turnCount++;
    }

    return 0;
}
