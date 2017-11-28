#ifndef CHECKCHESS_H
#define CHECKCHESS_H


class CheckChess
{
private:
    int checkPawn(int toX, int toY, int x, int y, int type);
    int checkKnight(int toX, int toY, int x, int y);
    int checkBishop(int toX, int toY, int x, int y);
    int checkRook(int toX, int toY, int x, int y);
    int checkQueen(int toX, int toY, int x, int y);
    int checkKing(int toX, int toY, int x, int y);
public:
    CheckChess();
    ~CheckChess();
    int checkFigurePosition(int toX, int toY, int x, int y, int type);
};

#endif // CHESS_H
