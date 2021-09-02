#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <winbase.h>
#include <stdbool.h>
#include <time.h>
#define MAX 30

typedef struct{
    char name[MAX] ;
    int score;
    int moves;
}player;

typedef struct{
    player player1;
    player player2;
    int index;
    int turn;
    int leftMoves;
    time_t startTime;
    time_t endTime;
    int boxes;
    int counter;
    int flag;
    int undoFlag;
    int undoGrid[60][8];
    int grid[100][100];
    char colors[100][100];
}load;

void print_menu(){
    colour();
    yellow();
    printf("\t\t\t\t----------------------------------\n");
    printf("\n");
    printf("\t\t\t\t>>>>>>>>>> DOTS &\ BOXES <<<<<<<<<<\n");
    printf("\n");
    yellow();
    printf("\t\t\t\t----------------------------------\n");
    printf("\n\n");
    magenta();
    printf("\t\t\t\t   >>>>>WELCOME TO OUR GAME<<<<<\n\n");
    reset();
    printf("\t\t\t\t\t    1-Start Game\n");
    printf("\t\t\t\t\t    2-Load Game\n");
    printf("\t\t\t\t\t    3-Top 10 Legends\n");
    printf("\t\t\t\t\t    4-Exit Game\n");

}

void menu_choices(){
    char choice;
    int fileNo;
    load loadM;
    while(choice!='1'|| choice!='2'|| choice!='3'|| choice!='4'){
        scanf("%c",&choice);
        switch(choice){
            case '1':
                start_game();
                break;
            case '2':
                printf("Choose the game you want to load... \n1- Game 1\n2- Game 2\n3- Game 3\n");
                scanf("%d", &fileNo);
                //loadM = load_game(fileNo);
                break;
            case '3':
                top_ten();
                break;
            case '4':
                break;
        }
    }
}
int start_game(){
    system("cls");
    colour();
    magenta();
    printf("\n\n\t\t\t\t  >>>>>choose your level<<<<<\n\n");
    reset();
    printf("\t\t\t\t\t 1- Beginner (2x2)\n");
    printf("\t\t\t\t\t 2- Expert (5x5)\n");
    char choice;
    int boxes;
    while(choice!='1' || choice!='2'){
        scanf("%c",&choice);
        switch(choice){
            case '1':
                boxes=2;
                players(boxes);
                break;
            case '2':
                boxes=5;
                players(boxes);
                break;
        }
    }
    return boxes;
}

void players(int boxes){
    system("cls");
    colour();
    magenta();
    printf("\n\n\t\t\t\t  >>>>>choose how to play<<<<<\n\n");
    reset();
    printf("\t\t\t\t\t 1- player vs PC\n");
    printf("\t\t\t\t\t 2- player vs player\n");
    char choice;
    int index=4*boxes+1;
    while(choice!='1' || choice!='2'){
        scanf("%c",&choice);
        switch(choice){
            case '1':
                pVSpc(index, boxes);
                break;
            case '2':
                pVSp(index, boxes);
                break;
        }
    }
}

