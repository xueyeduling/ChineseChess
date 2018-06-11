#include <QApplication>
#include "plate.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Plate p;
    p.show();

    return app.exec();
}
