#include "ChooseDlg.h"

ChooseDlg::ChooseDlg(QWidget *parent) : QDialog(parent)
{
    this->setWindowIcon(QIcon(":/Img/log.png"));
    this->setWindowTitle("中国象棋");
    this->setFixedSize(1000, 600);

    // 添加背景图片
    this->setAutoFillBackground(true);
    QPalette palette;
    QPixmap pixmap(":/Img/background.png");
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    this->setPalette(palette);
}

// 绘图事件
void ChooseDlg::paintEvent(QPaintEvent *event)
{
    int d = 55;

    QPainter p(this);
    p.translate(QPoint(270, 50));

    QPen pen = p.pen();
    pen.setWidth(2);//改变线宽
    p.setPen(pen);

    // 悔棋button
    p.setPen(Qt::NoPen); // 不要画笔(没边框)
    // 背景颜色：能悔棋是绿色，不能悔棋是灰色
    p.setBrush(QBrush(QColor(Qt::darkGreen)));
    QRect rcBtn = QRect(QPoint(350, 100), QPoint(530, 160));
    p.drawRoundRect(rcBtn, 20, 50);
    // 字体颜色：能悔棋是白色，不能悔棋是黑色
    p.setPen(QPen(Qt::white));
    p.setFont(QFont("楷体", d/2 - 16, QFont::DemiBold )); // -10让字体变小一点, QFont::DemiBold为半粗体(权重是63)
    p.drawText(rcBtn, "人机对战", QTextOption(Qt::AlignCenter));

    // 重新开始button
    p.setPen(Qt::NoPen); // 不要画笔(没边框)
    // 背景颜色：能悔棋是绿色，不能悔棋是灰色
    p.setBrush(QBrush(QColor(Qt::darkGreen)));
    rcBtn = QRect(QPoint(350, 200), QPoint(530, 260));
    p.drawRoundRect(rcBtn, 20, 50);
    // 字体颜色：能悔棋是白色，不能悔棋是黑色
    p.setPen(QPen(Qt::white));
    p.setFont(QFont("楷体", d/2 - 16, QFont::DemiBold )); // -10让字体变小一点, QFont::DemiBold为半粗体(权重是63)
    p.drawText(rcBtn, "创建房间", QTextOption(Qt::AlignCenter));
    // 字体颜色恢复黑色，用于画线
    p.setPen(QPen(Qt::black));

    // 重新开始button
    p.setPen(Qt::NoPen); // 不要画笔(没边框)
    // 背景颜色：能悔棋是绿色，不能悔棋是灰色
    p.setBrush(QBrush(QColor(Qt::darkGreen)));
    rcBtn = QRect(QPoint(350, 300), QPoint(530, 360));
    p.drawRoundRect(rcBtn, 20, 50);
    // 字体颜色：能悔棋是白色，不能悔棋是黑色
    p.setPen(QPen(Qt::white));
    p.setFont(QFont("楷体", d/2 - 16, QFont::DemiBold )); // -10让字体变小一点, QFont::DemiBold为半粗体(权重是63)
    p.drawText(rcBtn, "加入房间", QTextOption(Qt::AlignCenter));
    // 字体颜色恢复黑色，用于画线
    p.setPen(QPen(Qt::black));
}

void ChooseDlg::mouseReleaseEvent(QMouseEvent *event)
{
    // pt是像数值
    QPoint pt = event->pos();
    pt -= QPoint(270, 50);

    // (350, 100), QPoint(530, 160)
    if(pt.x() > 350 && pt.x() < 530 && pt.y() > 100 && pt.y() < 160)
        gametype = Single;
    else if(pt.x() > 350 && pt.x() < 530 && pt.y() > 200 && pt.y() < 260)
        gametype = Server;
    else if(pt.x() > 350 && pt.x() < 530 && pt.y() > 300 && pt.y() < 360)
        gametype = Client;
    else
        return;

    accept();
}
