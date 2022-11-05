QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CheckersGameGUI
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    BackTracking.cpp \
    Game.cpp \
        main.cpp

HEADERS += \
    BackTracking.h \
    Check.h \
    Game.h \
    MovePiece.h \
    Square.h \
    main.h