void pVSpc(int index, int boxes){
    player player1,player2;
    strcpy(player2.name,"Computer");
    system("cls");
    cyan();
    printf("Enter your name --> ");
    fgets(player1.name,MAX,stdin);
    fgets(player1.name,MAX,stdin);
    reset();
    player1.name[strlen(player1.name)-1]='\0';
    player1.moves=player1.score=player2.moves=player2.score=0;
    int pre_score1,pre_score2,R,C,left_moves,loop;
    left_moves=loop=2*(boxes*boxes+boxes);
    char color[index][index];
    int valid,counter=0,j,grid[index][index],undo_grid[2*(boxes*boxes+boxes)][8] ,inChoice, fileNo, flag=1, undoFlag=0;
    dec_grid(index,index,grid);
    time_t start=time(NULL), end=time(NULL);
    label:
    while(loop>=0){
        system("cls");
        print_info(player1,player2);
        yellow();
        printf("\n\t\t\t\t\t\tLeft Moves        %d",loop);
        printf("\n\t\t\t\t\t\t\t%d : %d", (end-start)/60, (end-start)%60);
        reset();
        printf("\n\n\n\n");
        print_grid(index,index,grid,color);
        int turn=turns(left_moves);
        if(turn==1){
            if(loop>0){
                yellow();
                printf("\n\n>>>>>");
                red();
                printf(" %s ",player1.name);
                yellow();
                printf("<<<<<\n");
                while(flag==1){
                    flag=0;
                    yellow();
                    printf("choose the number of the option you want:\n1-continue    2-save    3-main menu    4-undo    5-redo\n");
                    scanf("%d", &inChoice);
                    switch (inChoice){
                        case 1:

                            break;
                        case 2:
                            printf("Save the game in....\n1- Game 1\n2- Game 2\n3- Game 3\n");
                            scanf("%d", &fileNo);
                            save_game(index, grid, player1, player2, turn, loop, start, end, color, fileNo,boxes,undo_grid[2*(boxes*boxes+boxes)][8],counter,flag,undoFlag);
                            break;
                        case 3:
                            print_menu();
                            menu_choices();
                            break;
                        case 4:
                            while(undo_grid[counter-1][2]==2){
                                reassign(undo_grid[counter-1][0],undo_grid[counter-1][1],index,grid,color);
                                counter--;
                            }
                            while(undo_grid[counter-1][2]==1){
                                reassign(undo_grid[counter-1][0],undo_grid[counter-1][1],index,grid,color);
                                counter--;
                            }
                            loop=undo_grid[counter][3];
                            player1.moves=undo_grid[counter][4];
                            player2.moves=undo_grid[counter][5];
                            if(counter>0){
                                player1.score=undo_grid[counter-1][6];
                                player2.score=undo_grid[counter-1][7];
                            }
                            undoFlag=1;
                            flag=1;
                            goto label;
                            break;
                        case 5:
                            while(undo_grid[counter][2]==1){
                                assign_grid(undo_grid[counter][0],undo_grid[counter][1],index,grid,undo_grid[counter][2],color);
                                check_box(index,boxes,undo_grid[counter][2],grid,color);
                                counter++;
                            }
                            while(undo_grid[counter][2]==2){
                                assign_grid(undo_grid[counter][0],undo_grid[counter][1],index,grid,undo_grid[counter][2],color);
                                check_box(index,boxes,undo_grid[counter][2],grid,color);
                                counter++;
                            }
                            loop=undo_grid[counter-1][3];
                            player1.moves=undo_grid[counter-1][4];
                            player2.moves=undo_grid[counter-1][5];
                            player1.score=undo_grid[counter-1][6];
                            player2.score=undo_grid[counter-1][7];
                            undoFlag=0;
                            flag=1;
                            goto label;
                            break;
                        default:
                            printf("ERROR!");
                            flag=1;
                            break;
                    }
                }
                flag=1;
                R=scan_row();
                C=scan_col();
                valid=validity(R,C,index,grid,boxes);
                if(valid==0){
                    while(valid==0){
                        printf("\nINVALID POINT!!!\n");
                        R=scan_row();
                        C=scan_col();
                        valid=validity(R,C,index,grid,boxes);
                    }
                }
            }
            undo_grid[counter][0]=R;
            undo_grid[counter][1]=C;
            undo_grid[counter][2]=turn;
            undo_grid[counter][3]=loop;
            undo_grid[counter][4]=player1.moves;
            undo_grid[counter][5]=player2.moves;
            undo_grid[counter][6]=player1.score;
            undo_grid[counter][7]=player2.score;
            counter++;
            assign_grid(R,C,index,grid,turn,color);
            pre_score1=player1.score;
            player1.score+=check_box(index, boxes, turn, grid,color);
            if(pre_score1<player1.score){
                left_moves++;
            }
            player1.moves++;
        }else{
            if(loop>0){
                R=AI_row(index,boxes,grid);
                C=AI_column(index,boxes,grid);
                valid=validity(R,C,index,grid,boxes);
                if(valid==0){
                    while(valid==0){
                        R=pc(boxes);
                        C=pc(boxes);
                        valid=validity(R,C,index,grid,boxes);
                    }
                }
            }
            undo_grid[counter][0]=R;
            undo_grid[counter][1]=C;
            undo_grid[counter][2]=turn;
            undo_grid[counter][3]=loop;
            undo_grid[counter][4]=player1.moves;
            undo_grid[counter][5]=player2.moves;
            undo_grid[counter][6]=player1.score;
            undo_grid[counter][7]=player2.score;
            counter++;
            assign_grid(R,C,index,grid,turn,color);
            pre_score2=player2.score;
            player2.score+=check_box(index, boxes, turn, grid,color);
            if(pre_score2<player2.score){
                left_moves++;
            }
            player2.moves++;
        }

        left_moves--;
        loop--;
        end=time(NULL);
    }
    if(player1.score>player2.score){
        red();
        printf("\n%s ",player1.name);
        yellow();
        printf("WON!!");
    }else if(player2.score>player1.score){
        blue();
        printf("\n%s ",player2.name);
        yellow();
        printf("WON!!");
    }else{
        yellow();
        printf("\nTIE");
    }
    top_ten_assign(player1.name,player1.score);
    top_ten_assign(player2.name,player2.score);
}

