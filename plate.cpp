#include "Plate.h"

//Rooks,Mao,Elephants,Mandarins,King,Pao,Pawns
static int score[] = {90, 45, 25, 25, 2000, 50, 10};

Plate::Plate(QWidget *parent) : QDialog(parent)
{
    gametype = Choose;

    isRed = true;

    this->setWindowIcon(QIcon(":/Img/log.png"));
    this->setWindowTitle("中国象棋");

    d = 55;
    off = QPoint(270, 50);
    this->setFixedSize(1000, 600);

    // 添加背景图片
    this->setAutoFillBackground(true);
    QPalette palette;
    QPixmap pixmap(":/Img/background.png");
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    this->setPalette(palette);

    // 放置棋子
    initGame();
}

// 绘图事件
void Plate::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.translate(off);

    QPen pen = p.pen();
    pen.setWidth(2);//改变线宽
    p.setPen(pen);

    // x轴-50，使棋盘向左偏移一点
    p.translate(QPoint(-50, 0));

    if(gametype == Single)
    {
        // 悔棋button
        p.setPen(Qt::NoPen); // 不要画笔(没边框)
        // 背景颜色：能悔棋是绿色，不能悔棋是灰色
        p.setBrush(QBrush(listStep.isEmpty()?QColor(Qt::gray):QColor(Qt::darkGreen)));
        QRect rcBtn = QRect(QPoint(500, 100), QPoint(680, 160));
        p.drawRoundRect(rcBtn, 20, 50);
        // 字体颜色：能悔棋是白色，不能悔棋是黑色
        p.setPen(QPen(listStep.isEmpty()?Qt::black:Qt::white));
        p.setFont(QFont("楷体", d/2 - 16, QFont::DemiBold )); // -10让字体变小一点, QFont::DemiBold为半粗体(权重是63)
        p.drawText(rcBtn, "悔  棋", QTextOption(Qt::AlignCenter));

        // 重新开始button
        p.setPen(Qt::NoPen); // 不要画笔(没边框)
        // 背景颜色：能悔棋是绿色，不能悔棋是灰色
        p.setBrush(QBrush(QColor(Qt::darkGreen)));
        rcBtn = QRect(QPoint(500, 200), QPoint(680, 260));
        p.drawRoundRect(rcBtn, 20, 50);
        // 字体颜色：能悔棋是白色，不能悔棋是黑色
        p.setPen(QPen(Qt::white));
        p.setFont(QFont("楷体", d/2 - 16, QFont::DemiBold )); // -10让字体变小一点, QFont::DemiBold为半粗体(权重是63)
        p.drawText(rcBtn, "重新开始", QTextOption(Qt::AlignCenter));
        // 字体颜色恢复黑色，用于画线
        p.setPen(QPen(Qt::black));

        // 重新开始button
        p.setPen(Qt::NoPen); // 不要画笔(没边框)
        // 背景颜色：能悔棋是绿色，不能悔棋是灰色
        p.setBrush(QBrush(QColor(Qt::darkGreen)));
        rcBtn = QRect(QPoint(500, 300), QPoint(680, 360));
        p.drawRoundRect(rcBtn, 20, 50);
        // 字体颜色：能悔棋是白色，不能悔棋是黑色
        p.setPen(QPen(Qt::white));
        p.setFont(QFont("楷体", d/2 - 16, QFont::DemiBold )); // -10让字体变小一点, QFont::DemiBold为半粗体(权重是63)
        p.drawText(rcBtn, "返回菜单", QTextOption(Qt::AlignCenter));
        // 字体颜色恢复黑色，用于画线
        p.setPen(QPen(Qt::black));
    }
    else
    {
        // y轴-50，使棋盘向上偏移一点
        p.translate(QPoint(0, -50));

        // 悔棋button
        p.setPen(Qt::NoPen); // 不要画笔(没边框)
        // 背景颜色：能悔棋是绿色，不能悔棋是灰色
        p.setBrush(QBrush(listStep.isEmpty()?QColor(Qt::gray):QColor(Qt::darkGreen)));
        QRect rcBtn = QRect(QPoint(500, 100), QPoint(680, 160));
        p.drawRoundRect(rcBtn, 20, 50);
        // 字体颜色：能悔棋是白色，不能悔棋是黑色
        p.setPen(QPen(listStep.isEmpty()?Qt::black:Qt::white));
        p.setFont(QFont("楷体", d/2 - 16, QFont::DemiBold )); // -10让字体变小一点, QFont::DemiBold为半粗体(权重是63)
        p.drawText(rcBtn, "悔  棋", QTextOption(Qt::AlignCenter));

        // 重新开始button
        p.setPen(Qt::NoPen); // 不要画笔(没边框)
        // 背景颜色：能悔棋是绿色，不能悔棋是灰色
        p.setBrush(QBrush(QColor(Qt::darkGreen)));
        rcBtn = QRect(QPoint(500, 200), QPoint(680, 260));
        p.drawRoundRect(rcBtn, 20, 50);
        // 字体颜色：能悔棋是白色，不能悔棋是黑色
        p.setPen(QPen(Qt::white));
        p.setFont(QFont("楷体", d/2 - 16, QFont::DemiBold )); // -10让字体变小一点, QFont::DemiBold为半粗体(权重是63)
        p.drawText(rcBtn, "求 和", QTextOption(Qt::AlignCenter));
        // 字体颜色恢复黑色，用于画线
        p.setPen(QPen(Qt::black));

        // 重新开始button
        p.setPen(Qt::NoPen); // 不要画笔(没边框)
        // 背景颜色：能悔棋是绿色，不能悔棋是灰色
        p.setBrush(QBrush(QColor(Qt::darkGreen)));
        rcBtn = QRect(QPoint(500, 300), QPoint(680, 360));
        p.drawRoundRect(rcBtn, 20, 50);
        // 字体颜色：能悔棋是白色，不能悔棋是黑色
        p.setPen(QPen(Qt::white));
        p.setFont(QFont("楷体", d/2 - 16, QFont::DemiBold )); // -10让字体变小一点, QFont::DemiBold为半粗体(权重是63)
        p.drawText(rcBtn, "认 输", QTextOption(Qt::AlignCenter));
        // 字体颜色恢复黑色，用于画线
        p.setPen(QPen(Qt::black));

        // 重新开始button
        p.setPen(Qt::NoPen); // 不要画笔(没边框)
        // 背景颜色：能悔棋是绿色，不能悔棋是灰色
        p.setBrush(QBrush(QColor(Qt::darkGreen)));
        rcBtn = QRect(QPoint(500, 400), QPoint(680, 460));
        p.drawRoundRect(rcBtn, 20, 50);
        // 字体颜色：能悔棋是白色，不能悔棋是黑色
        p.setPen(QPen(Qt::white));
        p.setFont(QFont("楷体", d/2 - 16, QFont::DemiBold )); // -10让字体变小一点, QFont::DemiBold为半粗体(权重是63)
        p.drawText(rcBtn, "返回菜单", QTextOption(Qt::AlignCenter));
        // 字体颜色恢复黑色，用于画线
        p.setPen(QPen(Qt::black));

        // y轴+50，还原Y轴
        p.translate(QPoint(0, 50));
    }

    // 画中间7条横线
    for(int i = 1; i < 9; ++i)
        p.drawLine(QPoint(0, i * d), QPoint(8 * d, i * d));

    pen.setWidth(3);//改变线宽，四周加粗
    p.setPen(pen);
    // 画两边横线
    p.drawLine(QPoint(0, 0), QPoint(8 * d, 0));
    p.drawLine(QPoint(0, 9 * d), QPoint(8 * d, 9 * d));
    // 画两边的竖线
    p.drawLine(QPoint(0 * d, 0), QPoint(0 * d, 9 * d));
    p.drawLine(QPoint(8 * d, 0), QPoint(8 * d, 9 * d));

    pen.setWidth(2);//改变线宽
    p.setPen(pen);

    // 画中间的上半部竖线
    for(int i = 1; i < 8; ++i)
        p.drawLine(QPoint(i * d, 0), QPoint(i * d, 4 * d));

    // 画中间的下半部竖线
    for(int i = 1; i < 8; ++i)
        p.drawLine(QPoint(i * d, 5 * d), QPoint(i * d, 9 * d));

    // 上半部九宫格
    p.drawLine(QPoint(3 * d, 0), QPoint(5 * d, 2 * d));
    p.drawLine(QPoint(5 * d, 0), QPoint(3 * d, 2 * d));

    // 下半部九宫格
    p.drawLine(QPoint(3 * d, 9 * d), QPoint(5 * d, 7 * d));
    p.drawLine(QPoint(5 * d, 9 * d), QPoint(3 * d, 7 * d));

    // 上半部两个炮的花格
    drawCross(2, 1, p);
    drawCross(2, 7, p);
    // 上半部五个兵的花格
    drawCross(3, 0, p);
    drawCross(3, 2, p);
    drawCross(3, 4, p);
    drawCross(3, 6, p);
    drawCross(3, 8, p);

    // 下半部两个炮的花格
    drawCross(7, 1, p);
    drawCross(7, 7, p);
    // 下半部五个兵的花格
    drawCross(6, 0, p);
    drawCross(6, 2, p);
    drawCross(6, 4, p);
    drawCross(6, 6, p);
    drawCross(6, 8, p);

    // 楚河汉界
    p.setPen(QPen(Qt::darkRed));
    p.setFont(QFont("楷体", d/2 - 10, QFont::DemiBold )); // -10让字体变小一点, QFont::DemiBold为半粗体(权重是63)
    QRect rc = QRect(QPoint(0, d * 4), QPoint(d * 4, d * 5));
    p.drawText(rc, "楚 河", QTextOption(Qt::AlignCenter));
    rc = QRect(QPoint(d * 4, d * 4), QPoint(d * 8, d * 5));
    p.drawText(rc, "汉 界", QTextOption(Qt::AlignCenter));

    // 画棋子
    for ( int i = 0; i < 32; ++i)
    {
        pieces[i].draw(p, d, selectid);
    }
}

