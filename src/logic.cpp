#include "logic.h"
#include <QList>
#include <QByteArray>
#include <QHash>
#include <iostream>
#include <QApplication>
#include <QDataStream>
#include <QIODevice>
#include <QFile>
#include <QDebug>

struct Logic::Figure
{
  int type;
  int x;
  int y;
};

struct Logic::Impl
{
  QList<Logic::Figure> figures;

  int findByPosition(int x, int y);
};

int Logic::Impl::findByPosition(int x, int y) {
  for (int i(0); i<figures.size(); ++i) {
    if (figures[i].x != x || figures[i].y != y ) { 
      continue; 
    }
    return i;    
  }
  return -1;
}

Logic::Logic(QObject *parent)
    : QAbstractListModel(parent)
  , impl(new Impl())
{
    newGame(impl->figures);
    playerNamber = 1;
}

Logic::~Logic() {
}

void Logic::newGame(QList<Logic::Figure> & figures) {

    figures << Logic::Figure { 0, 0, 1 };
    figures << Logic::Figure { 0, 1, 1 };
    figures << Logic::Figure { 0, 2, 1 };
    figures << Logic::Figure { 0, 3, 1 };
    figures << Logic::Figure { 0, 4, 1 };
    figures << Logic::Figure { 0, 5, 1 };
    figures << Logic::Figure { 0, 6, 1 };
    figures << Logic::Figure { 0, 7, 1 };
    figures << Logic::Figure { 1, 1, 0 };
    figures << Logic::Figure { 1, 6, 0 };
    figures << Logic::Figure { 2, 2, 0 };
    figures << Logic::Figure { 2, 5, 0 };
    figures << Logic::Figure { 3, 0, 0 };
    figures << Logic::Figure { 3, 7, 0 };
    figures << Logic::Figure { 4, 3, 0 };
    figures << Logic::Figure { 5, 4, 0 };


    figures << Logic::Figure { 6, 0, 6 };
    figures << Logic::Figure { 6, 1, 6 };
    figures << Logic::Figure { 6, 2, 6 };
    figures << Logic::Figure { 6, 3, 6 };
    figures << Logic::Figure { 6, 4, 6 };
    figures << Logic::Figure { 6, 5, 6 };
    figures << Logic::Figure { 6, 6, 6 };
    figures << Logic::Figure { 6, 7, 6 };
    figures << Logic::Figure { 7, 1, 7 };
    figures << Logic::Figure { 7, 6, 7 };
    figures << Logic::Figure { 8, 2, 7 };
    figures << Logic::Figure { 8, 5, 7 };
    figures << Logic::Figure { 9, 0, 7 };
    figures << Logic::Figure { 9, 7, 7 };
    figures << Logic::Figure { 10, 3, 7 };
    figures << Logic::Figure { 11, 4, 7 };

    if (history.isEmpty())
        saveOneStep();
}

void Logic::startNewGame() {
    if (!history.isEmpty())
        history.clear();
    impl->figures.clear();
    newGame(impl->figures);
    int index;
    for(int i = 0; i < impl->figures.size(); i++)
    {
        index = impl->findByPosition(impl->figures[i].x, impl->figures[i].y);
        QModelIndex topLeft = createIndex(index, 0);
        QModelIndex bottomRight = createIndex(index, 0);
        emit dataChanged(topLeft, bottomRight);
    }
}

int Logic::boardSize() const {
  return BOARD_SIZE;
}

int Logic::rowCount(const QModelIndex & ) const {
  return impl->figures.size(); 
}

QHash<int, QByteArray> Logic::roleNames() const { 
  QHash<int, QByteArray> names;
  names.insert(Roles::Type      , "type");
  names.insert(Roles::PositionX , "positionX");
  names.insert(Roles::PositionY , "positionY");
  return names;
}

QVariant Logic::data(const QModelIndex & modelIndex, int role) const { 
  if (!modelIndex.isValid()) {
    return QVariant();
  }
    
  int index = static_cast<int>(modelIndex.row());
  
  if (index >= impl->figures.size() || index < 0) {
    return QVariant();
  }

  Figure & figure = impl->figures[index];
    
  switch (role) {
    case Roles::Type     : return figure.type;
    case Roles::PositionX: return figure.x;
    case Roles::PositionY: return figure.y;
  }
  return QVariant(); 
}

void Logic::clear() {
  beginResetModel();
  impl->figures.clear();
  endResetModel();
}

void Logic::finish() {
    beginResetModel();
    impl->figures.clear();
    endResetModel();
    QApplication::quit();
}

bool Logic::move(int fromX, int fromY, int toX, int toY) {
  int index = impl->findByPosition(fromX, fromY);

  if (index < 0) return false;
  if (playerNamber == 1 && impl->figures[index].type > 5 ) return false;
  if (playerNamber == 2 && impl->figures[index].type < 6 ) return false;

  int n = chess.checkFigurePosition(toX, toY, impl->figures[index].x, impl->figures[index].y, impl->figures[index].type);
  if (n < 0) return false;

  if (toX < 0 || toX >= BOARD_SIZE || toY < 0 || toY >= BOARD_SIZE || impl->findByPosition(toX, toY) >= 0) {
    return false;
  }

  playerNamber = playerNamber == 1 ? 2 : 1;

  impl->figures[index].x = toX;
  impl->figures[index].y = toY;
  QModelIndex topLeft = createIndex(index, 0);
  QModelIndex bottomRight = createIndex(index, 0);
  emit dataChanged(topLeft, bottomRight);
  return true;
}

void Logic::saveOneStep() {
     appendStepToHistory(impl->figures);
}

void Logic::appendStepToHistory(QList<Logic::Figure> figures) {
    for (int i = 0; i < figures.size(); i++)
    {
        history << figures[i].type;
        history << figures[i].x;
        history << figures[i].y;
    }
}

void Logic::loadGame() {
    QList<int> log = memento.getState();
    history.clear();
    for (int i = 0; i < log.size() - 3; i += 3){
        history << log[i];
        history << log[i + 1];
        history << log[i + 2];
    }
    playerNamber = log[log.size() - 1];
    numberSteps = history.size() / 96;
//    qDebug() << "Number steps : " << numberSteps;
    updateImpl();
}

void Logic::updateImpl() {
//    qDebug() << "Update impl : " << numberSteps;
    if (numberSteps > history.size() / 96)
        return;
    int i = 96 * numberSteps - 1;
    int index;
    for(int j = 32 - 1; j >= 0; j--, i -= 3)
    {
        impl->figures[j].y = history[i];
        impl->figures[j].x = history[i - 1];
        impl->figures[j].type = history[i - 2];

        index = impl->findByPosition(impl->figures[j].x, impl->figures[j].y);
        QModelIndex topLeft = createIndex(index, 0);
        QModelIndex bottomRight = createIndex(index, 0);
        emit dataChanged(topLeft, bottomRight);
    }
}

int Logic::getPlayerNamber() const {
    return playerNamber;
}

void Logic::saveGame() {
    memento.setState(history, playerNamber);
}

void Logic::nextStep() {
    if (numberSteps >= history.size() / 96)
        return;
    else
    {
        playerNamber = playerNamber == 1 ? 2 : 1;
        numberSteps++;
        updateImpl();
    }
}

void Logic::prevStep() {
    if (numberSteps <= 1)
        return;
    else
    {
        playerNamber = playerNamber == 1 ? 2 : 1;
        numberSteps--;
        updateImpl();
    }
}
