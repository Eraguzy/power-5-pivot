#include "header.h"

void emptybuffer(){ //empties buffer for scanfs
    int c;
    while((c=getchar())!='\n' && c!=EOF){}
}