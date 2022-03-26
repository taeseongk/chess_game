#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <iostream>
#include <utility>
#include <sstream>
#include <cmath>
#include <queue>
#include "chessPiece.h"

class chessBoard {
    public:
        chessBoard();
        ~chessBoard();
        bool checkMove(chessPiece &piece, int x, int y) const;
        bool checkPiece1(chessPiece piece);
        bool checkPiece2(chessPiece piece);
        bool checkSurr(chessPiece piece) const;
        bool isCheck(chessPiece piece) const;
        bool isCheckmate(int color);
        bool isStalemate(int color);
        bool checkQueue(int color, int prevX, int prevY, int x, int y, chessPiece &piece);
        bool checkArray(int color, int prevX, int prevY, int x, int y, chessPiece &piece);
        bool canCastleQueen(int color); //castle queenside
        bool canCastleKing(int color); //castle kingside
        void castleQueen(int color);
        void castleKing(int color);
        void promotion(int color, char p, int x, int y);
        bool makeMove(int color);
        bool movePiece(int color, int prevX, int prevY, int x, int y, chessPiece &p, bool temp1, bool temp2, bool temp3);
        void printBoard(int color) const;
    private:
        chessPiece** whiteBoard;
        chessPiece** blackBoard;
        std::vector<chessPiece> whitePieces; //lists remaining pieces
        std::vector<chessPiece> blackPieces;
        std::deque<chessPiece> whiteCheck; //pieces putting white at check
        std::deque<chessPiece> blackCheck; //pieces putting black at check
        chessPiece reservePiece;
        std::pair<int, int> reservePos;      
};

#endif