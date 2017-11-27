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

int Logic::playerNamber = 1;

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
    impl->figures << Logic::Figure { 0, 0, 1 };
    impl->figures << Logic::Figure { 0, 1, 1 };
    impl->figures << Logic::Figure { 0, 2, 1 };
    impl->figures << Logic::Figure { 0, 3, 1 };
    impl->figures << Logic::Figure { 0, 4, 1 };
    impl->figures << Logic::Figure { 0, 5, 1 };
    impl->figures << Logic::Figure { 0, 6, 1 };
    impl->figures << Logic::Figure { 0, 7, 1 };
    impl->figures << Logic::Figure { 1, 1, 0 };
    impl->figures << Logic::Figure { 1, 6, 0 };
    impl->figures << Logic::Figure { 2, 2, 0 };
    impl->figures << Logic::Figure { 2, 5, 0 };
    impl->figures << Logic::Figure { 3, 0, 0 };
    impl->figures << Logic::Figure { 3, 7, 0 };
    impl->figures << Logic::Figure { 4, 3, 0 };
    impl->figures << Logic::Figure { 5, 4, 0 };


    impl->figures << Logic::Figure { 6, 0, 6 };
    impl->figures << Logic::Figure { 6, 1, 6 };
    impl->figures << Logic::Figure { 6, 2, 6 };
    impl->figures << Logic::Figure { 6, 3, 6 };
    impl->figures << Logic::Figure { 6, 4, 6 };
    impl->figures << Logic::Figure { 6, 5, 6 };
    impl->figures << Logic::Figure { 6, 6, 6 };
    impl->figures << Logic::Figure { 6, 7, 6 };
    impl->figures << Logic::Figure { 7, 1, 7 };
    impl->figures << Logic::Figure { 7, 6, 7 };
    impl->figures << Logic::Figure { 8, 2, 7 };
    impl->figures << Logic::Figure { 8, 5, 7 };
    impl->figures << Logic::Figure { 9, 0, 7 };
    impl->figures << Logic::Figure { 9, 7, 7 };
    impl->figures << Logic::Figure { 10, 3, 7 };
    impl->figures << Logic::Figure { 11, 4, 7 };

    saveOneStep();
}

Logic::~Logic() {
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

bool Logic::loadGame() {
    qInfo() << "Load";
    QFile in("history.bin");
    if( in.open( QIODevice::ReadOnly ) ) {
        QList<int> log;
        int t, x, y;
        QDataStream stream( &in );
        for (int i = 0; !in.atEnd(); i += 3) {
            stream >> t >> x >> y;
             qDebug() << "Debag : " << t << " " << x << " " << y;
        }
//        int size = log.size();
//        for (int i = size; i > size-96; i++){
//            impl->figures[i].type = log[size - 1][i].type;
//            impl->figures[i].x = log[size - 1][i].x;
//            impl->figures[i].y = log[size - 1][i].y;
//        }
        in.close();
        }
    return true;
}

void Logic::saveGame() {
    QFile file("history.bin");
    if(file.open(QIODevice::WriteOnly)) {
        QDataStream stream(&file);
        stream. setVersion(QDataStream::Qt_5_6);
        for (int i = 0; i < history.size(); i++)
            stream << history[i];
//        stream << history;
    }
    file.close();
}

QDataStream& operator<<( QDataStream& d, const QList<int>& h ){
    for (int i = 0; i < h.size(); i++){
        d << h[i];
        qDebug() << "Debag : " << h[i];
    }
    return d;
}

//QDataStream& operator<<( QDataStream& d, const QList<Logic::Figure>& l ){

//    for (int i = 0; i < l.size(); i++) {
//        d << l[i];
//    }
//    return d;
//}

//QDataStream& operator<<( QDataStream& d, const Logic::Figure& f ){
//    return d << f.type << f.x << f.y;
//}


//QDataStream& operator>>( QDataStream& d, const QList<QList<Logic::Figure>>& h ) {
//    for (int i = 0; i < h.size(); i++){
//        d >> h[i];
//    }
//    return d;
//}

//QDataStream& operator>>( QDataStream& d, const QList<Logic::Figure>& l ){

//    for (int i = 0; i < l.size(); i++) {
//        d >> l[i];
//    }
//    return d;
//}

//QDataStream& operator>>( QDataStream& d, const Logic::Figure& f ){
//    d >> f.type >> f.x >> f.y;
//    return d;
//}

//QDataStream& operator>>( QDataStream& d, const int& n ){
//    d >> n;
//    return d;
//}
