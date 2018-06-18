#include "AI.h"
#define KINGVALUE 1000

//Rooks,Mao,Elephants,Mandarins,King,Pao,Pawns
//static int score[] = {90, 45, 25, 25, 2000, 50, 10};

#define INFINITE 10000
#define LEAVEL 4

AI::AI(QWidget *parent):Plate(parent)
{
    isRed = true;
}

// 获取对方走棋后的局面最小值
int AI::getMinScore(int level, int curBest)
{
    if(!level)
        return eval();
    // 列出所有的移动方法
    QList<Step*> steps;
    Step *step = NULL;
    getAllPossibleMove(steps);

    int minValue = INFINITE;

    // 移动每一种可能，评估分数
    for(auto beg = steps.begin(); beg != steps.end(); ++beg)
    {
        step= *beg;

        // 移动
        move(step->moveId,step->killId, step->targetRow, step->targetCol);

        // 评估
        //int value = eval();

        // 吃王
        if(eval() <= -KINGVALUE)
        {
            // 先获取最小值，然后返回
            minValue = eval();
            moveBack();
            break;
        }

        int value = getMaxScore(level - 1, minValue);

        // 返回
        moveBack();

        // 如果小于传入的值，立即返回
        if(value <= curBest)
        {
            minValue = value;
            break;
        }
        if(value < minValue)
            minValue = value;
    }

    // 释放所有资源
    for(auto beg = steps.begin(); beg != steps.end(); ++beg)
        delete *beg;

    // 记录分数最大的走法，返回这个走法
    return minValue;
}

// 获取自己走棋后的局面最大值
int AI::getMaxScore(int level, int curBest)
{
    if(!level)
        return eval();
    // 列出所有的移动方法
    QList<Step*> steps;
    Step *step = NULL;
    getAllPossibleMove(steps);

    int maxValue = -INFINITE;

    // 移动每一种可能，评估分数
    for(auto beg = steps.begin(); beg != steps.end(); ++beg)
    {
        step= *beg;

        // 移动
        move(step->moveId,step->killId, step->targetRow, step->targetCol);

        // 评估
        //int value = eval();

        // 吃王
        if(eval() >= KINGVALUE)
        {
            // 先获取最大值，然后返回
            maxValue = eval();
            moveBack();
            break;
        }

        int value = getMinScore(level - 1, maxValue);

        // 返回
        moveBack();

        // 如果大于传入的值，立即返回
        if(value >= curBest)
        {
            maxValue = value;
            break;
        }
        if(value > maxValue)
            maxValue = value;
    }

    // 释放所有资源
    for(auto beg = steps.begin(); beg != steps.end(); ++beg)
        delete *beg;

    // 记录分数最大的走法，返回这个走法r
    return maxValue;
}

// 添加步骤
bool AI::addSteps(int moveid, int targetRow, int targetCol, QList<Step *> &steps)
{
    int killid = ps[targetRow][targetCol];
    if(killid != -1 && pieces[killid].isBlack() == pieces[moveid].isBlack())
        return false;
    if(!canMove(moveid, killid, targetRow, targetCol))
        return false;

    Step *step = new Step;
    step->moveId = moveid;
    step->killId = killid;
    step->moveRow = pieces[moveid].row;
    step->moveCol = pieces[moveid].col;
    step->targetRow = targetRow;
    step->targetCol = targetCol;

    steps.append(step);
    return true;
}

// 电脑走的下一步棋
Step *AI::getNextStep()
{
    // 列出所有的移动方法
    QList<Step*> steps;
    Step *step = NULL;
    Step* best = NULL;
    getAllPossibleMove(steps);

    int maxValue = -INFINITE;

    // 移动每一种可能，评估分数
    for(auto beg = steps.begin(); beg != steps.end(); ++beg)
    {
        step= *beg;

        // 移动
        move(step->moveId,step->killId, step->targetRow, step->targetCol);

        // 评估
        //int value = eval();

        // 吃王
        if(eval() >= KINGVALUE)
        {
            // 返回
            maxValue = eval();
            moveBack();
            if(best) delete best;
            best = step;
            while(++beg != steps.end())
                delete *beg;
            break;
        }

        int value = getMinScore(LEAVEL - 1, maxValue);

        // 返回
        moveBack();
        if(value > maxValue)
        {
            if(best) delete best;
            maxValue = value;
            best = step;
        }
        else
            delete step;
    }

    if(maxValue <= -KINGVALUE)
        isWin = 1;
    if(maxValue >= KINGVALUE)
        isWin = -1;

    // 记录分数最大的走法，返回这个走法
    return best;
}

// 局面评估
int AI::eval()
{
    return countValue;
}

