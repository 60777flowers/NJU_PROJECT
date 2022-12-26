#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "prepare.h"
#include <QProcess>
#include <QPushButton>


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

extern int ROUND_AMOUNT;

extern int dicepoint;

extern player*Player;

chess* movechess;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Board = ui->Board;  // 关联QTextEdit的指针与ui中的QTextEdit对象
    //Board->setReadOnly(true);

    ui->move_A->setEnabled(false);//先让按钮无法点击
    ui->move_B->setEnabled(false);
    ui->move_C->setEnabled(false);
    ui->move_D->setEnabled(false);
    ui->newchess->setEnabled(false);
    ui->getdieres_button->setEnabled(false);



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



}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_reboot_button_clicked()
{
    // 启动新的进程
    QProcess::startDetached(QApplication::applicationFilePath());
    // 终止当前进程
    QApplication::exit();
}


void MainWindow::on_getdieres_button_clicked()
{
    ui->message->setText("");

    switch (Player->ID)//由于骰子是万物起源，所以判断放在这里来做
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


    srand(time(0));  // 使用当前时间作为种子初始化随机数生成器
                dicepoint = rand() % 6+1;  // 生成 1~6 之间的随机数
                ui->Point_text->clear();
                ui->Point_text->setText(QString::number(dicepoint));
                if(dicepoint==6)//出发许可
                {
                    if(Player->unstart>0)
                    {
                        ui->getdieres_button->setEnabled(false);//先让骰子不能用
                        ui->newchess->setEnabled(true);//再让走
                        ui->message->setText("你可以出发一个棋子\n");
                    }
                }

                if((Player->unstart+Player->approched)==4&&dicepoint!=6)
                {
                    //这里不需要无效化骰子
                    Player=Player->next;
                    ROUND_AMOUNT++;
                    ui->ROUND_text->setText(QString::number(ROUND_AMOUNT));
                    ui->message->setText("你的回合结束，下一名玩家的回合开始辣\n");
                    ui->now_player_text->setText(QString(Player->ID));
                    //ui->Point_text->setText("");
                }
                else
                {
                    ui->getdieres_button->setEnabled(false);//先让骰子不能用
                    if(Player->A.start&&!(Player->A.arrived))
                    {ui->move_A->setEnabled(true);}//再让按钮可以点击
                    if(Player->B.start&&!(Player->B.arrived))
                    ui->move_B->setEnabled(true);
                    if(Player->C.start&&!(Player->C.arrived))
                    ui->move_C->setEnabled(true);
                    if(Player->D.start&&!(Player->D.arrived))
                    ui->move_D->setEnabled(true);
                    ui->message->setText("请选择可移动棋子\n");
                    if(Player->A.start&&!(Player->A.arrived))
                    {ui->message->append(QString("A (%2,%3)").arg(Player->A.chess_place.SNj).arg(Player->A.chess_place.SNi));}
                    if(Player->B.start&&!(Player->B.arrived))
                    {ui->message->append(QString("B (%2,%3)").arg(Player->B.chess_place.SNj).arg(Player->B.chess_place.SNi));}
                    if(Player->C.start&&!(Player->C.arrived))
                    {ui->message->append(QString("C (%2,%3)").arg(Player->C.chess_place.SNj).arg(Player->C.chess_place.SNi));}
                    if(Player->D.start&&!(Player->D.arrived))
                    {ui->message->append(QString("D (%2,%3)").arg(Player->D.chess_place.SNj).arg(Player->D.chess_place.SNi));}
                }
}


