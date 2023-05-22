#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

#define LA 10 //largeur de cases
#define HA 8 //hauteur de cases


void displayer(int ha, int la, char **tab){ //fix esthétique ═ ║ ═ ╔ ╦ ╗ ╠ ╬ ╣ ╚ ╩ ╝
    printf("╔═══");
    for (int i=0; i<la-1; i++){
        printf("╦═══");              //first line
    }
    printf("╗\n");


    for (int i=0; i<ha-1; i++){
        for (int j=0; j<la; j++){    //loop for tab values + colors (between lines)
            if(tab[i][j]=='x'){
                printf("║ \033[31m%c\033[0m ",tab[i][j]); //light blue
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
            printf("║ \033[31m%c\033[0m ",tab[ha-1][j]); //light blue
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

int endgame(char cas, int ha, int la, char** tab){
    ///fonction temporaire : par la suite, cas par cas pour surligner cases gagnantes
    displayer(ha, la, tab);
    if(cas=='x'){
        printf("joueur 1 (\033[31mx\033[0m) a gagné !\n");
    }
    else{
        printf("joueur 2 (\033[36mo\033[0m) a gagné !\n");
    }
    return 0;
}

int notfull(int ha, int la, char ** tab){ //checks every round if the array is fully filled
    for (int i=0; i<ha; i++){
        for (int j=0; j<la; j++){
            if(tab[i][j]==32){
                return 1;
            }
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

int choix(int tour, int ha, int la, char **tab){ //takes player's column choice (for x's turn or o's turn)
    int column;
    if(tour%2!=0){
        do{
            printf("\nAu tour de joueur 1 (\033[31mx\033[0m)\nquelle colonne joues-tu ?\n");
            scanf(" %d",&column);
            column-=1; //mismatch btw array index and display (range 0-6 and range 1-7)
        }while((column<0 || column>=la) || tab[0][column]!=' ');
        tab[0][column]='x';
    }
    if(tour%2==0){
        do{
            printf("\nAu tour de joueur 2 (\033[36mo\033[0m)\nquelle colonne joues-tu ?\n");
            scanf(" %d",&column);
            column-=1;
        }while((column<0 || column>=la) || tab[0][column]!=' ');
        tab[0][column]='o';
    }
    return column;
}

void fill(int ha, int la, char** tab, int column){ //applies gravity on ONE COLUMN ONLY
    int buffer, cond;
    do{
        cond=0;
        for (int i=0; i<ha-1; i++){
            if(tab[i+1][column]==' ' && tab[i][column]!=' '){
                cond=1;
                buffer=tab[i+1][column];
                tab[i+1][column]=tab[i][column];
                tab[i][column]=buffer;
            }
        }
    } while(cond);
}

int main(){
    printf("Choisis le nombre de cases à aligner pour être gagnant :\n");
    int n;

    scanf("%d",&n);
    int tour=1; //permet d'alterner le joueur

    int la, ha; // Variables pour la largeur et la hauteur du plateau

    printf("\nLa largeur doit être comprise entre 8 et %d.", LA);
    do{
        printf("\nChoisissez la largeur du plateau : \n");
        scanf("%d", &la);
    } while(la < 8 || la > LA);

    printf("\nLa hauteur doit être comprise entre 6 et %d.", HA);
    do{
        printf("\nChoisissez la hauteur du plateau : \n");
        scanf("%d", &ha);
    } while(ha < 6 || ha > HA);

    #if 0
    char* addr=malloc(sizeof(char)*ha*la);
    char (*tab)[la] = (char (*)[la])addr;
    #endif

    char** tab = malloc(sizeof(char*)*ha);

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
            tab[i][j]=' '; //spacebar in ascii
        }
    }

    do{
        displayer(ha, la, tab);
        fill(ha, la, tab, choix(tour, ha, la ,tab));
        tour++;
        printf("tour suivant\n");
    }while(align4(n, ha, la, tab) && notfull(ha, la, tab)); //verifies the two conditions to end the game

    return 0;
}