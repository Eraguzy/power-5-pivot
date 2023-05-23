#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

#define LA 10 // largeur de cases
#define HA 8 // hauteur de cases

void displayer(int ha, int la, char **tab) {
    // Fonction pour afficher le tableau
    printf("╔═══");
    for (int i=0; i<la-1; i++){
        printf("╦═══");              //first line
    }
    printf("╗\n");


    for (int i=0; i<ha-1; i++){
        for (int j=0; j<la; j++){    //loop for tab values + colors (between lines)
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
        for (int i=0; i<la-1; i++){
            printf("╬═══");              //loop for middle width lines
        }
        printf("╣\n");
    }

    for (int j=0; j<la; j++){    //loop for tab values + colors (between lines) (last line)
        if(tab[ha-1][j]=='x'){
            printf("║ \033[31m%c\033[0m ",tab[ha-1][j]); //red
        }
        else if(tab[ha-1][j]=='+'){
            printf("║\033[40m %c \033[0m",tab[ha-1][j]); //red
        }
        else{
            printf("║ \033[36m%c\033[0m ",tab[ha-1][j]); //light blue
        }
    }
    printf("║\n");

    printf("╚═══");
    for (int i=0; i<la-1; i++){
        printf("╩═══");              //last line
    }
    printf("╝\n");

    int count=0;
    for (int i=0; i<la; i++){
        count++;
        printf("| %2d",count);
    }
    printf("|\n");           //numéro des colonnes
}
int endgame(char cas, int ha, int la, char** tab) {
    // Fonction pour détecter la fin du jeu et afficher le gagnant
    displayer(ha, la, tab);
    if(cas=='x'){
        printf("joueur 1 (\033[31mx\033[0m) a gagné !\n");
    }
    else{
        printf("joueur 2 (\033[36mo\033[0m) a gagné !\n");
    }
    return 0;
}

int notfull(int ha, int la, char ** tab) {
    for (int j=0; j<la; j++){
        if(tab[0][j]==32){
            return 1;
        }
    }
    displayer(ha, la, tab);
    printf("Egalité !\n");
    return 0;
}


int align4(int n, int ha, int la, char **tab) {
    int count = 0;

    for (int i = 0; i < ha; i++) {
        for (int j = 0; j < la; j++) {
            if (tab[i][j] != ' ') {
                count = 0;

                // Vérification horizontale
                for (int k = 0; k < n && j + k < la; k++) {
                    if (tab[i][j] == tab[i][j + k]) {
                        count++;
                    }
                }
                if (count == n) {
                    endgame(tab[i][j], ha, la, tab);
                    return 0;
                }

                count = 0;

                // Vérification verticale
                for (int k = 0; k < n && i + k < ha; k++) {
                    if (tab[i][j] == tab[i + k][j]) {
                        count++;
                    }
                }
                if (count == n) {
                    endgame(tab[i][j], ha, la, tab);
                    return 0;
                }

                count = 0;

                // Vérification diagonale bas droite
                for (int k = 0; k < n && i + k < ha && j + k < la; k++) {
                    if (tab[i][j] == tab[i + k][j + k]) {
                        count++;
                    }
                }
                if (count == n) {
                    endgame(tab[i][j], ha, la, tab);
                    return 0;
                }

                count = 0;

                // Vérification diagonale haut droite
                for (int k = 0; k < n && i - k >= 0 && j + k < la; k++) {
                    if (tab[i][j] == tab[i - k][j + k]) {
                        count++;
                    }
                }
                if (count == n) {
                    endgame(tab[i][j], ha, la, tab);
                    return 0;
                }
            }
        }
    }

    return 1;
}

int choix(int tour, int ha, int la, char **tab) {
    int column;
    if (tour % 2 != 0) {
        do {
            printf("\nAu tour de joueur 1 (\033[31mx\033[0m)\nquelle colonne joues-tu ?\n");
            scanf(" %d", &column);
            column -= 1; // mismatch btw array index and display (range 0-6 and range 1-7)
        } while ((column < 0 || column >= la) || tab[0][column] != ' ');
        tab[0][column] = 'x';
    }
    if (tour % 2 == 0) {
        do {
            printf("\nAu tour de joueur 2 (\033[36mo\033[0m)\nquelle colonne joues-tu ?\n");
            scanf(" %d", &column);
            column -= 1;
            int pivotSize, direction;
            printf("\nChoisissez la taille du pivot (3 ou 5) : ");
            scanf("%d", &pivotSize);
            printf("Choisissez la direction du pivot (1 pour gauche, 2 pour droite) : ");
            scanf("%d", &direction);

            // Appliquer le pivot à gauche
            if (direction == 1) {
                for (int i = 0; i < pivotSize; i++) {
                    for (int j = 0; j < ha; j++) {
                        char temp = tab[j][column - i];
                        tab[j][column - i] = tab[j][column];
                        tab[j][column] = temp;
                    }
                }
            }
        } while ((column < 0 || column >= la) || tab[0][column] != ' ');
        tab[0][column] = 'o';
    }

    // Demande de pivot après chaque fois que deux pions sont posés
    if (tour % 2 == 0) {
        int pivotSize, direction;
        printf("\nChoisissez la taille du pivot (3 ou 5) : ");
        scanf("%d", &pivotSize);
        printf("Choisissez la direction du pivot (1 pour gauche, 2 pour droite) : ");
        scanf("%d", &direction);

        // Appliquer le pivot à gauche
        if (direction == 1) {
            for (int i = 0; i < pivotSize; i++) {
                for (int j = 0; j < ha; j++) {
                    char temp = tab[j][column - i];
                    tab[j][column - i] = tab[j][column];
                    tab[j][column] = temp;
                }
            }
        }
            // Appliquer le pivot à droite
        else if (direction == 2) {
            for (int i = 0; i < pivotSize; i++) {
                for (int j = 0; j < ha; j++) {
                    char temp = tab[j][column + i];
                    tab[j][column + i] = tab[j][column];
                    tab[j][column] = temp;
                }
            }
        }
    }

    return column;
}


void fill(int ha, int la, char** tab, int column) {
    // Fonction pour appliquer la gravité sur UNE COLONNE UNIQUEMENT
    int buffer, cond;
    do{
        cond=0;
        for (int i=0; i<ha-1; i++){
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
    int tour=1; //permet d'alterner le joueur
    int la, ha; // Variables pour la largeur et la hauteur du plateau
    char nogravity; // if nogravity = y, then there will be the 4 nogravity slots
    printf("\nBienvenue à \033[31mCY-Connect\033[0m ! Commençons par choisir les paramètres du jeu. \n\nPetite particularité dans ce programme : il y la possibilité de jouer avec des cases \033[35msans gravité\033[0m (symbolisées par '\033[40m + \033[0m'). \nSouhaites-tu jouer avec ces cases ?\ny: oui          n: non\n");
    do{ //play with or without nograv slots
        scanf(" %c", &nogravity);
        if (nogravity != 'y' && nogravity != 'n') {
            printf("Merci d'entrer une valeur valide ('y' ou 'n').\n");
        }
    }while(nogravity!='y' && nogravity!='n');


    printf("\nTu peux choisir le nombre de \033[35mcases à aligner\033[0m pour être gagnant :\n");
    scanf("%d",&n);


    printf("\nLa largeur doit être comprise entre \033[31m8\033[0m et \033[31m%d\033[0m.", LA);
    do{
        printf("\nChoisis la \033[35mlargeur\033[0m du plateau : \n");
        scanf("%d", &la);
    } while(la < 8 || la > LA);

    printf("\nLa hauteur doit être comprise entre \033[31m6\033[0m et \033[31m%d\033[0m.", HA);
    do{
        printf("\nChoisis la \033[35mhauteur\033[0m du plateau : \n");
        scanf("%d", &ha);
    } while(ha < 6 || ha > HA);


#if 0
    char* addr=malloc(sizeof(char)*ha*la);
    char (*tab)[la] = (char (*)[la])addr;
#endif

    char** tab = malloc(sizeof(char*)*ha);     //creates the array for the game

    if (tab == NULL) {
        printf("malloc error\n");
        return 0;
    }

    for (int j=0; j<ha; j++){
        tab[j] = malloc(sizeof(char)*la);
        if (tab == NULL) {
            printf("malloc error\n");
            return 0;
        }
    }

    for (int i=0; i<ha; i++){
        for (int j=0; j<la; j++){
            tab[i][j]=' ';          //initializes the entire array with spaces, then puts the no-gravity slots
        }
    }

    if (nogravity == 'y'){
        tab[0][0]='+';
        tab[0][la-1]='+';
        tab[ha-1][0]='+';
        tab[ha-1][la-1]='+';
    }

    printf("\n\n\n\nC'est parti ! La partie va commencer. Amuse-toi bien ;)\n\n\n\n");
    sleep(3);

    do{
        displayer(ha, la, tab);
        fill(ha, la, tab, choix( tour,  ha,  la, *tab));
        tour++;
    }while(align4(n, ha, la, tab) && notfull(ha, la, tab)); //verifies the two conditions to end the game

    return 0;
}