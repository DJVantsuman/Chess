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
    bool loadHistory();
public:
    void setState(QList<int> log, int playerNamber);
    bool getState(QList<int> & log);
};

#endif // MEMENTO_H
