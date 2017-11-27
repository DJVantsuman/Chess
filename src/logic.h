#pragma once
#include <memory>
#include <QAbstractListModel>
#include "chess.h"
#include "memento.h"

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
    Q_INVOKABLE void loadGame();
    Q_INVOKABLE void saveGame();
    Q_INVOKABLE void saveOneStep();
    Q_INVOKABLE void updateImpl();
    Q_INVOKABLE void prevStep();
    Q_INVOKABLE void nextStep();
    Q_INVOKABLE int getPlayerNamber() const;
    Q_INVOKABLE void startNewGame();


protected:
    int rowCount(const QModelIndex & parent) const override;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    int numberSteps;
    struct Figure;
    Q_INVOKABLE int playerNamber;
    Chess chess;
    Memento memento;
    void appendStepToHistory(QList<Figure> figures);
    void newGame(QList<Figure> & figures);

public:
    struct Impl;
    Impl* impl;
    QList<int> history;
};
