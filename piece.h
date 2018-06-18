#ifndef PIECE_H
#define PIECE_H

#include <QObject>
#include <QPainter>

enum Type{
    Rooks,
    Mao,
    Elephants,
    Mandarins,
    King,
    Pao,
    Pawns
};

class Piece : public QObject
{
    Q_OBJECT
public:
    explicit Piece(QObject *parent = nullptr);

    Type type;
    int row; // 0-9 10行
    int col; // 0-8 9列
    int id; // 0-31 32个棋子，0-15为红棋，16-32为黑棋
    bool killed; // 是否被干掉

    bool isBlack()
    {
        return id < 16;
    }

    void draw(QPainter &p, int d, int selectid);

    // 旋转
    void rotate();

signals:

public slots:
};

#endif // PIECE_H