// 点击事件
void Plate::mouseReleaseEvent(QMouseEvent *event)
{
    // pt是像数值
    QPoint pt = event->pos();
    pt -= (off - QPoint(50, 0));

    if(gametype == Single)
    {
        //500, 300), QPoint(680, 360
        if(pt.x() > 500 && pt.x() < 680 && pt.y() > 300 && pt.y() < 360)
        {
            gametype = Choose;

            accept();
        }

        // 悔棋按钮
        if(pt.x() > 500 && pt.x() < 680 && pt.y() > 100 && pt.y() < 160)
        {
            if(listStep.isEmpty() || isWin == 1)
                return;

            // 回退两步
            moveBack();
            moveBack();

            isWin = 0;

            update();
            return;
        }

        // 重新开始
        if(pt.x() > 500 && pt.x() < 680 && pt.y() > 200 && pt.y() < 260)
        {
            QMessageBox box(QMessageBox::Question, "重新开始","确定重新对局吗？", QMessageBox::Ok | QMessageBox::Cancel, this);
            box.setButtonText (QMessageBox::Ok,QString("确 定"));
            box.setButtonText (QMessageBox::Cancel,QString("取 消"));
            int ret = box.exec ();
            //int ret = QMessageBox::question(this, "重新开始", "确定重新对局吗？", QMessageBox::Ok,QMessageBox::Cancel).setButtonText(QMessageBox::Ok, "确 定");
            if(ret != QMessageBox::Ok)
                return;

            initGame();

            update();
            return;
        }
    }
    else if(gametype == Server || gametype == Client)
    {
        if(pt.x() > 500 && pt.x() < 680 && pt.y() > 350 && pt.y() < 410)
        {
            gametype = Choose;

            accept();
        }

        // 悔棋按钮
        if(pt.x() > 500 && pt.x() < 680 && pt.y() > 50 && pt.y() < 110)
        {
            if(listStep.isEmpty() || isWin == 1)
                return;

            // 回退两步
            moveBack();
            moveBack();

            isWin = 0;

            update();
            return;
        }
    }

    // 失败或胜利，不能再点击棋子
    if(isWin)
        return;

    // 计算点击点的x，y与象棋中心点的间距
    int xdist = (pt.x() + d/2) % d;
    int ydist = (pt.y() + d/2) % d;

    // 4为棋子直径与格子长宽的差值的一半
    if (xdist < 4 || xdist > (d - 4))
        return;
    if( ydist < 4 || ydist > (d - 4))
        return;

    // pt对应的行列值
    int col = (pt.x() + d/2) / d;
    int row = (pt.y() + d/2) / d;

    // 判断是否点击在棋盘外
    if(col < 0 || col > 8)
        return;
    if(row < 0 || row > 9)
        return;

    int clickid = ps[row][col];

    click(clickid, row, col);
}

