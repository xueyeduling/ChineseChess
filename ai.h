#ifndef AI_H
#define AI_H

#include <QList>
#include "Plate.h"
#include <QPair>
#include <QMessageBox.h>

class AI : public Plate
{
public:
    AI(QWidget *parent = 0);

    // 电脑走的下一步棋
    Step *getNextStep();

    // 局面评估
    int eval();

    // 获取所有可能的步骤
    void getAllPossibleMove(QList<Step*> &steps);

    // 获取对方走棋后的局面最小值
    int getMinScore(int level, int curBest);

    // 获取自己走棋后的局面最大值
    int getMaxScore(int level, int curBest);

    // 添加步骤
    bool addSteps(int moveid, int targetRow, int targetCol, QList<Step*> &steps);

    // 处理点击
    virtual void click(int clickid, int row, int col);

    // 移动棋子
    void otherMove();

    // 计分
    virtual void AddUpValue(bool isBack, int value);

};

#endif // AI_H
