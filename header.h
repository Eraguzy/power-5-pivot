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
    int notfull(int lines, int columns, char ** tab);
    int align4(int n, int lines, int columns, char **tab);
    int loadGame(int lines, int columns, char** tab);
    void saveGame(int lines, int columns, char** tab, int round);
    int choice(int round, int lines, int columns, char **tab);
    void fill(int lines, int columns, char** tab, int column);

    void emptybuffer(void);
#endif