void pVSp(int index, int boxes){
    colour();
    cyan();
    player player1,player2;
    printf("Player1 enter your name --> ");
    fgets(player1.name,MAX,stdin);
    fgets(player1.name,MAX,stdin);
    player1.name[strlen(player1.name)-1]='\0';
    printf("Player2 enter your name --> ");
    fgets(player2.name,MAX,stdin);
    player2.name[strlen(player2.name)-1]='\0';
    reset();
    player1.moves=player1.score=player2.moves=player2.score=0;
    int left_moves,loop;
    left_moves=loop=2*(boxes*boxes+boxes);
    char color[index][index];
    int i,j,valid,grid[index][index],undo_grid[2*(boxes*boxes+boxes)][8] ,inChoice,counter=0,R,C,pre_score, fileNo, flag=1, undoFlag=0;
    dec_grid(index,index,grid);
    time_t start=time(NULL) , end=time(NULL);
    label2:
    while(loop>=0){
        system("cls");
        print_info(player1,player2);
        yellow();
        printf("\n\t\t\t\t\t\tLeft Moves        %d",loop);
        printf("\n\t\t\t\t\t\t\t%d : %d", (end-start)/60, (end-start)%60);
        reset();
        printf("\n\n\n\n");
        print_grid(index,index,grid,color);
        int turn=turns(left_moves);
        if(turn==1){
            if(loop>0){
                yellow();
                printf("\n\n>>>>>");
                red();
                printf(" %s's ",player1.name);
                yellow();
                printf("turn <<<<<\n");
                while(flag==1){
                    flag=0;
                    yellow();
                    printf("choose the number of the option you want:\n1-continue    2-save    3-main menu    4-undo    5-redo\n");
                    scanf("%d", &inChoice);
                    switch (inChoice){
                        case 1:

                            break;
                        case 2:
                            printf("Save the game in....\n1- Game 1\n2- Game 2\n3- Game 3\n");
                            scanf("%d", &fileNo);
                            save_game(index, grid, player1, player2, turn, loop, start, end, color, fileNo,boxes,undo_grid[2*(boxes*boxes+boxes)][8],counter,flag,undoFlag);
                            break;
                        case 3:
                            print_menu();
                            menu_choices();
                            break;
                        case 4:
                            while(undo_grid[counter-1][2]==2){
                                reassign(undo_grid[counter-1][0],undo_grid[counter-1][1],index,grid,color);
                                counter--;
                            }
                            while(undo_grid[counter-1][2]==1){
                                reassign(undo_grid[counter-1][0],undo_grid[counter-1][1],index,grid,color);
                                counter--;
                            }
                            loop=undo_grid[counter][3];
                            player1.moves=undo_grid[counter][4];
                            player2.moves=undo_grid[counter][5];
                            if(counter>0){
                                player1.score=undo_grid[counter-1][6];
                                player2.score=undo_grid[counter-1][7];
                            }
                            undoFlag=1;
                            flag=1;
                            goto label2;
                            break;
                        case 5:
                            while(undo_grid[counter][2]==1){
                                assign_grid(undo_grid[counter][0],undo_grid[counter][1],index,grid,undo_grid[counter][2],color);
                                check_box(index,boxes,undo_grid[counter][2],grid,color);
                                counter++;
                            }
                            while(undo_grid[counter][2]==2){
                                assign_grid(undo_grid[counter][0],undo_grid[counter][1],index,grid,undo_grid[counter][2],color);
                                check_box(index,boxes,undo_grid[counter][2],grid,color);
                                counter++;
                            }
                            loop=undo_grid[counter-1][3];
                            player1.moves=undo_grid[counter-1][4];
                            player2.moves=undo_grid[counter-1][5];
                            player1.score=undo_grid[counter-1][6];
                            player2.score=undo_grid[counter-1][7];
                            undoFlag=0;
                            flag=1;
                            goto label2;
                            break;
                        default:
                            printf("ERROR!");
                            flag=1;
                            break;
                    }
                }
                flag=1;
                R=scan_row();
                C=scan_col();
                valid=validity(R,C,index,grid,boxes);
                if(valid==0){
                    while(valid==0){
                        printf("\nINVALID POINT!!!\n");
                        R=scan_row();
                        C=scan_col();
                        valid=validity(R,C,index,grid,boxes);
                    }
                }
            }
            undo_grid[counter][0]=R;
            undo_grid[counter][1]=C;
            undo_grid[counter][2]=turn;
            undo_grid[counter][3]=loop;
            undo_grid[counter][4]=player1.moves;
            undo_grid[counter][5]=player2.moves;
            undo_grid[counter][6]=player1.score;
            undo_grid[counter][7]=player2.score;
            counter++;
            assign_grid(R,C,index,grid,turn,color);
            pre_score=player1.score;
            player1.score+=check_box(index, boxes, turn, grid,color);
            if(pre_score<player1.score){
                left_moves++;
            }
            player1.moves++;
        }else{
            if(loop>0){
                yellow();
                printf("\n\n>>>>>");
                blue();
                printf(" %s's ",player2.name);
                yellow();
                printf("turn <<<<<\n");
                while(flag==1){
                    flag=0;
                    yellow();
                    printf("choose the number of the option you want:\n1-continue    2-save    3-main menu    4-undo    5-redo\n");
                    scanf("%d", &inChoice);
                    switch (inChoice){
                        case 1:

                            break;
                        case 2:
                            printf("Save the game in....\n1- Game 1\n2- Game 2\n3- Game 3\n");
                            scanf("%d", &fileNo);
                            save_game(index, grid, player1, player2, turn, loop, start, end, color, fileNo,boxes,undo_grid[2*(boxes*boxes+boxes)][8],counter,flag,undoFlag);
                            break;
                        case 3:
                            print_menu();
                            menu_choices();
                            break;
                        case 4:
                            while(undo_grid[counter-1][2]==1){
                                reassign(undo_grid[counter-1][0],undo_grid[counter-1][1],index,grid,color);
                                counter--;
                            }
                            while(undo_grid[counter-1][2]==2){
                                reassign(undo_grid[counter-1][0],undo_grid[counter-1][1],index,grid,color);
                                counter--;
                            }
                            loop=undo_grid[counter][3];
                            player1.moves=undo_grid[counter][4];
                            player2.moves=undo_grid[counter][5];
                            if(counter>0){
                                player1.score=undo_grid[counter-1][6];
                                player2.score=undo_grid[counter-1][7];
                            }
                            undoFlag=1;
                            flag=1;
                            goto label2;
                            break;
                        case 5:
                            while(undo_grid[counter][2]==2){
                                assign_grid(undo_grid[counter][0],undo_grid[counter][1],index,grid,undo_grid[counter][2],color);
                                check_box(index,boxes,undo_grid[counter][2],grid,color);
                                counter++;
                            }
                            while(undo_grid[counter][2]==1){
                                assign_grid(undo_grid[counter][0],undo_grid[counter][1],index,grid,undo_grid[counter][2],color);
                                check_box(index,boxes,undo_grid[counter][2],grid,color);
                                counter++;
                            }
                            loop=undo_grid[counter-1][3];
                            player1.moves=undo_grid[counter-1][4];
                            player2.moves=undo_grid[counter-1][5];
                            player1.score=undo_grid[counter-1][6];
                            player2.score=undo_grid[counter-1][7];
                            undoFlag=0;
                            flag=1;
                            goto label2;
                            break;
                        default:
                            printf("ERROR!");
                            flag=1;
                            break;
                    }
                }
                flag=1;
                R=scan_row();
                C=scan_col();
                valid=validity(R,C,index,grid,boxes);
                if(valid==0){
                    while(valid==0){
                        printf("\nINVALID POINT!!!\n");
                        R=scan_row();
                        C=scan_col();
                        valid=validity(R,C,index,grid,boxes);
                    }
                }
            }
            undo_grid[counter][0]=R;
            undo_grid[counter][1]=C;
            undo_grid[counter][2]=turn;
            undo_grid[counter][3]=loop;
            undo_grid[counter][4]=player1.moves;
            undo_grid[counter][5]=player2.moves;
            undo_grid[counter][6]=player1.score;
            undo_grid[counter][7]=player2.score;
            counter++;
            assign_grid(R,C,index,grid,turn,color);
            pre_score=player2.score;
            player2.score+=check_box(index, boxes, turn, grid,color);
            if(pre_score<player2.score){
                left_moves++;
            }
            player2.moves++;
        }
        left_moves--;
        loop--;
        end=time(NULL);
    }
    if(player1.score>player2.score){
        red();
        printf("\n%s ",player1.name);
        yellow();
        printf("WON!!");
    }else if(player2.score>player1.score){
        blue();
        printf("\n%s ",player2.name);
        yellow();
        printf("WON!!");
    }else{
        yellow();
        printf("\n>>>TIE<<<");
    }
    top_ten_assign(player1.name,player1.score);
    top_ten_assign(player2.name,player2.score);

}