// 处理点击
void Plate::click(int clickid, int row, int col)
{
    // 选中
    if(-1 == selectid)
    {
        // 选择棋子
        if(clickid == -1)
        {
            // 点击的位置没有棋子
            return;
        }

        // 是否轮到点击的棋子走棋
        if(redTure == pieces[clickid].isBlack())
            return;
        selectid = clickid;
    }
    // 走棋
    else
    {
        if(clickid != -1)
        {
            // 相同颜色，换选中的棋子
            if(pieces[selectid].isBlack() == pieces[clickid].isBlack())
            {
                selectid = clickid;
                update();
                return;
            }
        }

        // 判断走棋是否符合规则
        if(!canMove(selectid, clickid, row, col))
            return;

        // 移动棋子
        move(selectid, clickid, row, col);
    }
    update();
}

// 初始化棋子
// isRed为true表示执红棋
void Plate::initGame()
{
    // 0表示没有获胜，1表示获胜，-1表示失败
    isWin = 0;

    // 局面分为0
    countValue = 0;

    redTure = true; // 默认红先走

    selectid = -1; // 没有棋子被选中

    for(auto beg = listStep.begin(); beg != listStep.end(); ++beg)
        delete *beg;
    listStep.clear();

    for(int row = 0; row < 10; ++row)
    {
        for(int col = 0; col < 9; ++col)
            ps[row][col] = -1;
    }

    for(int i = 0; i < 32; ++i)
    {
        int j = i > 15 ? i - 16 : i; // 如果大于15为黑棋(列相同)，减16，然后在底下判断行
        pieces[i].id = i;
        pieces[i].killed = false;
        // 第一排与最后一排
        if(j < 9)
        {
            pieces[i].type = (Type)(4-abs(4 - j)); // 第一排计算公式
            pieces[i].row = i > 15 ? 9 : 0;
            pieces[i].col = j;
        }
        // 两个炮
        else if (j < 11)
        {
            pieces[i].type = Pao;
            pieces[i].row = i > 15 ? 7 : 2;
            pieces[i].col = 1 + (j - 9) * 6; // 9在第1列 10在第7列
        }
        // 卒子
        else
        {
            pieces[i].type = Pawns;
            pieces[i].row = i > 15 ? 6 : 3;
            pieces[i].col = (j - 11)  * 2;
        }

        if(!isRed)
            pieces[i].rotate();

        // 记录有棋子的位置
        ps[pieces[i].row][pieces[i].col] = i;
    }
}

