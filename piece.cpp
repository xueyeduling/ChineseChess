#include "piece.h"

Piece::Piece(QObject *parent) : QObject(parent)
{

}

void Piece::draw(QPainter &p, int d, int selectid)
{
    // 被吃掉的棋子不绘制
    if(killed)
        return;

    int x = col * d;
    int y = row * d;

    // 减小棋子直径，8为棋子直径与格子的长宽的差值
    // 棋子直径为棋盘格子的长宽减8
    d -= 8;
    QRect rc;

    //p.setPen(Qt::NoPen); // 不要画笔(没边框)
    p.setPen(QColor(Qt::black));

    if(id == selectid)
    {
        // 设置选中背景色
        p.setBrush(QBrush(QColor(0xd2,0x69,0x1e)));
        // 选中上移10像素
        rc = QRect(QPoint(x-d/2, y-d/2 - 10), QPoint(x+d/2, y+d/2 - 10));

        p.drawEllipse(QPoint(x, y - 10), d/2, d/2);
    }
    else
    {
        p.setBrush(QBrush(QColor(0xf4,0xa4,0x60))); // 设置背景色
        rc = QRect(QPoint(x-d/2, y-d/2), QPoint(x+d/2, y+d/2));

        p.drawEllipse(QPoint(x, y), d/2, d/2);
    }

    p.setPen(QPen(isBlack()?Qt::black:Qt::red));// 设置画笔，显示字
    p.setFont(QFont("楷体", d/2 - 8, QFont::Bold)); // -8让字体变小一点, QFont::Bold为加粗体(权重是75)

    switch (type) {
    case Rooks:
        p.drawText(rc, isBlack()?"车":"車", QTextOption(Qt::AlignCenter));
        break;
    case Mao:
        p.drawText(rc, "马", QTextOption(Qt::AlignCenter));
        break;
    case Elephants:
        p.drawText(rc, isBlack()?"象":"相", QTextOption(Qt::AlignCenter));
        break;
    case Mandarins:
        p.drawText(rc, isBlack()?"士":"仕", QTextOption(Qt::AlignCenter));
        break;
    case King:
        p.drawText(rc, isBlack()?"将":"帥", QTextOption(Qt::AlignCenter));
        break;
    case Pao:
        p.drawText(rc, "炮", QTextOption(Qt::AlignCenter));
        break;
    case Pawns:
        p.drawText(rc, isBlack()?"卒":"兵", QTextOption(Qt::AlignCenter));
        break;
    default:
        break;
    }
}
