#include "NetGame.h"
#include <QDebug>
#include <QThread>
#include <QTimer>
#include <QList>
#include <QHostAddress>
#include <QNetworkInterface>
#include <winsock2.h>

NetGame::NetGame(bool isServer, QWidget *parent):Plate(parent)
{
    _server = NULL;
    _socket = NULL;
    udpSocket = NULL;
    port = 8080;

    if(isServer)
    {
        udpSocket =  new QUdpSocket(this);
        udpSocket->bind(port,QUdpSocket::ShareAddress|QUdpSocket::ReuseAddressHint);
        connect(udpSocket,SIGNAL(readyRead()),this,SLOT(UdpRece()));

        _server = new QTcpServer(this);
        _server->listen(QHostAddress::Any, port);

        connect(_server, SIGNAL(newConnection()),
                this, SLOT(slotNewConnection()));
    }
    else
    {
        udpSocket =  new QUdpSocket(this);
        udpSocket->bind(port,QUdpSocket::ShareAddress|QUdpSocket::ReuseAddressHint);
        connect(udpSocket,SIGNAL(readyRead()),this,SLOT(UdpRece()));

        QString buf = "3";
        udpSocket->writeDatagram(buf.toLocal8Bit(),QHostAddress::Broadcast,port);

        _socket = new QTcpSocket(this);

        connect(_socket, SIGNAL(connected()),
                this, SLOT(slotSuccess()));

        connect(_socket, SIGNAL(readyRead()),
                this, SLOT(slotRecv()));
    }
}

void NetGame::click(int clickid, int row, int col)
{
    if(redTure != isRed)
        return;

    Plate::click(clickid, row, col);

    // 发送给对方
    char buf[4];
    buf[0] = 2;
    buf[1] = 9 - row;
    buf[2] = 8 - col;
    buf[3] = clickid;
    _socket->write(buf, 4);
}

void NetGame::slotNewConnection()
{
    if(_socket) return;

    udpSocket = NULL;

    _socket = _server->nextPendingConnection();
    connect(_socket, SIGNAL(readyRead()),
            this, SLOT(slotRecv()));

    // 给对方发送数据
    char buf[2];
    buf[0] = 1;
    buf[1] = 0;

    _socket->write(buf, 2);

    isRed = true;
    initGame();
    update();
}

void NetGame::slotRecv()
{
    QByteArray ba = _socket->readAll();
    char cmd = ba[0];
    if(cmd == 1)
    {
        // 初始化
        isRed = false;
        initGame();
        update();
    }
    else if(cmd == 2)
    {
        int row = ba[1];
        int col = ba[2];
        int clickid = ba[3];
        Plate::click(clickid, row, col);
    }
}

void NetGame::UdpRece()
{
    QByteArray datagram;
    datagram.resize(udpSocket->pendingDatagramSize());
    udpSocket->readDatagram(datagram.data(),datagram.size());

    char cmd = datagram[0];
    if(cmd == '3' && _server)
    {
        QString buf = "4";
        QString ip = getHostIpAddress();
        udpSocket->writeDatagram((buf+ip).toLocal8Bit(),QHostAddress::Broadcast,port);
    }
    else if(cmd == '4' && !_server)
    {
        QString ip = QString(datagram);
        _socket->connectToHost(QHostAddress(ip.mid(1)), port);
    }
}

void NetGame::slotSuccess()
{
    udpSocket = NULL;
}

// 获取内网ip
QString NetGame::getHostIpAddress()
{
    WSAData wsaData;
    if(WSAStartup(MAKEWORD(1,1),&wsaData)!=0)//需要添加库WS2_32.lib，如果不明白什么意思，参见http://blog.csdn.net/bolike/article/details/7584727
    {
        return NULL;
    }

    char *ipAddress = fetchIPAddress();
    WSACleanup();
    return ipAddress;
}

// 获取内网ip
char* NetGame::fetchIPAddress()
{
    char host_name[225];
    if(gethostname(host_name,sizeof(host_name)) == SOCKET_ERROR)
    {
        qDebug()<<"Error "<<WSAGetLastError()<<" when getting local host name."<<endl;
    }

    struct hostent *phe = gethostbyname(host_name);
    if(phe == 0)
    {
        qDebug()<<"get host entry error";
    }

    struct in_addr addr;
    memcpy(&addr,phe->h_addr_list[0],sizeof(struct in_addr));
    return inet_ntoa(addr);
}

// 统计分数
void NetGame::AddUpValue(bool isBack, int value)
{
    if(!isBack)
        countValue += value;
    else
        countValue -= value;
}
