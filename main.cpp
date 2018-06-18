#include <QApplication>
#include <QProcess>
#include "Plate.h"
#include "AI.h"
#include "NetGame.h"
#include "ChooseDlg.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Plate *p;

    ChooseDlg dlg;

    do{
        if(dlg.exec() != QDialog::Accepted)
            return 0;

        switch((int)dlg.gametype)
        {
        case Single:
            p = new AI();
            p->gametype = Single;
            break;
        case Server:
            p = new NetGame(true);
            p->gametype = Server;
            break;
        case Client:
            p = new NetGame(false);
            p->gametype = Client;
            break;
        }

        if(p->exec() != QDialog::Accepted)
            return 0;
        else
            delete p;
    }while(1);
}
