#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <string>
#include <iostream>
#include <utility>

class chessPiece {
    public:
        chessPiece();
        chessPiece(int n); //0 = empty piece, 1 = out of bounds
        chessPiece(int c, int n);
        void printPiece() const;
        int getPiece() const;
        int getColor() const;
        void setPawn(); //only for pawns
        int getPawn() const;
        void setPosition(int x, int y);
        std::pair<int, int> getPosition() const;
        int getCastle() const;
        void setCastle(); // only for castling
    private:
        int piece; //-2 == wall, -1 = empty, 0 = pawn, 1 = rook, 2 = knight, 3 = bishop, 4 = queen, 5 = white king, 6 = black king
        int color; //0 = white, 1 = black
        int pawn; //0 = if first turn, 1 = after first turn
        int castle; //0 = has not moved, 1 = has moved
        std::string unicode;
        std::pair<int ,int> position; 
};

#endif