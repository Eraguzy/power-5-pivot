#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

#define LA 10 //largeur de cases
#define HA 10 //hauteur de cases

void displayer(char tab[HA][LA]){ //fix esthétique ═ ║ ═ ╔ ╦ ╗ ╠ ╬ ╣ ╚ ╩ ╝
    printf("╔═══");
    for (int i=0; i<LA-1; i++){
        printf("╦═══");              //first line
    }
    printf("╗\n");


    for (int i=0; i<HA-1; i++){
        for (int j=0; j<LA; j++){    //loop for tab values + colors (between lines)
            if(tab[i][j]=='x'){
                printf("║ \033[31m%c\033[0m ",tab[i][j]); //light blue
            }
            else{ 
                printf("║ \033[36m%c\033[0m ",tab[i][j]); //light blue
            }
        }
        printf("║\n");

        printf("╠═══");
        for (int i=0; i<LA-1; i++){
            printf("╬═══");              //loop for middle width lines
        }
        printf("╣\n");
    }

    for (int j=0; j<LA; j++){    //loop for tab values + colors (between lines) (last line)
        if(tab[HA-1][j]=='x'){
            printf("║ \033[31m%c\033[0m ",tab[HA-1][j]); //light blue
        }
        else{
            printf("║ \033[36m%c\033[0m ",tab[HA-1][j]); //light blue
        }
    }
    printf("║\n");

    printf("╚═══");
    for (int i=0; i<LA-1; i++){
        printf("╩═══");              //last line
    }
    printf("╝\n");

    int count=0; 
    for (int i=0; i<LA; i++){
        count++;
        printf("| %2d",count);
    }
    printf("|\n");           //numéro des colonnes
}

int endgame(char cas, char tab[HA][LA]){
    ///fonction temporaire : par la suite, cas par cas pour surligner cases gagnantes
    displayer(tab);
    if(cas=='x'){
        printf("joueur 1 (\033[31mx\033[0m) a gagné !\n");
    }
    else{
        printf("joueur 2 (\033[36mo\033[0m) a gagné !\n");
    }
    return 0;
}

int notfull(char tab[HA][LA]){ //checks every round if the array is fully filled
    for (int i=0; i<HA; i++){
        for (int j=0; j<LA; j++){
            if(tab[i][j]==32){
                return 1;
            }
        }
    }
    displayer(tab);
    printf("Egalité !\n");
    return 0;
}

int align4(int n, char tab[HA][LA]){
    int count=0; //compteur qui met fin au prog en cas de condition remplie 4 fois ou + : doit être remis à zéro à chaque nouvelle vérif pour éviter accumulation de comptages entre différentes boucles
    for (int i=0; i<HA; i++){
        for (int j=0; j<LA; j++){
            if((tab[i][j]!=' ') && (j<LA-n+1 || i<HA-n+1)){ //verif seg fault et ne vérif pas la cond de victoire pour les espaces //fix
                count=0;
                for(int k=0;k<n;k++){
                    if(tab[i][j]==tab[i][j+k]){ //horizontal
                        count++;
                    }
                }
                if(count==n){ //fin du jeu si count rempli
                    endgame(tab[i][j], tab);
                    return 0;
                }
                count=0;
                for(int k=0;k<n;k++){
                    if(tab[i][j]==tab[i+k][j]){ //vertical
                        count++;
                    }
                }
                if(count==n){ //fin du jeu si count rempli
                    endgame(tab[i][j], tab);
                    return 0;
                }
                count=0;
                for(int k=0;k<n;k++){
                    if(tab[i][j]==tab[i+k][j+k]){ //diago bas droite
                        count++;
                    }
                }
                if(count==n){ //fin du jeu si count rempli
                    endgame(tab[i][j], tab);
                    return 0;
                }
                count=0;
                for(int k=0;k<n;k++){
                    if(tab[i][j]==tab[i-k][j+k]){ // diago haut droite
                        count++;
                    }
                }
                if(count==n){ //fin du jeu si count rempli
                    endgame(tab[i][j], tab);
                    return 0;
                }
            }
        }
    }
    return 1;
}

int choix(int tour, char tab[HA][LA]){ //takes player's column choice (for x's turn or o's turn)
    int column;
    if(tour%2!=0){
        do{
            printf("\nAu tour de joueur 1 (\033[31mx\033[0m)\nquelle colonne joues-tu ?\n");
            scanf(" %d",&column);
            column-=1; //mismatch btw array index and display (range 0-6 and range 1-7)
        }while((column<0 || column>=LA) || tab[0][column]!=' ');
        tab[0][column]='x';
    }
    if(tour%2==0){
        do{
            printf("\nAu tour de joueur 2 (\033[36mo\033[0m)\nquelle colonne joues-tu ?\n");
            scanf(" %d",&column);
            column-=1;
        }while((column<0 || column>=LA) || tab[0][column]!=' ');
        tab[0][column]='o';
    }
    return column;
}

void fill(char tab[HA][LA], int column){ //applies gravity on ONE COLUMN ONLY
    int buffer, cond;
    do{
        cond=0;
        for (int i=0; i<HA; i++){
            if(tab[i+1][column]==32 && tab[i][column]!=32){
                cond=1;
                buffer=tab[i+1][column];
                tab[i+1][column]=tab[i][column];
                tab[i][column]=buffer;
            }
        }
    }while(cond);
}

int main(){
    int n;
    printf("Paramètres du plateau de jeu :\nHauteur : %d cases\nLargeur : %d cases\n\n", HA, LA);
    printf("Choisis le nombre de cases à aligner pour être gagnant :\n");
    scanf("%d",&n);
    char tab[HA][LA];
    int tour=1; //permet d'alterner le joueur
    int count=0;
    for (int i=0; i<HA; i++){
        for (int j=0; j<LA; j++){
            tab[i][j]=32; //espace en ascii
        }
    }
    do{
        displayer(tab);
        fill(tab, choix(tour, tab));
        tour++;
    }while(align4(n, tab) && notfull(tab));
    return 0;
}