void dec_grid(int row,int col,int grid[row][col]){
    int i,j;
    for(i=0; i<row; i++){
        for(j=0; j<col; j++){
            grid[i][j]=32;
        }
    }
    for(i=0; i<row; i+=4){
        for(j=0; j<col; j+=4){
            grid[i][j]=254;
        }
    }
}

void print_grid(int row,int col,int grid[row][col],char color[][col]){
    int r=1,c=1,k=0;
    printf("   ");
    for(int i=0; i<col; i+=2){
        if(r>=10){
            yellow();
            printf("%d      ",r);
            reset();
        }else{
            yellow();
            printf("%d       ",r);
            reset();
        }
        r++;
    }
    printf("\n\n");
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++)
        {
            if(i==k)
            {
                k+=2;
                if(c>=10){
                    yellow();
                    printf("%d ",c);
                    reset();
                }else{
                    yellow();
                    printf("%d  ",c);
                    reset();
                }
                c++;
            }else{
                printf("   ");
            }
            if(color[i][j]=='r'){
                red();
                printf("%c",grid[i][j]);
                reset();
            }else if(color[i][j]=='b'){
                blue();
                printf("%c",grid[i][j]);
                reset();
            }else{
                yellow();
                printf("%c",grid[i][j]);
                reset();
            }
        }
        printf("\n");
    }
}

