#include "mainwindow.h"
#include"prepare.h"


#include <QApplication>
#include <QTextEdit>

player* RED;
player* YELLOW;
player* GREEN;
player* BLUE;

chess* RED_A;
chess* RED_B;
chess* RED_C;
chess* RED_D;

chess* BLUE_A;
chess* BLUE_B;
chess* BLUE_C;
chess* BLUE_D;

chess* GREEN_A;
chess* GREEN_B;
chess* GREEN_C;
chess* GREEN_D;

chess* YELLOW_A;
chess* YELLOW_B;
chess* YELLOW_C;
chess* YELLOW_D;

player*Player;

int ROUND_AMOUNT;

char Board[14][14];

int dicepoint;


int main(int argc, char *argv[])
{
    RED=(player*) malloc(sizeof (player));//写一半才想到能用RWBY致敬一下，然而懒，先申请内存
    YELLOW=(player*) malloc(sizeof (player));
    GREEN=(player*) malloc(sizeof (player));
    BLUE=(player*) malloc(sizeof (player));

    Player=RED;//初始化阶段

    RED->next=BLUE;//轮流关系
    BLUE->next=GREEN;
    GREEN->next=YELLOW;
    YELLOW->next=RED;
    for(int i=0;i<4;i++,Player=Player->next)//4个还没出发
    {
        Player->approched=0;
        Player->unstart=4;
        Player->A.arrived=0;//每个棋子都没有到达
        Player->B.arrived=0;
        Player->C.arrived=0;
        Player->D.arrived=0;
    }
    RED->ID='R';YELLOW->ID='Y';GREEN->ID='G';BLUE->ID='B';//名字
    RED->starti=3;RED->startj=4;//出发点
    BLUE->starti=8;BLUE->startj=3;//j是横坐标,i是纵坐标
    GREEN->starti=9;GREEN->startj=8;
    YELLOW->starti=4;YELLOW->startj=9;

    for(int i=0;i<13;i++)//初始化棋盘
    {
        for(int j=0;j<13;j++)
        {Board[i][j]=' ';}
    }

    Board[2][2]='R';Board[2][3]='R';Board[3][2]='R';Board[3][3]='R';Board[3][4]='O';
    Board[2][9]='Y';Board[2][10]='Y';Board[3][9]='Y';Board[3][10]='Y';Board[4][9]='O';
    Board[9][9]='G';Board[9][10]='G';Board[10][9]='G';Board[10][10]='G';Board[9][8]='O';
    Board[9][2]='B';Board[9][3]='B';Board[10][2]='B';Board[10][3]='B';Board[8][3]='O';

    Board[4][4]='O';Board[5][4]='O';Board[6][4]='O';Board[7][4]='O';
    Board[8][4]='O';Board[8][5]='O';Board[8][6]='O';Board[8][7]='O';
    Board[8][8]='O';Board[7][8]='O';Board[6][8]='O';Board[5][8]='O';
    Board[4][8]='O';Board[4][7]='O';Board[4][6]='O';Board[4][5]='O';

    Board[0][6]='O';Board[1][6]='O';Board[2][6]='O';Board[3][6]='O';
    Board[9][6]='O';Board[10][6]='O';Board[11][6]='O';Board[12][6]='O';
    Board[6][0]='O';Board[6][1]='O';Board[6][2]='O';Board[6][3]='O';
    Board[6][9]='O';Board[6][10]='O';Board[6][11]='O';Board[6][12]='O';

    RED->A.chess_place.SNj=2;RED->A.chess_place.SNi=2;//初始化棋子位置
    RED->B.chess_place.SNj=2;RED->B.chess_place.SNi=3;
    RED->C.chess_place.SNj=3;RED->C.chess_place.SNi=2;
    RED->D.chess_place.SNj=3;RED->D.chess_place.SNi=3;

    BLUE->A.chess_place.SNj=2;BLUE->A.chess_place.SNi=9;
    BLUE->B.chess_place.SNj=2;BLUE->B.chess_place.SNi=10;
    BLUE->C.chess_place.SNj=3;BLUE->C.chess_place.SNi=9;
    BLUE->D.chess_place.SNj=3;BLUE->D.chess_place.SNi=10;

    GREEN->A.chess_place.SNj=9;GREEN->A.chess_place.SNi=9;
    GREEN->B.chess_place.SNj=9;GREEN->B.chess_place.SNi=10;
    GREEN->C.chess_place.SNj=10;GREEN->C.chess_place.SNi=9;
    GREEN->D.chess_place.SNj=10;GREEN->D.chess_place.SNi=10;

    YELLOW->A.chess_place.SNj=9;YELLOW->A.chess_place.SNi=2;
    YELLOW->B.chess_place.SNj=10;YELLOW->B.chess_place.SNi=3;
    YELLOW->C.chess_place.SNj=9;YELLOW->C.chess_place.SNi=2;
    YELLOW->D.chess_place.SNj=10;YELLOW->D.chess_place.SNi=3;

    RED->A.start=0;RED->B.start=0;RED->C.start=0;RED->D.start=0;
    BLUE->A.start=0;BLUE->B.start=0;BLUE->C.start=0;BLUE->D.start=0;
    GREEN->A.start=0;GREEN->B.start=0;GREEN->C.start=0;GREEN->D.start=0;
    YELLOW->A.start=0;YELLOW->B.start=0;YELLOW->C.start=0;YELLOW->D.start=0;

    RED->A.ID='A';RED->B.ID='B';RED->C.ID='C';RED->D.ID='D';
    BLUE->A.ID='A';BLUE->B.ID='B';BLUE->C.ID='C';BLUE->D.ID='D';
    GREEN->A.ID='A';GREEN->B.ID='B';GREEN->C.ID='C';GREEN->D.ID='D';
    YELLOW->A.ID='A';YELLOW->B.ID='B';YELLOW->C.ID='C';YELLOW->D.ID='D';


    RED_A=&(RED->A);
    RED_B=&(RED->B);
    RED_C=&(RED->C);
    RED_D=&(RED->D);
    RED_A->next=RED_B;
    RED_B->next=RED_C;
    RED_C->next=RED_D;
    RED_D->next=RED_A;

    BLUE_A=&(BLUE->A);
    BLUE_B=&(BLUE->B);
    BLUE_C=&(BLUE->C);
    BLUE_D=&(BLUE->D);
    BLUE_A->next=BLUE_B;
    BLUE_B->next=BLUE_C;
    BLUE_C->next=BLUE_D;
    BLUE_D->next=BLUE_A;

    GREEN_A=&(GREEN->A);
    GREEN_B=&(GREEN->B);
    GREEN_C=&(GREEN->C);
    GREEN_D=&(GREEN->D);
    GREEN_A->next=GREEN_B;
    GREEN_B->next=GREEN_C;
    GREEN_C->next=GREEN_D;
    GREEN_D->next=GREEN_A;

    YELLOW_A=&(YELLOW->A);
    YELLOW_B=&(YELLOW->B);
    YELLOW_C=&(YELLOW->C);
    YELLOW_D=&(YELLOW->D);
    YELLOW_A->next=YELLOW_B;
    YELLOW_B->next=YELLOW_C;
    YELLOW_C->next=YELLOW_D;
    YELLOW_D->next=YELLOW_A;



    QApplication a(argc, argv);
    MainWindow w;



    w.show();
    return a.exec();
}
