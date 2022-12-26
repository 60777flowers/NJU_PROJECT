#ifndef UNTITLED1_FUNCTIONS_H
#define UNTITLED1_FUNCTIONS_H
#include "prepare.h"
#include <stdlib.h>
#include <time.h>



extern player* RED;
extern player* YELLOW;
extern player* GREEN;
extern player* BLUE;

extern chess* RED_A;
extern chess* RED_B;
extern chess* RED_C;
extern chess* RED_D;

extern chess* BLUE_A;
extern chess* BLUE_B;
extern chess* BLUE_C;
extern chess* BLUE_D;

extern chess* GREEN_A;
extern chess* GREEN_B;
extern chess* GREEN_C;
extern chess* GREEN_D;

extern chess* YELLOW_A;
extern chess* YELLOW_B;
extern chess* YELLOW_C;
extern chess* YELLOW_D;

extern char Board[14][14];

chess *movechess=NULL;

bool game_continue()
{
    if (RED->approched<4&&YELLOW->approched<4&&GREEN->approched<4&&BLUE->approched<4)
    {return 1;}
    return 0;
}

int getDieRes(player*Player)
{
    if(!(Player->human_gamer))
    {goto suijitouzi;}
    char cheatjudge;
    T2:
    printf("wanna to cheat? Y/N\n");
    scanf(" %c",&cheatjudge);
    int r;
    switch (cheatjudge)
    {
        T3:case 'Y':
            int amount;
            amount=6;
            printf("how much step u want?(1~9)\n");
            scanf(" %d",&amount);
            if(amount>9)
            {
                printf("1~9 please\n");
                goto T3;
            }
            return amount;
        suijitouzi:case 'N':
            srand(time(0));  // 使用当前时间作为种子初始化随机数生成器
            r = rand() % 6+1;  // 生成 1~6 之间的随机数
            printf("The number of points to roll the dice is: %d\n",r);
            return r;
        default:
            printf("Y/N please\n");
            goto T2;
    }
}

void print()
{
    for(int i=0;i<13;i++)
    {
        for(int j=0;j<13;j++)
        {printf("%c",Board[i][j]);}
        printf("\n");
    }
}