// 获取所有可能的步骤
// 大概每个局面有45种走法
void AI::getAllPossibleMove(QList<Step *> &steps)
{
    int min = 0, max = 16;
    if(redTure)
        min = 16, max = 32;
    for(int moveid = min; moveid < max; ++moveid)
    {
        // bool color = pieces[moveid].isBlack();
        if(pieces[moveid].killed) continue;

        // 车
        if(pieces[moveid].type == Rooks)
        {
            int rowFrom = pieces[moveid].row;
            int colFrom = pieces[moveid].col;

            // 向左走
            for(int col = colFrom - 1; col >= 0 ; --col)
            {
                if(!addSteps(moveid, rowFrom, col, steps))
                    break;
            }
            // 向右走
            for(int col = colFrom + 1; col <= 8 ; ++col)
            {
                if(!addSteps(moveid, rowFrom, col, steps))
                    break;
            }
            // 向上
            for(int row = rowFrom - 1; row >= 0 ; --row)
            {
                if(!addSteps(moveid, row, colFrom, steps))
                    break;
            }
            // 向下走
            for(int row = rowFrom + 1; row <= 9 ; ++row)
            {
                if(!addSteps(moveid, row, colFrom, steps))
                    break;
            }
        }
        // 马
        else if(pieces[moveid].type == Mao)
        {
            int rowFrom = pieces[moveid].row;
            int colFrom = pieces[moveid].col;

            // 辅助数据结构，表示相对位移量
            struct {
                int dx;
                int dy;
            } offs[8] = {
            {1, 2},
            {2, 1},
            {-1, 2},
            {-2, 1},
            {1, -2},
            {2, -1},
            {-1, -2},
            {-2, -1}
        };

            for(int i = 0; i < 8; ++i)
            {
                int row = rowFrom + offs[i].dx;
                int col = colFrom + offs[i].dy;

                if(row < 0 || row > 9 || col < 0 || col >8)
                    continue;
                addSteps(moveid, row, col, steps);
            }
        }
        // 象
        else if(pieces[moveid].type == Elephants)
        {
            int rowFrom = pieces[moveid].row;
            int colFrom = pieces[moveid].col;

            // 辅助数据结构，表示相对位移量
            struct {
                int dx;
                int dy;
            } offs[4] = {
            {2, 2},
            {2, -2},
            {-2, 2},
            {-2, -2}
        };

            for(int i = 0; i < 4; ++i)
            {
                int row = rowFrom + offs[i].dx;
                int col = colFrom + offs[i].dy;

                if(row < 0 || row > 9 || col < 0 || col >8)
                    continue;
                addSteps(moveid, row, col, steps);
            }
        }
        // 士
        else if(pieces[moveid].type == Mandarins)
        {
            int rowFrom = pieces[moveid].row;
            int colFrom = pieces[moveid].col;

            // 辅助数据结构，表示相对位移量
            struct {
                int dx;
                int dy;
            } offs[4] = {
            {1, 1},
            {1, -1},
            {-1, 1},
            {-1, -1}
        };

            for(int i = 0; i < 4; ++i)
            {
                int row = rowFrom + offs[i].dx;
                int col = colFrom + offs[i].dy;

                if(row < 0 || row > 9 || col < 0 || col >8)
                    continue;
                addSteps(moveid, row, col, steps);
            }
        }
        // 王
        else if(pieces[moveid].type == King)
        {
            int rowFrom = pieces[moveid].row;
            int colFrom = pieces[moveid].col;

            // 辅助数据结构，表示相对位移量
            struct {
                int dx;
                int dy;
            } offs[4] = {
            {1, 0},
            {-1, 0},
            {0, 1},
            {0, -1}
        };

            for(int i = 0; i < 4; ++i)
            {
                int row = rowFrom + offs[i].dx;
                int col = colFrom + offs[i].dy;

                if(row < 0 || row > 9 || col < 0 || col >8)
                    continue;
                addSteps(moveid, row, col, steps);
            }
        }
        // 炮
        else if(pieces[moveid].type == Pao)
        {
            int rowFrom = pieces[moveid].row;
            int colFrom = pieces[moveid].col;

            // 向左走
            for(int col = colFrom - 1; col >= 0 ; --col)
            {
                addSteps(moveid, rowFrom, col, steps);
            }
            // 向右走
            for(int col = colFrom + 1; col <= 8 ; ++col)
            {
                addSteps(moveid, rowFrom, col, steps);
            }
            // 向上
            for(int row = rowFrom - 1; row >= 0 ; --row)
            {
                addSteps(moveid, row, colFrom, steps);
            }
            // 向下走
            for(int row = rowFrom + 1; row <= 9 ; ++row)
            {
                addSteps(moveid, row, colFrom, steps);
            }
        }
        // 兵
        else if(pieces[moveid].type == Pawns)
        {
            int rowFrom = pieces[moveid].row;
            int colFrom = pieces[moveid].col;

            // 辅助数据结构，表示相对位移量
            struct {
                int dx;
                int dy;
            } offs[4] = {
            {1, 0},
            {-1, 0},
            {0, 1},
            {0, -1}
        };

            for(int i = 0; i < 4; ++i)
            {
                int row = rowFrom + offs[i].dx;
                int col = colFrom + offs[i].dy;

                if(row < 0 || row > 9 || col < 0 || col >8)
                    continue;
                addSteps(moveid, row, col, steps);
            }
        }
    }
}

void AI::click(int clickid, int row, int col)
{
    Plate::click(clickid, row, col);

    QTimer::singleShot(100, [&](){ // 启用0.1秒计时器，0.1秒后，电脑再思考
            if(!redTure)
            {
                otherMove();
            }
        });
}

// 移动棋子
void AI::otherMove()
{
    Step *step = getNextStep();
    if(isWin == 1)
    {
        delete step;
        /*QMessageBox message(QMessageBox::NoIcon, "Title", "Content with icon.");
                    message.setIconPixmap(QPixmap("icon.png"));
                    message.exec();*/
        QMessageBox::about(this, "胜利", "胜利      ");
        return;
    }
    move(step->moveId, step->killId, step->targetRow, step->targetCol);
    update();
    if(isWin == -1)
    {
        /*QMessageBox message(QMessageBox::NoIcon, "Title", "Content with icon.");
                    message.setIconPixmap(QPixmap("icon.png"));
                    message.exec();*/
        QMessageBox::about(this, "失败", "失败      ");
        //QMessageBox::information(NULL, "失败", "失败");
    }
    delete step;
}

// 统计分数
void AI::AddUpValue(bool isBack, int value)
{
    if(!isBack)
        countValue += value;
    else
        countValue -= value;
}