int turns(int left_moves){
    int turn=1;
    if(left_moves%2==1){
        turn=2;
    }
    return turn;
}

int scan_row(){
    int R;
    yellow();
    printf("\n\nEnter the number of the row --> ");
    scanf("%d",&R);
    reset();
    return R;
}

int scan_col(){
    int C;
    yellow();
    printf("\nEnter the number of the column --> ");
    scanf("%d",&C);
    reset();
    return C;
}

void reassign(int R , int C , int index , int grid[index][index] , char color[index][index]){
    int i,j;
    if(C%2==0){
        j=((C-1)*2)-1;
        for(i=j ; i<(j+3) ; i++){
            grid[(R-1)*2][i]=32;
            color[(R-1)*2][i]='w';
            if(i==j+1 && ((R-1)*2+2)>=0 && ((R-1)*2+2)<index && ((R-1)*2-2)>=0 && ((R-1)*2-2)<index){
                grid[(R-1)*2+2][i]=32;
                color[(R-1)*2+2][i]='w';
            }if(i==j+1 && ((R-1)*2-2)>=0 && ((R-1)*2-2)<index){
                grid[(R-1)*2-2][i]=32;
                color[(R-1)*2-2][i]='w';
            }
        }
    }else{
        j=((R-1)*2)-1;
        for(i=j ; i<(j+3) ; i++){
            grid[i][(C-1)*2]=32;
            color[i][(C-1)*2]='w';
            if(i==j+1 && ((C-1)*2+2)>=0 && ((C-1)*2+2)<index && ((C-1)*2-2)>=0 && ((C-1)*2-2)<index){
                grid[i][(C-1)*2+2]=32;
                color[i][(C-1)*2+2]='w';
            }if(i==j+1 && ((C-1)*2-2)>=0 && ((C-1)*2-2)<index){
                grid[i][(C-1)*2-2]=32 ;
                color[i][(C-1)*2-2]='w';
            }
        }
    }
}

