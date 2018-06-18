SOURCES += \
    main.cpp \
    AI.cpp \
    Piece.cpp \
    Plate.cpp \
    NetGame.cpp \
    Step.cpp \
    ChooseDlg.cpp

QT += widgets gui
QT += network
LIBS += -lWs2_32
RC_FILE = icon.rc

HEADERS += \
    AI.h \
    Piece.h \
    Plate.h \
    NetGame.h \
    Step.h \
    ChooseDlg.h

RESOURCES += \
    ret.qrc
