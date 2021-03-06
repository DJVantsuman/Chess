TEMPLATE = app

CONFIG += c++11
CONFIG += CONSOLE

QT += qml quick widgets

SOURCES += src/main.cpp \
    src/logic.cpp \
    src/memento.cpp \
    src/checkChess.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

HEADERS += \
    src/logic.h \
    src/memento.h \
    src/checkChess.h