void assign_grid(int R , int C , int index , int grid[index][index] , int turn , char color[index][index]){
    int i,j;
    if(C%2==0){
        j=((C-1)*2)-1;
        for(i=j ; i<(j+3) ; i++){
            grid[(R-1)*2][i]=196;
            if(turn==1){
                color[(R-1)*2][i]='r';
            }else{
                color[(R-1)*2][i]='b';
            }
        }
    }else{
        j=((R-1)*2)-1;
        for(i=j ; i<(j+3) ; i++){
            grid[i][(C-1)*2]=124;
            if(turn==1){
                color[i][(C-1)*2]='r';
            }else{
                color[i][(C-1)*2]='b';
            }
        }
    }
}

int validity(int R,int C,int index ,int grid[index][index],int boxes){
    int valid=0;
    int x=(R-1)*2 ,y=(C-1)*2;
    if((R>0) && (R<=(2*boxes+1)) && (C>0) && (C<=(2*boxes+1)) && (((R%2==0) && (C%2==1)) || ((C%2==0) && (R%2==1))) && (grid[x][y]==32)){
        valid=1;
    }
    return valid;
}

int check_box(int index,int boxes,int turn,int grid[index][index],char color[index][index]){
    int i,j,score=0;
    for(i=2; i<index; i+=4){
        for(j=2; j<index; j+=4){
            if(grid[i][j+2]!=32&&grid[i][j-2]!=32&&grid[i+2][j]!=32&&grid[i-2][j]!=32&&grid[i][j]==32){
                score++;
                if(turn==1){
                    color[i][j]='r';
                    grid[i][j]=65;
                }else{
                    color[i][j]='b';
                    grid[i][j]=66;
                }
            }
        }
    }
    return score ;
}

void print_info(player player1,player player2){
    red();
    printf("\t\t\t\t%s ",player1.name);
    blue();
    printf("\t\t\t\t\t  %s\n\n",player2.name);
    yellow();
    printf("Moves   \t\t\t  ");
    red();
    printf("%d\t\t\t\t\t\t",player1.moves);
    blue();
    printf("%d\n",player2.moves);
    yellow();
    printf("Score   \t\t\t  ");
    red();
    printf("%d\t\t\t\t\t\t",player1.score);
    blue();
    printf("%d\n",player2.score);
    reset();
}

int pc(int boxes){
    int a, val;
    a=2*boxes+2;
    val=rand()%a+1;
    return val;
}

int AI_row(int index,int boxes,int grid[index][index]){
    int i,j,R;
    for(i=2; i<index; i+=4){
        for(j=2; j<index; j+=4){
            if(grid[i][j+2]!=32&&grid[i][j-2]!=32&&grid[i+2][j]!=32&&grid[i-2][j]==32){
                R=((i-2)/2)+1;
                break;
            }else if(grid[i][j+2]!=32&&grid[i][j-2]!=32&&grid[i+2][j]==32&&grid[i-2][j]!=32){
                R=((i+2)/2)+1;
                break;
            }else if(grid[i][j+2]!=32&&grid[i][j-2]==32&&grid[i+2][j]!=32&&grid[i-2][j]!=32){
                R=((i)/2)+1;
                break;
            }else if(grid[i][j+2]==32&&grid[i][j-2]!=32&&grid[i+2][j]!=32&&grid[i-2][j]!=32){
                R=((i)/2)+1;
                break;
            }
        }
    }
    return R;
}

int AI_column(int index,int boxes,int grid[index][index]){
    int i,j,C;
    for(i=2; i<index; i+=4){
        for(j=2; j<index; j+=4){
            if(grid[i][j+2]!=32&&grid[i][j-2]!=32&&grid[i+2][j]!=32&&grid[i-2][j]==32){
                C=((j)/2)+1;
                break;
            }else if(grid[i][j+2]!=32&&grid[i][j-2]!=32&&grid[i+2][j]==32&&grid[i-2][j]!=32){
                C=((j)/2)+1;
                break;
            }else if(grid[i][j+2]!=32&&grid[i][j-2]==32&&grid[i+2][j]!=32&&grid[i-2][j]!=32){
                C=((j-2)/2)+1;
                break;
            }else if(grid[i][j+2]==32&&grid[i][j-2]!=32&&grid[i+2][j]!=32&&grid[i-2][j]!=32){
                C=((j+2)/2)+1;
                break;
            }
        }
    }
    return C;
}