int move(player* Player,int count)
{
    //棋子指针的初始化
    RED_A=&(RED->A);RED_A->next=RED_B;
    RED_B=&(RED->B);RED_B->next=RED_C;
    RED_C=&(RED->C);RED_C->next=RED_D;
    RED_D=&(RED->D);RED_D->next=RED_A;

    BLUE_A=&(BLUE->A);BLUE_A->next=BLUE_B;
    BLUE_B=&(BLUE->B);BLUE_B->next=BLUE_C;
    BLUE_C=&(BLUE->C);BLUE_C->next=BLUE_D;
    BLUE_D=&(BLUE->D);BLUE_D->next=BLUE_A;

    GREEN_A=&(GREEN->A);GREEN_A->next=GREEN_B;
    GREEN_B=&(GREEN->B);GREEN_B->next=GREEN_C;
    GREEN_C=&(GREEN->C);GREEN_C->next=GREEN_D;
    GREEN_D=&(GREEN->D);GREEN_D->next=GREEN_A;

    YELLOW_A=&(YELLOW->A);YELLOW_A->next=YELLOW_B;
    YELLOW_B=&(YELLOW->B);YELLOW_B->next=YELLOW_C;
    YELLOW_C=&(YELLOW->C);YELLOW_C->next=YELLOW_D;
    YELLOW_D=&(YELLOW->D);YELLOW_D->next=YELLOW_A;


    //count=6;
    printf("first look at your chess guys\n");
    printf("A is at (%d,%d)\n",Player->A.chess_place.SNj,Player->A.chess_place.SNi);
    printf("B is at (%d,%d)\n",Player->B.chess_place.SNj,Player->B.chess_place.SNi);
    printf("C is at (%d,%d)\n",Player->C.chess_place.SNj,Player->C.chess_place.SNi);
    printf("D is at (%d,%d)\n",Player->D.chess_place.SNj,Player->D.chess_place.SNi);



    switch (Player->ID)
    {
        case 'R':
            movechess=RED_A;
            break;
        case 'B':
            movechess=BLUE_A;
            break;
        case 'G':
            movechess=GREEN_A;
            break;
        case 'Y':
            movechess=YELLOW_A;
            break;
    }

    if(count==6&&Player->unstart>0)//出发判断
    {
        char tmp;

        if(!(Player->human_gamer))
        {
            tmp='Y';
            goto computer_gamer_stand1;
        }
        T1:printf("wanna a new chess to start? Y/N\n");
        scanf(" %c",&tmp);
        computer_gamer_stand1://电脑优先出门（它越菜我们越好赢的考虑）
        if(tmp=='Y')
        {
            switch (Player->unstart)//可以用指针优化但是懒得了
            {
                case 4:
                    Board[Player->A.chess_place.SNi][Player->A.chess_place.SNj]='O';
                    Player->A.chess_place.SNj=Player->startj;Player->A.chess_place.SNi=Player->starti;
                    Board[Player->A.chess_place.SNi][Player->A.chess_place.SNj]=Player->ID;
                    Player->unstart--;
                    Player->A.start=1;
                    return 0;
                case 3:
                    Board[Player->B.chess_place.SNi][Player->B.chess_place.SNj]='O';
                    Player->B.chess_place.SNj=Player->startj;Player->B.chess_place.SNi=Player->starti;
                    Board[Player->B.chess_place.SNi][Player->B.chess_place.SNj]=Player->ID;
                    Player->unstart--;
                    Player->B.start=1;
                    return 0;
                case 2:
                    Board[Player->C.chess_place.SNi][Player->C.chess_place.SNj]='O';
                    Player->C.chess_place.SNj=Player->startj;Player->C.chess_place.SNi=Player->starti;
                    Board[Player->C.chess_place.SNi][Player->C.chess_place.SNj]=Player->ID;
                    Player->unstart--;
                    Player->C.start=1;
                    return 0;
                case 1:
                    Board[Player->D.chess_place.SNi][Player->D.chess_place.SNj]='O';
                    Player->D.chess_place.SNj=Player->startj;Player->D.chess_place.SNi=Player->starti;
                    Board[Player->D.chess_place.SNi][Player->D.chess_place.SNj]=Player->ID;
                    Player->unstart--;
                    Player->D.start=1;
                    return 0;
            }
        }
        else
        {
            if(Player->unstart+Player->approched==4&&tmp=='N')//没一个出发的
            {printf("But Y?,Please think more\n");goto T1;}
            if(tmp=='N')//不新出发
            {goto Move;}
            else//没输入Y/N
            { printf("Y/N please\n");goto T1;}
        }
    }



    if(Player->unstart==4)//特殊情况
    {return 0;}

    char chmove_chess;
    Move://真正的移动阶段
    printf("look at your movable chess and make a choice:\n");//可移动棋子展示
    if(Player->A.start&&(!Player->A.arrived))
    { printf("A is at (%d,%d)\n",Player->A.chess_place.SNj,Player->A.chess_place.SNi);}
    if(Player->B.start&&(!Player->B.arrived))
    { printf("B is at (%d,%d)\n",Player->B.chess_place.SNj,Player->B.chess_place.SNi);}
    if(Player->C.start&&(!Player->C.arrived))
    { printf("C is at (%d,%d)\n",Player->C.chess_place.SNj,Player->C.chess_place.SNi);}
    if(Player->D.start&&(!Player->D.arrived))
    { printf("D is at (%d,%d)\n",Player->D.chess_place.SNj,Player->D.chess_place.SNi);}

    //........................................................................................................................................................................................//


    if(!(Player->human_gamer))//优先走排名靠前的棋子
    {
        if(Player->A.start&&(!Player->A.arrived))
        {chmove_chess='A';goto computer_gamer_stand2;}
        if(Player->B.start&&(!Player->B.arrived))
        { chmove_chess='B';goto computer_gamer_stand2;}
        if(Player->C.start&&(!Player->C.arrived))
        { chmove_chess='C';goto computer_gamer_stand2;}
        if(Player->D.start&&(!Player->D.arrived))
        { chmove_chess='D';goto computer_gamer_stand2;}
    }
    chmove_chess='A';
    scanf(" %c",&chmove_chess);\
    if(chmove_chess>'D'||chmove_chess<'A')
    {
        printf("don't do fucking illegal input please~ try again\n");
        goto Move;
    }
    computer_gamer_stand2:
    switch (Player->ID) {
        case 'R':
            //printf("DEBUG1\n");
            switch (chmove_chess)//错误输入类型：1还未出发的棋子；2已经到达的棋子；3甚至不是一个棋子
            {
                case 'D':
                    movechess = movechess->next;
                case 'C':
                    movechess = movechess->next;
                case 'B':
                    movechess = movechess->next;
                case 'A'://这里是红色的移动
                    //printf("DEBUG2\n");
                    if (!movechess->start || movechess->chess_place.SNi == 0)//到达了或者还没出发
                    {
                        printf("movable chess please~ try again\n");
                        switch (chmove_chess)
                        {
                            case 'B':
                                movechess=movechess->next;
                            case 'C':
                                movechess=movechess->next;
                            case 'D':
                                movechess=movechess->next;
                            case 'A':
                                break;
                        }
                        goto Move;
                    }

                    Board[movechess->chess_place.SNi][movechess->chess_place.SNj] = 'O';
                    //printf("DEBUG3\n");
                    int tmpi = movechess->chess_place.SNi;
                    int tmpj = movechess->chess_place.SNj;//判断一下会不会踩掉以及有没有重叠
                    //printf("DEBUG4\n");
                    movechess = movechess->next;
                    //printf("DEBUG5\n");
                    for (int k = 0; k < 3; k++, movechess = movechess->next)//重叠判断
                    {
                        if (tmpj == movechess->chess_place.SNj && tmpi == movechess->chess_place.SNi) {
                            Board[movechess->chess_place.SNi][movechess->chess_place.SNj] = 'R';
                        }
                    }
                    //printf("DEBUG3\n");

                    while (movechess->chess_place.SNj == 4 && movechess->chess_place.SNi < 8 && count > 0)//公共棋盘部分的移动
                    {
                        count--;
                        movechess->chess_place.SNi++;
                    }
                    while (movechess->chess_place.SNi == 8 && movechess->chess_place.SNj < 8 && count > 0) {
                        count--;
                        movechess->chess_place.SNj++;
                    }
                    while (movechess->chess_place.SNj == 8 && movechess->chess_place.SNi > 4 && count > 0)//公共棋盘部分的移动
                    {
                        count--;
                        movechess->chess_place.SNi--;
                    }
                    while (movechess->chess_place.SNi == 4 && movechess->chess_place.SNj > 6 && count > 0) {
                        count--;
                        movechess->chess_place.SNj--;
                    }
                    while (count > 0) {
                        movechess->chess_place.SNi--;
                        count--;
                        if (movechess->chess_place.SNi == 0) { break; }
                    }
                    while (count > 0) {
                        movechess->chess_place.SNi++;
                        count--;
                        if (movechess->chess_place.SNi == 4) { break; }
                    }
                    while (count > 0) {
                        movechess->chess_place.SNi--;
                        count--;
                    }
                    //printf("DEBUG3\n");
                    printf("Now %c is at (%d,%d)\n", movechess->ID, movechess->chess_place.SNj,
                           movechess->chess_place.SNi);


                    tmpi=movechess->chess_place.SNi;tmpj=movechess->chess_place.SNj;
                    Player = Player->next;
                    for (int i = 0; i < 3; i++, Player = Player->next) {
                        if (Player->A.chess_place.SNi == tmpi)//有没有踩到别人的A棋子
                        {
                            if (Player->A.chess_place.SNj == tmpj) {
                                Player->A.chess_place.SNj = Player->startj;
                                Player->A.chess_place.SNi = Player->starti;
                                Board[Player->starti][Player->startj] = Player->ID;
                            }
                        }
                        if (Player->B.chess_place.SNi == tmpi)//有没有踩到别人的B棋子
                        {
                            if (Player->B.chess_place.SNj == tmpj) {
                                Player->B.chess_place.SNj = Player->startj;
                                Player->B.chess_place.SNi = Player->starti;
                                Board[Player->starti][Player->startj] = Player->ID;
                            }
                        }
                        if (Player->C.chess_place.SNi == tmpi)//有没有踩到别人的C棋子
                        {
                            if (Player->C.chess_place.SNj == tmpj) {
                                Player->C.chess_place.SNj = Player->startj;
                                Player->C.chess_place.SNi = Player->starti;
                                Board[Player->starti][Player->startj] = Player->ID;
                            }
                        }
                        if (Player->D.chess_place.SNi == tmpi)//有没有踩到别人的D棋子
                        {
                            if (Player->D.chess_place.SNj == tmpj) {
                                Player->D.chess_place.SNj = Player->startj;
                                Player->D.chess_place.SNi = Player->starti;
                                Board[Player->starti][Player->startj] = Player->ID;
                            }
                        }
                    }
                    Board[movechess->chess_place.SNi][movechess->chess_place.SNj] = 'R';
                    if (movechess->chess_place.SNi == 0) {
                        Player->approched++;
                        movechess->arrived = 1;
                    }
                    return 0;
            }
//.............................................................................................................................................................................................//
        case 'B':
            switch (chmove_chess)//错误输入类型：1还未出发的棋子；2已经到达的棋子；3甚至不是一个棋子
            {
                case 'D':
                    movechess = movechess->next;
                case 'C':
                    movechess = movechess->next;
                case 'B':
                    movechess = movechess->next;
                case 'A'://这里是红色的移动
                    //printf("DEBUG2\n");
                    if (!movechess->start || movechess->chess_place.SNj == 0)//到达了或者还没出发//修改5
                    {
                        printf("movable chess please~ try again\n");
                        switch (chmove_chess)
                        {
                            case 'B':
                                movechess=movechess->next;
                            case 'C':
                                movechess=movechess->next;
                            case 'D':
                                movechess=movechess->next;
                            case 'A':
                                break;
                        }
                        goto Move;
                    }

                    Board[movechess->chess_place.SNi][movechess->chess_place.SNj] = 'O';
                    //printf("DEBUG3\n");
                    int tmpi = movechess->chess_place.SNi;
                    int tmpj = movechess->chess_place.SNj;//判断一下会不会踩掉以及有没有重叠
                    //printf("DEBUG4\n");
                    movechess = movechess->next;
                    //printf("DEBUG5\n");
                    for (int k = 0; k < 3; k++, movechess = movechess->next) {
                        if (tmpj == movechess->chess_place.SNj && tmpi == movechess->chess_place.SNi) {
                            Board[movechess->chess_place.SNi][movechess->chess_place.SNj] = 'B';//修改1
                        }
                    }
                    //printf("DEBUG3\n");
//移动部分改这里就行了，修改2
                    while (movechess->chess_place.SNi == 8 && movechess->chess_place.SNj < 8 && count > 0)//公共棋盘部分的移动
                    {
                        count--;
                        movechess->chess_place.SNj++;
                    }
                    while (movechess->chess_place.SNj == 8 && movechess->chess_place.SNi >4 && count > 0) {
                        count--;
                        movechess->chess_place.SNi--;
                    }
                    while (movechess->chess_place.SNi == 4 && movechess->chess_place.SNj > 4 && count > 0)//公共棋盘部分的移动
                    {
                        count--;
                        movechess->chess_place.SNj--;
                    }
                    while (movechess->chess_place.SNj == 4 && movechess->chess_place.SNi < 6 && count > 0) {
                        count--;
                        movechess->chess_place.SNi++;
                    }
                    while (count > 0) {
                        movechess->chess_place.SNj--;
                        count--;
                        if (movechess->chess_place.SNj == 0) { break; }
                    }
                    while (count > 0) {
                        movechess->chess_place.SNj++;
                        count--;
                        if (movechess->chess_place.SNj == 4) { break; }
                    }
                    while (count > 0) {
                        movechess->chess_place.SNj--;
                        count--;
                    }
                    //printf("DEBUG3\n");
                    printf("Now %c is at (%d,%d)\n", movechess->ID, movechess->chess_place.SNj,movechess->chess_place.SNi);


                    tmpi=movechess->chess_place.SNi;tmpj=movechess->chess_place.SNj;
                    Player = Player->next;
                    for (int i = 0; i < 3; i++, Player = Player->next) {
                        if (Player->A.chess_place.SNi == tmpi)//有没有踩到别人的A棋子
                        {
                            if (Player->A.chess_place.SNj == tmpj) {
                                Player->A.chess_place.SNj = Player->startj;
                                Player->A.chess_place.SNi = Player->starti;
                                Board[Player->starti][Player->startj] = Player->ID;
                            }
                        }
                        if (Player->B.chess_place.SNi == tmpi)//有没有踩到别人的B棋子
                        {
                            if (Player->B.chess_place.SNj == tmpj) {
                                Player->B.chess_place.SNj = Player->startj;
                                Player->B.chess_place.SNi = Player->starti;
                                Board[Player->starti][Player->startj] = Player->ID;
                            }
                        }
                        if (Player->C.chess_place.SNi == tmpi)//有没有踩到别人的C棋子
                        {
                            if (Player->C.chess_place.SNj == tmpj) {
                                Player->C.chess_place.SNj = Player->startj;
                                Player->C.chess_place.SNi = Player->starti;
                                Board[Player->starti][Player->startj] = Player->ID;
                            }
                        }
                        if (Player->D.chess_place.SNi == tmpi)//有没有踩到别人的D棋子
                        {
                            if (Player->D.chess_place.SNj == tmpj) {
                                Player->D.chess_place.SNj = Player->startj;
                                Player->D.chess_place.SNi = Player->starti;
                                Board[Player->starti][Player->startj] = Player->ID;
                            }
                        }
                    }
                    Board[movechess->chess_place.SNi][movechess->chess_place.SNj] = Player->ID;//修改3
                    if (movechess->chess_place.SNj == 0) {
                        Player->approched++;
                        movechess->arrived = 1;
                    }
                    return 0;
            }
//..............................................................................................................................................................................................//
        case 'G':
            switch (chmove_chess)//错误输入类型：1还未出发的棋子；2已经到达的棋子；3甚至不是一个棋子
            {
                case 'D':
                    movechess = movechess->next;
                case 'C':
                    movechess = movechess->next;
                case 'B':
                    movechess = movechess->next;
                case 'A'://这里是红色的移动
                    //printf("DEBUG2\n");
                    if (!movechess->start || movechess->chess_place.SNi == 12)//到达了或者还没出发//修改5
                    {
                        printf("movable chess please~ try again\n");
                        switch (chmove_chess)
                        {
                            case 'B':
                                movechess=movechess->next;
                            case 'C':
                                movechess=movechess->next;
                            case 'D':
                                movechess=movechess->next;
                            case 'A':
                                break;
                        }
                        goto Move;
                    }

                    Board[movechess->chess_place.SNi][movechess->chess_place.SNj] = 'O';
                    //printf("DEBUG3\n");
                    int tmpi = movechess->chess_place.SNi;
                    int tmpj = movechess->chess_place.SNj;//判断一下会不会踩掉以及有没有重叠
                    //printf("DEBUG4\n");
                    movechess = movechess->next;
                    //printf("DEBUG5\n");
                    for (int k = 0; k < 3; k++, movechess = movechess->next) {
                        if (tmpj == movechess->chess_place.SNj && tmpi == movechess->chess_place.SNi) {
                            Board[movechess->chess_place.SNi][movechess->chess_place.SNj] = 'G';//修改1
                        }
                    }
                    //printf("DEBUG3\n");
//移动部分改这里就行了，修改2
                    while (movechess->chess_place.SNj == 8 && movechess->chess_place.SNi> 4 && count > 0)//公共棋盘部分的移动
                    {
                        count--;
                        movechess->chess_place.SNi--;
                    }
                    while (movechess->chess_place.SNi==4 && movechess->chess_place.SNj>4 && count > 0) {
                        count--;
                        movechess->chess_place.SNj--;
                    }
                    while (movechess->chess_place.SNj == 4 && movechess->chess_place.SNi<8 && count > 0)//公共棋盘部分的移动
                    {
                        count--;
                        movechess->chess_place.SNi++;
                    }
                    while (movechess->chess_place.SNi== 8 && movechess->chess_place.SNj <6 && count > 0) {
                        count--;
                        movechess->chess_place.SNj++;
                    }
                    while (count > 0) {
                        movechess->chess_place.SNi++;
                        count--;
                        if (movechess->chess_place.SNi == 12) { break; }
                    }
                    while (count > 0) {
                        movechess->chess_place.SNi--;
                        count--;
                        if (movechess->chess_place.SNi == 8) { break; }
                    }
                    while (count > 0) {
                        movechess->chess_place.SNi++;
                        count--;
                    }
                    //改到这里
                    //printf("DEBUG3\n");
                    printf("Now %c is at (%d,%d)\n", movechess->ID, movechess->chess_place.SNj,movechess->chess_place.SNi);


                    tmpi=movechess->chess_place.SNi;tmpj=movechess->chess_place.SNj;
                    Player = Player->next;
                    for (int i = 0; i < 3; i++, Player = Player->next) {
                        if (Player->A.chess_place.SNi == tmpi)//有没有踩到别人的A棋子
                        {
                            if (Player->A.chess_place.SNj == tmpj) {
                                Player->A.chess_place.SNj = Player->startj;
                                Player->A.chess_place.SNi = Player->starti;
                                Board[Player->starti][Player->startj] = Player->ID;
                            }
                        }
                        if (Player->B.chess_place.SNi == tmpi)//有没有踩到别人的B棋子
                        {
                            if (Player->B.chess_place.SNj == tmpj) {
                                Player->B.chess_place.SNj = Player->startj;
                                Player->B.chess_place.SNi = Player->starti;
                                Board[Player->starti][Player->startj] = Player->ID;
                            }
                        }
                        if (Player->C.chess_place.SNi == tmpi)//有没有踩到别人的C棋子
                        {
                            if (Player->C.chess_place.SNj == tmpj) {
                                Player->C.chess_place.SNj = Player->startj;
                                Player->C.chess_place.SNi = Player->starti;
                                Board[Player->starti][Player->startj] = Player->ID;
                            }
                        }
                        if (Player->D.chess_place.SNi == tmpi)//有没有踩到别人的D棋子
                        {
                            if (Player->D.chess_place.SNj == tmpj) {
                                Player->D.chess_place.SNj = Player->startj;
                                Player->D.chess_place.SNi = Player->starti;
                                Board[Player->starti][Player->startj] = Player->ID;
                            }
                        }
                    }
                    Board[movechess->chess_place.SNi][movechess->chess_place.SNj] = Player->ID;//修改3
                    if (movechess->chess_place.SNi == 12) {
                        Player->approched++;
                        movechess->arrived = 1;
                    }
                    return 0;
            }
            //.............................................................................................................................................................................................//
        case 'Y':
            switch (chmove_chess)//错误输入类型：1还未出发的棋子；2已经到达的棋子；3甚至不是一个棋子
            {
                case 'D':
                    movechess = movechess->next;
                case 'C':
                    movechess = movechess->next;
                case 'B':
                    movechess = movechess->next;
                case 'A'://这里是红色的移动
                    //printf("DEBUG2\n");
                    if (!movechess->start || movechess->chess_place.SNj == 12)//到达了或者还没出发//修改5
                    {
                        printf("movable chess please~ try again\n");
                        switch (chmove_chess)
                        {
                            case 'B':
                                movechess=movechess->next;
                            case 'C':
                                movechess=movechess->next;
                            case 'D':
                                movechess=movechess->next;
                            case 'A':
                                break;
                        }
                        goto Move;
                    }

                    Board[movechess->chess_place.SNi][movechess->chess_place.SNj] = 'O';
                    //printf("DEBUG3\n");
                    int tmpi = movechess->chess_place.SNi;
                    int tmpj = movechess->chess_place.SNj;//判断一下会不会踩掉以及有没有重叠
                    //printf("DEBUG4\n");
                    movechess = movechess->next;
                    //printf("DEBUG5\n");
                    for (int k = 0; k < 3; k++, movechess = movechess->next) {
                        if (tmpj == movechess->chess_place.SNj && tmpi == movechess->chess_place.SNi) {
                            Board[movechess->chess_place.SNi][movechess->chess_place.SNj] = 'B';//修改1
                        }
                    }
                    //printf("DEBUG3\n");
//移动部分改这里就行了，修改2
                    while (movechess->chess_place.SNi == 4 && movechess->chess_place.SNj >4 && count > 0)//公共棋盘部分的移动
                    {
                        count--;
                        movechess->chess_place.SNj--;
                    }
                    while (movechess->chess_place.SNj == 4 && movechess->chess_place.SNi<8&& count > 0) {
                        count--;
                        movechess->chess_place.SNi++;
                    }
                    while (movechess->chess_place.SNi == 8 && movechess->chess_place.SNj <8 && count > 0)//公共棋盘部分的移动
                    {
                        count--;
                        movechess->chess_place.SNj++;
                    }
                    while (movechess->chess_place.SNj ==8 && movechess->chess_place.SNi >6 && count > 0) {
                        count--;
                        movechess->chess_place.SNi--;
                    }
                    while (count > 0) {
                        movechess->chess_place.SNj++;
                        count--;
                        if (movechess->chess_place.SNj == 12) { break; }
                    }
                    while (count > 0) {
                        movechess->chess_place.SNj--;
                        count--;
                        if (movechess->chess_place.SNj == 8) { break; }
                    }
                    while (count > 0) {
                        movechess->chess_place.SNj++;
                        count--;
                    }
                    //printf("DEBUG3\n");
                    printf("Now %c is at (%d,%d)\n", movechess->ID, movechess->chess_place.SNj,movechess->chess_place.SNi);


                    tmpi=movechess->chess_place.SNi;tmpj=movechess->chess_place.SNj;
                    Player = Player->next;
                    for (int i = 0; i < 3; i++, Player = Player->next)
                    {
                        if (Player->A.chess_place.SNi == tmpi)//有没有踩到别人的A棋子
                        {
                            if (Player->A.chess_place.SNj == tmpj)
                            {
                                Player->A.chess_place.SNj = Player->startj;
                                Player->A.chess_place.SNi = Player->starti;
                                Board[Player->starti][Player->startj] = Player->ID;
                            }
                        }
                        if (Player->B.chess_place.SNi == tmpi)//有没有踩到别人的B棋子
                        {
                            if (Player->B.chess_place.SNj == tmpj)
                            {
                                Player->B.chess_place.SNj = Player->startj;
                                Player->B.chess_place.SNi = Player->starti;
                                Board[Player->starti][Player->startj] = Player->ID;
                            }
                        }
                        if (Player->C.chess_place.SNi == tmpi)//有没有踩到别人的C棋子
                        {
                            if (Player->C.chess_place.SNj == tmpj)
                            {
                                Player->C.chess_place.SNj = Player->startj;
                                Player->C.chess_place.SNi = Player->starti;
                                Board[Player->starti][Player->startj] = Player->ID;
                            }
                        }
                        if (Player->D.chess_place.SNi == tmpi)//有没有踩到别人的D棋子
                        {
                            if (Player->D.chess_place.SNj == tmpj)
                            {
                                Player->D.chess_place.SNj = Player->startj;
                                Player->D.chess_place.SNi = Player->starti;
                                Board[Player->starti][Player->startj] = Player->ID;
                            }
                        }
                    }
                    Board[movechess->chess_place.SNi][movechess->chess_place.SNj] = Player->ID;//修改3
                    if (movechess->chess_place.SNj == 12)//修改4
                    {
                        Player->approched++;
                        movechess->arrived = 1;
                    }
                    return 0;
            }
            return 0;
    }
}
#endif //UNTITLED1_FUNCTIONS_H
