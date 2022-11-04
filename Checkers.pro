QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Checkers
TEMPLATE = app


DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17

SOURCES += \
    display.cpp \
    king.cpp \
    main.cpp \
    space.cpp \
    Checker.cpp \
    Board.cpp \
    Game.cpp \
    Piece.cpp \
    Square.cpp

HEADERS += \
    display.h \
    king.h \
    space.h \
    Checker.h \
    Board.h \
    Game.h \
    Piece.h \
    Square.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
