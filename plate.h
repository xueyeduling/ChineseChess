#ifndef PLATE_H
#define PLATE_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QPalette>
#include <QPixmap>
#include <cmath>
#include <QIcon>
#include <QRect>
#include <QMouseEvent>
#include <QList>
#include "piece.h"

class Step: public QObject
{
public:
    int moveId;
    int killId;
    int moveRow;
    int moveCol;
    int targetRow;
    int targetCol;
};

class AI;

class Plate : public QWidget
{
    Q_OBJECT
public:
    explicit Plate(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    int selectid;
    int d;
    QPoint off;
    bool redTure; // true红走，false黑走

    Piece pieces[32];

    // 冗余数据结构
    // 表示棋盘中每一个点，-1表示该点没有棋子，0-31表示棋子的id
    // 方便通过坐标值找到棋子ID
    char ps[10][9];

    // 走棋记录，用于悔棋
    QList<Step*> listStep;

    AI * ai;

    int isWin;

    void initGame();

    void drawCross(int row, int col, QPainter &p);

    bool canMove(int moveId, int killId, int  targetRow, int  targetCol);

    // 返回-1表示两个点不在一条直线上
    // 返回非负数表示两点之间棋子数
    int getPieceCount(int row1, int col1, int row2, int col2);

    bool isMeet(int moveId, int targetCol);

    void move(int moveId, int killId, int targetRow, int targetCol);

    void moveBack();

    void addStep(int moveId, int killId, int targetRow, int targetCol);
signals:

public slots:
};

#endif // PLATE_H
