#ifndef STEP_H
#define STEP_H

#include <QObject>

class Step : public QObject
{
    Q_OBJECT
public:
    explicit Step(QObject *parent = nullptr);
    int moveId;
    int killId;
    int moveRow;
    int moveCol;
    int targetRow;
    int targetCol;

signals:

public slots:
};

#endif // STEP_H
