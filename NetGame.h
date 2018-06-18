#ifndef NETGAME_H
#define NETGAME_H

#include "Plate.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>

/*
 * 1. 执红方还是黑方，这个信息又服务器发出，客户端接收
 *      第一个字节固定是1
 *      第二个字节固定是1或0，1表示走红棋，0表示走黑棋
 * 2. 点击信息
 *      第一个字节固定是2
 *      第二个字节是row，第三个字节是col，第四个字节是点击的棋子ID
 * 3.
 */

class NetGame :  public Plate
{
    Q_OBJECT
public:
    explicit NetGame(bool isServer, QWidget *parent = 0);

    QTcpServer *_server;
    QTcpSocket *_socket;
    QUdpSocket * udpSocket;
    qint16 port; // 端口

    // 计分
    virtual void AddUpValue(bool isBack, int value);

    virtual void click(int clickid, int row, int col);

    QString getHostIpAddress();

    char* fetchIPAddress();

signals:

public slots:
    void slotNewConnection();
    void slotRecv();
    void UdpRece();
    void slotSuccess();
};

#endif // NETGAME_H