// 绘制花格
void Plate::drawCross(int row, int col, QPainter &p)
{
    // 花线与横线的间距为5，花线的长度为15
    int margin = 5;
    int len = 15;
    QPoint center = QPoint(col * d, row * d);
    QPoint start;

    // 最左边横线不画左边的花线
    if(col != 0)
    {
        // 左上角花型
        start = center + QPoint(-margin, -margin);
        p.drawLine(start, start + QPoint(-len, 0));
        p.drawLine(start, start + QPoint(0, -len));

        // 左下角花型
        start = center + QPoint(-margin, +margin);
        p.drawLine(start, start + QPoint(-len, 0));
        p.drawLine(start, start + QPoint(0, len));
    }

    // 最右边横线不画右边的花线
    if(col != 8)
    {
        // 右上角花型
        start = center + QPoint(+margin, -margin);
        p.drawLine(start, start + QPoint(len, 0));
        p.drawLine(start, start + QPoint(0, -len));

        // 右下角花型
        start = center + QPoint(+margin, +margin);
        p.drawLine(start, start + QPoint(len, 0));
        p.drawLine(start, start + QPoint(0, len));
    }
}

// 能否移动
bool Plate::canMove(int moveId, int killId, int targetRow, int targetCol)
{
    Piece *pie = &pieces[moveId];

    // 移动是否会导致将帅会面
    if(pie->col >= 3 && pie->col <= 5 && isMeet(moveId, targetCol))
        return false;

    // 车规则
    if(pie->type == Rooks)
    {
        return !getPieceCount(pie->row, pie->col, targetRow, targetCol);
    }
    // 马规则
    else if(pie->type == Mao)
    {
        int rowDist = pie->row - targetRow;
        int colDist = pie->col - targetCol;

        // 不是竖日
        if(!(abs(rowDist) == 2 && abs(colDist) == 1))
            // 不是横日
            if(!(abs(rowDist) == 1 && abs(colDist) == 2))
                return false;

        // 竖日
        if(abs(rowDist) == 2)
        {
            // 撇马脚
            if(ps[(pie->row + targetRow) / 2][pie->col] != -1)
                return false;
        }
        // 横日
        else if(abs(colDist) == 2)
        {
            // 撇马脚
            if(ps[pie->row][(pie->col + targetCol) / 2] != -1)
                return false;
        }

        return true;
    }
    // 象的规则
    else if(pie->type == Elephants)
    {
        int rowDist = pie->row - targetRow;
        int colDist = pie->col - targetCol;

        // 走田
        if(abs(rowDist) != 2 || abs(colDist) != 2)
            return false;

        // 撇脚位置
        rowDist > 0 ? ++targetRow : --targetRow;
        colDist > 0 ? ++targetCol : --targetCol;

        // 撇脚
        if(ps[targetRow][targetCol] != -1)
            return false;

        // 是否过河
        return (pie->isBlack() == isRed) == (targetRow < 5);
    }
    // 士的规则
    else if(pie->type == Mandarins)
    {
        int rowDist = pie->row - targetRow;
        int colDist = pie->col - targetCol;

        // 斜走
        if(abs(rowDist) != 1 || abs(colDist) != 1)
            return false;

        // col是否出九宫格
        if(targetCol < 3 || targetCol > 5)
            return false;

        // row是否出九宫格
        if(pie->isBlack() == isRed)
            return targetRow <= 2;
        else
            return targetRow >= 7;
    }
    // 王的规则
    else if(pie->type == King)
    {
        int rowDist = pie->row - targetRow;
        int colDist = pie->col - targetCol;

        // 走一步
        if(abs(rowDist) > 1 || abs(colDist) > 1)
            return false;
        if((abs(rowDist) == 1) != (abs(colDist) == 0))
            return false;

        // 是否将帅会面
        int colOther = moveId > 16 ? pieces[moveId - 16].col : pieces[moveId + 16].col;
        if(colOther == targetCol)
        {
            int rowOther = moveId > 16 ? pieces[moveId - 16].row : pieces[moveId + 16].row;
            int targetRowTmp = targetRow;
            // 保证rowOther较小
            if(rowOther > targetRowTmp)
            {
                rowOther += targetRowTmp;
                targetRowTmp = rowOther - targetRowTmp;
                rowOther -= targetRowTmp;
            }
            ++rowOther;
            for(; rowOther < targetRowTmp; ++rowOther)
                if(ps[rowOther][targetCol] != -1 && pieces[(int)ps[rowOther][targetCol]].type != King )
                    break;
            if(rowOther == targetRowTmp)
                return false;
        }

        // col是否出九宫格
        if(targetCol < 3 || targetCol > 5)
            return false;

        // row是否出九宫格
        if(pie->isBlack() == isRed)
            return targetRow <= 2;
        else
            return targetRow >= 7;
    }
    // 炮的规则
    else if(pie->type == Pao)
    {
        int count = getPieceCount(pie->row, pie->col, targetRow, targetCol);
        if(count == 1 && killId != -1)
            return true;
        if(count == 0 && killId == -1)
            return true;
        return false;
    }
    // 兵的规则
    else if(pie->type == Pawns)
    {
        int rowDist = pie->row - targetRow;
        int colDist = pie->col - targetCol;

        if(abs(rowDist) > 1 || abs(colDist) > 1)
            return false;
        // 红棋
        if(pie->isBlack() == isRed)
        {
            if(rowDist > 0)
                return false;
            // 未过河，不能左右移动
            if(pie->row < 5 && colDist != 0)
                return false;
        }
        // 黑棋
        else
        {
            if(rowDist < 0)
                return false;
            // 未过河，不能左右移动
            if(pie->row > 4 && colDist != 0)
                return false;
        }
        return (abs(rowDist) == 1) == (abs(colDist) == 0);
    }
    else
        return false;

    return true;
}

