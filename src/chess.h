#ifndef CHESS_H
#define CHESS_H


class Chess
{
private:
    int checkPawn(int toX, int toY, int x, int y, int type);
    int checkKnight(int toX, int toY, int x, int y);
    int checkBishop(int toX, int toY, int x, int y);
    int checkRook(int toX, int toY, int x, int y);
    int checkQueen(int toX, int toY, int x, int y);
    int checkKing(int toX, int toY, int x, int y);
public:
    Chess();
    ~Chess();
    int checkFigurePosition(int toX, int toY, int x, int y, int type);
};

#endif // CHESS_H
