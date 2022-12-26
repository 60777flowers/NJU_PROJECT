#ifndef PREPARE_H
#define PREPARE_H


#include <QApplication>
#include <QTextEdit>
#include <QFont>
#include <QFontMetrics>
#include<stdio.h>
#include<stdlib.h>

struct board
{
    int SNj;
    int SNi;
};

struct chess
{
    char ID;
    board chess_place;
    bool start;
    bool arrived;
    chess* next;
};

struct player
{
    char ID;
    chess A;
    chess B;
    chess C;
    chess D;
    int unstart;
    int approched;
    player* next;
    int starti;//出发起始点的坐标
    int startj;
    bool human_gamer;
};

#endif // PREPARE_H