// 两点之间棋子数
int Plate::getPieceCount(int row1, int col1, int row2, int col2)
{
    int count = 0;
    if(row1 != row2 && col1 != col2)
        return -1;

    if(row1 == row2)
    {
        // 保证col1较小
        if(col1 > col2)
        {
            // 交换
            col1 += col2;
            col2 = col1 - col2;
            col1 -= col2;
        }
        ++col1;
        for(; col1 < col2; ++col1)
        {
            if(ps[row1][col1] != -1)
                ++count;
        }
    }
    else
    {
        // 保证row1较小
        if(row1 > row2)
        {
            // 交换
            row1 += row2;
            row2 = row1 - row2;
            row1 -= row2;
        }
        ++row1;
        for(; row1 < row2; ++row1)
        {
            if(ps[row1][col1] != -1)
                ++count;
        }
    }

    return count;
}

// 将帅会面
bool Plate::isMeet(int moveId, int targetCol)
{
    // 是否将帅会面
    if(pieces[4].col != pieces[20].col)
        return false;
    int col = pieces[4].col;
    int row = pieces[4].row;
    int rowOther = pieces[20].row;

    if(row>rowOther)
    {
        row += rowOther;
        rowOther = row - rowOther;
        row = row - rowOther;
    }

    ++row;
    for(; row < rowOther; ++row)
        if(ps[row][col] != -1)
        {
            if(ps[row][col] == moveId && targetCol != pieces[moveId].col)
                continue;
            break;
        }
    if(row == rowOther)
        return true;
    return false;
}