void MainWindow::on_newchess_clicked()
{
    ui->Point_text->setText("");

    switch (Player->unstart)//先是出发
                {
                    case 4:
                        Board[Player->A.chess_place.SNi][Player->A.chess_place.SNj]='O';
                        Player->A.chess_place.SNj=Player->startj;Player->A.chess_place.SNi=Player->starti;
                        Board[Player->A.chess_place.SNi][Player->A.chess_place.SNj]=Player->ID;
                        Player->unstart--;
                        Player->A.start=1;
                        ui->message->setText("你的A棋子出发辣！");
                        break;
                    case 3:
                        Board[Player->B.chess_place.SNi][Player->B.chess_place.SNj]='O';
                        Player->B.chess_place.SNj=Player->startj;Player->B.chess_place.SNi=Player->starti;
                        Board[Player->B.chess_place.SNi][Player->B.chess_place.SNj]=Player->ID;
                        Player->unstart--;
                        Player->B.start=1;
                        ui->message->setText("你的B棋子出发辣！");
                        break;
                    case 2:
                        Board[Player->C.chess_place.SNi][Player->C.chess_place.SNj]='O';
                        Player->C.chess_place.SNj=Player->startj;Player->C.chess_place.SNi=Player->starti;
                        Board[Player->C.chess_place.SNi][Player->C.chess_place.SNj]=Player->ID;
                        Player->unstart--;
                        Player->C.start=1;
                        ui->message->setText("你的C棋子出发辣！");
                        break;
                    case 1:
                        Board[Player->D.chess_place.SNi][Player->D.chess_place.SNj]='O';
                        Player->D.chess_place.SNj=Player->startj;Player->D.chess_place.SNi=Player->starti;
                        Board[Player->D.chess_place.SNi][Player->D.chess_place.SNj]=Player->ID;
                        Player->unstart--;
                        Player->D.start=1;
                        ui->message->setText("你的D棋子出发辣！");
                    break;
                }

//..............固定部分............

    QString outputboard;
        for (int i = 0; i < 13; i++)
        {
              for (int j = 0; j < 13; j++)
              {
                  if(Board[i][j]!=' ')
                    {outputboard += Board[i][j];}
                  else
                    {
                        outputboard+="+";
                        if((i!=0||j!=5)&&(i!=1||j!=5)&&(i!=11||j!=5)&&(i!=12||j!=5)&&(i!=5||j!=7)&&(i!=7||j!=7))
                        outputboard+=" ";
                    }
              }
              outputboard += '\n';
        }
        outputboard += '\0';
        ui->Board->setText(outputboard);

        ui->move_A->setEnabled(false);//先让按钮无法点击
        ui->move_B->setEnabled(false);
        ui->move_C->setEnabled(false);
        ui->move_D->setEnabled(false);
        ui->newchess->setEnabled(false);

        ui->getdieres_button->setEnabled(true);

        //最后是每次都要修改的回合，玩家名，变换玩家
        ROUND_AMOUNT++;
        ui->ROUND_text->setText(QString::number(ROUND_AMOUNT));
        ui->message->setText("你的回合结束，下一名玩家的回合开始辣\n");
        Player=Player->next;
        ui->now_player_text->setText(QString(Player->ID));

//..............固定部分............
}


