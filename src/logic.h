#pragma once
#include <memory>
#include <QAbstractListModel>
#include "chess.h"

class Logic: public QAbstractListModel
{
    Q_OBJECT
public:

    enum GlobalConstants {
        BOARD_SIZE = 8
    };

    enum Roles {
        Type = Qt::UserRole,
        PositionX,
        PositionY,
    };
    
public:
    explicit Logic(QObject *parent = 0);
    ~Logic();

    Q_PROPERTY(int boardSize READ boardSize CONSTANT);
    int boardSize() const;

    Q_INVOKABLE void clear();
    Q_INVOKABLE void finish();
    Q_INVOKABLE bool move(int fromX, int fromY, int toX, int toY);
    Q_INVOKABLE bool loadGame();
    Q_INVOKABLE void saveGame();

protected:
    int rowCount(const QModelIndex & parent) const override;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    static int playerNamber;
    Chess chess;
public:
    struct Figure;
    struct Impl;
    Impl* impl;
    QList<Figure> history;
};

QDataStream& operator<<( QDataStream& d, const QList<Logic::Impl>& l );
QDataStream& operator<<( QDataStream& d, const Logic::Impl& l );
QDataStream& operator<<( QDataStream& d, const Logic::Figure& f );

QDataStream& operator>>( QDataStream& d, const QList<Logic::Impl>& h );
QDataStream& operator>>( QDataStream& d, const Logic::Impl& l );
QDataStream& operator>>( QDataStream& d, const Logic::Figure& f );
QDataStream& operator>>( QDataStream& d, const int& n );