void save_game(int index, int grid[index][index], player player1, player player2,int turn, int leftMoves,time_t startTime, time_t endTime,char colors[index][index], int fileNo,int boxes,int undo_grid[2*(boxes*boxes+boxes)][8], int counter , int flag , int undo_flag){
    FILE *file;
    int i, j;
    if(fileNo==1){
        file=fopen("Game1.txt", "w");
    }else if(fileNo==2){
        file=fopen("Game2.txt", "w");
    }else if(fileNo==3){
        file=fopen("Game3.txt", "w");
    }

    fprintf(file,"%d %d %d ", player1.moves, player1.score, player1.name);
    fprintf(file,"%d %d %d ", player2.moves, player2.score, player2.name);
    fprintf(file,"%d %d %d %llu %llu %d %d %d %d ", index, turn, leftMoves, startTime, endTime, boxes, counter, flag, undo_flag);
    for(i=0; i<index; i++){
        for(j=0; j<index; j++){
            fprintf(file,"%d ",grid[i][j]);
        }
    }
    for(i=0; i<index; i++){
        for(j=0; j<index; j++){
            fprintf(file,"%c ",colors[i][j]);
        }
    }
    for(i=0; i<2*(boxes*boxes+boxes); i++){
        for(j=0; j<8; j++){
            fprintf(file,"%c ",undo_grid[i][j]);
        }
    }
    fclose(file);
}

/*
load load_game(int fileNo){
    load loadL;
    FILE *file;
    int i, j;
    if(fileNo==1){
        file=fopen("Game1.txt", "r");
    }else if(fileNo==2){
        file=fopen("Game2.txt", "r");
    }else if(fileNo==3){
        file=fopen("Game3.txt", "r");
    }
    fscanf(file,"%d %d %d ", &loadL.player1.moves, &loadL.player1.name, &loadL.player1.score);
    fscanf(file,"%d %d %d ", &loadL.player2.moves, &loadL.player2.name, &loadL.player2.score);
    fscanf(file,"%d %d %d %d %d %d %d %d %d ", &loadL.index, &loadL.turn, &loadL.leftMoves, &loadL.startTime, loadL.endTime, loadL.boxes, loadL.counter, loadL.flag, loadL.undoFlag);
    for(i=0; i<index; i++){
        for(j=0; j<index; j++){
            fscanf(file, "%d ", &loadL.grid[i][j]);
        }
    }
    for(i=0; i<index; i++){
        for(j=0; j<index; j++){
            fscanf(file, "%c ", &loadL.colors[i][j]);
        }
    }
    for(i=0; i<2*(boxes*boxes+boxes); i++){
        for(j=0; j<8; j++){
            fscanf(file,"%c ",&loadL.undoGrid[i][j]);
        }
    }
    return loadL;
}
*/

void top_ten_assign(char name[], int score){
    FILE *top10;
    int i,j;
    char topTenNames[50][1], tempName[15];
    int topTenScores[50]={0}, tempScore;
    top10=fopen("Top 10.txt", "a");
    fprintf(top10,"%s %d ", name, score);
    fclose(top10);
    top10=fopen("Top 10.txt", "r");
    for(i=0; i<50; i++){
        fscanf(top10,"%s ",&topTenNames[i][1]);
        fscanf(top10,"%d ",&topTenScores[i]);
    }
    fclose(top10);
    for(i=0; i<50; i++){
        for(j=i+1; j<50; j++){
            if(topTenScores[i]<topTenScores[j]){
                strcpy(tempName,topTenNames[i][1]);
                tempScore=topTenScores[i];
                strcpy(topTenNames[i][1],topTenNames[j][1]);
                topTenScores[i] = topTenScores[j];
                strcpy(topTenNames[j][1],tempName);
                topTenScores[j] = tempScore;
            }
        }
    }
    top10=fopen("Top 10.txt", "w");
    for(i=0; i<50; i++){
        fprintf(top10,"%s ",topTenNames[i][1]);
        fprintf(top10,"%d ",topTenScores[i]);
    }
    fclose(top10);
}

void top_ten(){
    char topTenNames[10][1];
    int topTenScores[10];
    int i;
    FILE *top10;
    top10=fopen("Top 10.txt", "a");
    for(i=0; i<10; i++){
        fscanf(top10,"%s ",&topTenNames[i][1]);
        fscanf(top10,"%d ",&topTenScores[i]);
    }
    system("cls");
    printf("\t\t\t\t   >>>>>TOP 10<<<<<\n\n");
    for(i=0; i<10; i++){
        printf("%d- %s \t%d\n",i+1, topTenNames[i][1], topTenScores[i]);

    }
    fclose(top10);

}

