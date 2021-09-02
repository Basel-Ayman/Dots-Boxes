#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <winbase.h>
#include <stdbool.h>
#define MAX 256

typedef struct{
    char name[MAX];
    int score;
    int moves;
}player;

int main(){

    int i,j,boxes,index;
    print_menu();
    menu_choices();
    boxes=start_game();
    index=4*boxes+1;
    char color[index][index];
    for(i=0;i<index;i++){
        for(j=0;j<index;j++){
            color[i][j]='w';
        }
    }

    return 0;
}
