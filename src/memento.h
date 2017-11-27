#ifndef MEMENTO_H
#define MEMENTO_H

#include <iostream>
#include <QApplication>
#include <QDataStream>
#include <QIODevice>
#include <QFile>
#include <QDebug>

class Memento
{
public:
    Memento();
    ~Memento();
private:
    QList<int> _state;
    void loadHistory();
public:
    void setState(QList<int> log, int playerNamber);
    QList<int> getState();
};

#endif // MEMENTO_H
