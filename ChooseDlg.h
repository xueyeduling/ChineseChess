#ifndef ChooseDlg_H
#define ChooseDlg_H

#include <QDialog>
#include <QIcon>
#include "Plate.h"

class ChooseDlg : public QDialog
{
    Q_OBJECT
public:
    explicit ChooseDlg(QWidget *parent = 0);

    void paintEvent(QPaintEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    GameType gametype;
signals:

public slots:
};

#endif // ChooseDlg_H