void MainWindow::on_move_A_clicked()//移动棋子A
{

    //失败的记录，qt是傻逼，bi~~~~~~~
    //chess* a=movechess->next;
    //char b=a->ID;
    //ui->DEBUG1->setText(QString(movechess->next->ID));

        int tmpi;
        int tmpj;//判断一下会不会踩掉以及有没有重叠
        tmpi=movechess->chess_place.SNi;
        tmpj=movechess->chess_place.SNj;


        /*if (Player->B.chess_place.SNi == tmpi)//有没有踩到自己的B棋子
        {
            if (Player->B.chess_place.SNj == tmpj)
            {
                Board[Player->A.chess_place.SNi][Player->A.chess_place.SNj] = Player->ID;
            }
        }
        if (Player->C.chess_place.SNi == tmpi)//有没有踩到自己的C棋子
        {
            if (Player->C.chess_place.SNj == tmpj)
            {
                Board[Player->A.chess_place.SNi][Player->A.chess_place.SNj] = Player->ID;
            }
        }
        if (Player->D.chess_place.SNi == tmpi)//有没有踩到自己的D棋子
        {
            if (Player->D.chess_place.SNj == tmpj)
            {
                Board[Player->A.chess_place.SNi][Player->A.chess_place.SNj] = Player->ID;
            }
        }*/

        Board[movechess->chess_place.SNi][movechess->chess_place.SNj] = 'O';
        movechess = movechess->next;
        for (int k = 0; k < 3; k++)//重叠判断
         {
             if (tmpj == movechess->chess_place.SNj && tmpi == movechess->chess_place.SNi) {
                 Board[movechess->chess_place.SNi][movechess->chess_place.SNj] = Player->ID;
             }
             movechess = movechess->next;
         }



        int count=dicepoint;
        //ui->DEBUG1->setText(QString(Player->ID));
        //ui->DEBUG1->setText(QString::number(movechess->chess_place.SNi));


        switch (Player->ID)
        {
                    case 'R':


                               while (movechess->chess_place.SNj == 4 && movechess->chess_place.SNi < 8 && count > 0)//公共棋盘部分的移动
                                {
                                    count--;
                                    movechess->chess_place.SNi++;
                                }
                                while (movechess->chess_place.SNi == 8 && movechess->chess_place.SNj < 8 && count > 0)
                                {
                                    count--;
                                    movechess->chess_place.SNj++;
                                }
                                while (movechess->chess_place.SNj == 8 && movechess->chess_place.SNi > 4 && count > 0)//公共棋盘部分的移动
                                {
                                    count--;
                                    movechess->chess_place.SNi--;
                                }
                                while (movechess->chess_place.SNi == 4 && movechess->chess_place.SNj > 6 && count > 0)
                                {
                                    count--;
                                    movechess->chess_place.SNj--;
                                }
                                while (count > 0)
                                {
                                    movechess->chess_place.SNi--;
                                    count--;
                                    if (movechess->chess_place.SNi == 0) { break; }
                                }
                                while (count > 0)
                                {
                                    movechess->chess_place.SNi++;
                                    count--;
                                    if (movechess->chess_place.SNi == 4) { break; }
                                }
                                while (count > 0)
                                {
                                    movechess->chess_place.SNi--;
                                    count--;
                                }
                                //printf("DEBUG3\n");
                                //printf("Now %c is at (%d,%d)\n", movechess->ID, movechess->chess_place.SNj,movechess->chess_place.SNi);
        //Qt 修改2：printf全部转到message里面去
                                ui->message->append(QString("Now %1 is at (%2,%3)").arg(movechess->ID).arg(movechess->chess_place.SNj).arg(movechess->chess_place.SNi));

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

                                Board[movechess->chess_place.SNi][movechess->chess_place.SNj] = 'R';
                                if (movechess->chess_place.SNi == 0)
                                {
                                    Player->approched++;
                                    movechess->arrived = 1;
                                }
                                break;
//.............................................................................................................................................................//
                case 'B':


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
                                //printf("Now %c is at (%d,%d)\n", movechess->ID, movechess->chess_place.SNj,movechess->chess_place.SNi);
                    //Qt 修改2：printf全部转到message里面去
                                ui->message->append(QString("Now %1 is at (%2,%3)").arg(movechess->ID).arg(movechess->chess_place.SNj).arg(movechess->chess_place.SNi));

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

                                Board[movechess->chess_place.SNi][movechess->chess_place.SNj] = 'B';
                                if (movechess->chess_place.SNi == 0)
                                {
                                    Player->approched++;
                                    movechess->arrived = 1;
                                }
                                break;
//...................................................................................................................................................................//
        case 'G':


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
                        //printf("DEBUG3\n");
                        //printf("Now %c is at (%d,%d)\n", movechess->ID, movechess->chess_place.SNj,movechess->chess_place.SNi);
            //Qt 修改2：printf全部转到message里面去
                        ui->message->append(QString("Now %1 is at (%2,%3)").arg(movechess->ID).arg(movechess->chess_place.SNj).arg(movechess->chess_place.SNi));

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

                        Board[movechess->chess_place.SNi][movechess->chess_place.SNj] = 'G';
                        if (movechess->chess_place.SNi == 0)
                        {
                            Player->approched++;
                            movechess->arrived = 1;
                        }
                        break;
 //..................................................................................................................................................................//
        case 'Y':


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
                        //printf("Now %c is at (%d,%d)\n", movechess->ID, movechess->chess_place.SNj,movechess->chess_place.SNi);
            //Qt 修改2：printf全部转到message里面去
                        ui->message->append(QString("Now %1 is at (%2,%3)").arg(movechess->ID).arg(movechess->chess_place.SNj).arg(movechess->chess_place.SNi));

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

                        Board[movechess->chess_place.SNi][movechess->chess_place.SNj] = 'Y';
                        if (movechess->chess_place.SNi == 0)
                        {
                            Player->approched++;
                            movechess->arrived = 1;
                        }
                        break;
    }
        //..............固定部分............

            QString outputboard;
                for (int i = 0; i < 13; i++)
                {
                      for (int j = 0; j < 13; j++)
                      {
                          if(Board[i][j]!=' ')
                            {outputboard += Board[i][j];}
                          else
                            {
                                outputboard+="+";
                                if((i!=0||j!=5)&&(i!=1||j!=5)&&(i!=11||j!=5)&&(i!=12||j!=5)&&(i!=5||j!=7)&&(i!=7||j!=7))
                                outputboard+=" ";
                            }
                      }
                      outputboard += '\n';
                }
                outputboard += '\0';
                ui->Board->setText(outputboard);
                if(RED->approched<4&&YELLOW->approched<4&&GREEN->approched<4&&BLUE->approched<4)
                {
                    ui->move_A->setEnabled(false);//先让按钮无法点击
                    ui->move_B->setEnabled(false);
                    ui->move_C->setEnabled(false);
                    ui->move_D->setEnabled(false);
                    ui->newchess->setEnabled(false);

                    ui->getdieres_button->setEnabled(true);

                    //最后是每次都要修改的回合，玩家名，变换玩家
                    ROUND_AMOUNT++;
                    ui->ROUND_text->setText(QString::number(ROUND_AMOUNT));
                    //ui->message->setText("你的回合结束，下一名玩家的回合开始辣\n");
                    Player=Player->next;
                    ui->now_player_text->setText(QString(Player->ID));
                }
                else
                {
                    ui->move_A->setEnabled(false);//先让按钮无法点击
                    ui->move_B->setEnabled(false);
                    ui->move_C->setEnabled(false);
                    ui->move_D->setEnabled(false);
                    ui->newchess->setEnabled(false);

                    ui->getdieres_button->setEnabled(false);
                    ui->message->append(QString("游戏结束，获胜的是：%1").arg(movechess->ID));

                }

        //..............固定部分............

}


void MainWindow::on_move_B_clicked()
{
    movechess=movechess->next;
    ui->move_A->click();
}

void MainWindow::on_move_C_clicked()
{
    movechess=movechess->next;
    ui->move_A->click();
}

void MainWindow::on_move_D_clicked()
{
    movechess=movechess->next;
    ui->move_A->click();
}



void MainWindow::on_pushButton_clicked()
{

    ui->pushButton->setEnabled(false);
    QString outputboard;
        for (int i = 0; i < 13; i++)
        {
              for (int j = 0; j < 13; j++)
              {
                  if(Board[i][j]!=' ')
                    {outputboard += Board[i][j];}
                  else
                    {
                        outputboard+="+";
                        if((i!=0||j!=5)&&(i!=1||j!=5)&&(i!=11||j!=5)&&(i!=12||j!=5)&&(i!=5||j!=7)&&(i!=7||j!=7))
                        outputboard+=" ";
                    }
              }
              outputboard += '\n';
        }
        outputboard += '\0';
        ui->Board->setText(outputboard);


        ROUND_AMOUNT=1;
        ui->ROUND_text->setText(QString::number(ROUND_AMOUNT));

        ui->now_player_text->setText(QString(Player->ID));

        ui->getdieres_button->setEnabled(true);
}

