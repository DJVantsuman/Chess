#include "chess.h"

Chess::Chess() {

}

Chess::~Chess(){

}

int Chess::checkFigurePosition(int toX, int toY, int x, int y, int type) {
    if (type == 0 || type == 6)
        return checkPawn(toX, toY, x, y, type);
    else if (type == 1 || type == 7)
        return checkKnight(toX, toY, x, y);
    else if (type == 2 || type == 8)
        return checkRook(toX, toY, x, y);
    else if (type == 3 || type == 9)
        return checkBishop(toX, toY, x, y);
    else if (type == 4 || type == 10)
        return checkQueen(toX, toY, x, y);
    else if (type == 5 || type == 11)
        return checkKing(toX, toY, x, y);
    return 1;
}

int Chess::checkPawn(int toX, int toY, int x, int y, int type) {
        if ((type == 0 && (x != toX || y >= toY)) ||
               (type == 6 && (x != toX || y <= toY)))
            return -1;
    return 1;
}

int Chess::checkKnight(int toX, int toY, int x, int y) {
    if (x - 2 == toX || x + 2 == toX){
        if (y + 1 == toY || y - 1 == toY)
            return 1;
    }
    else if (y - 2 == toY || y + 2 == toY) {
        if (x + 1 == toX || x - 1 == toX)
            return 1;
    }
    return -1;
}

int Chess::checkRook(int toX, int toY, int x, int y) {
    if (y > toY && ((y - toY == toX - x) || (y - toY == x - toX)))
        return 1;
    else if (y < toY && ((toY - y == toX - x) || (toY - y == x - toX)))
        return 1;
    return -1;
}

int Chess::checkBishop(int toX, int toY, int x, int y) {
    if ((x != toX && y == toY) ||  (x == toX && y != toY))
        return 1;
    return -1;
}

int Chess::checkQueen(int toX, int toY, int x, int y) {
    if (y > toY && ((y - toY == toX - x) || (y - toY == x - toX)))
        return 1;
    else if (y < toY && ((toY - y == toX - x) || (toY - y == x - toX)))
        return 1;
    else if ((x != toX && y == toY) ||  (x == toX && y != toY))
        return 1;
    return -1;
}

int Chess::checkKing(int toX, int toY, int x, int y) {
    if ((((x + 1 == toX || x - 1 == toX) && y == toY)) ||
            (x == toX && (y + 1 == toY || y - 1 == toY)))
            return 1;
    if (y  + 1 == toY && ((1 == toX - x) || (1 == x - toX)))
        return 1;
    else if (y - 1 == toY && ((1 == toX - x) || (1 == x - toX)))
        return 1;
    return -1;
}