// 移动棋子
void Plate::move(int moveId, int killId, int targetRow, int targetCol)
{
    // 棋盘对应位置没有棋子(要移走)
    ps[pieces[moveId].row][pieces[moveId].col] = -1;

    addStep(moveId, killId, targetRow, targetCol);

    pieces[moveId].row = targetRow;
    pieces[moveId].col = targetCol;

    if(killId != -1)
    {
        pieces[killId].killed = true;
        AddUpValue(pieces[killId].isBlack(), score[pieces[killId].type]);
    }

    // 棋盘对应位置保存棋子id
    ps[targetRow][targetCol]=moveId;

    // 准备下一次移动
    selectid = -1;

    // 轮到另一方走棋
    redTure = !redTure;
}

// 保存
void Plate::addStep(int moveId, int killId, int targetRow, int targetCol)
{
    Step *rec = new Step;
    rec->moveId = moveId;
    rec->killId = killId;
    rec->moveRow = pieces[moveId].row;
    rec->moveCol = pieces[moveId].col;
    rec->targetRow = targetRow;
    rec->targetCol = targetCol;
    listStep.append(rec);
}

// 回退一步
void Plate::moveBack()
{
    Step *rec = listStep.back();
    listStep.removeLast();

    pieces[rec->moveId].row = rec->moveRow;
    pieces[rec->moveId].col = rec->moveCol;
    ps[rec->moveRow][rec->moveCol] = rec->moveId;

    if(rec->killId != -1)
    {
        pieces[rec->killId].killed = false;

        AddUpValue(!pieces[rec->killId].isBlack(), score[pieces[rec->killId].type]);
    }
    ps[rec->targetRow][rec->targetCol] = rec->killId;

    // 释放空间
    delete rec;

    selectid = -1;
    redTure = !redTure;
}

// 对方统计分数
void Plate::AddUpValue(bool isBack, int value)
{

}
