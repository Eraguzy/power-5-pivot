//libraries
#ifndef def
    #define def
    #include<stdio.h>
    #include<stdlib.h>
    #include<unistd.h>
    #include<time.h>

    //constants
    #define ROWO 10 //box width
    #define COLO 8 //box height

    //functions
    void displayer(int lines, int columns, char **tab);

    int endgame(char slot, int lines, int columns, char** tab);
    int notfull(int lines, int columns, char** tab);
    int align(int n, int lines, int columns, char** tab);

    void loadGame(int* lines, int* columns, int* round, int* align, char*** tab);
    void saveGame(int lines, int columns, int round, int align, char** tab);

    void pivotBoard(int lines, int columns, char** tab);
    int choice(int round, int lines, int columns, int n, char **tab);
    void fill(int lines, int columns, char** tab, int column);

    void emptybuffer(void);

    void parameters(int* lines,int* columns,int* round,int* n, char*** tab);
#endif