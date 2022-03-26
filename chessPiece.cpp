#include "chessPiece.h"

chessPiece::chessPiece() {
    piece = -1;
    color = -1;
    unicode = " ";
}
chessPiece::chessPiece(int c) {
    piece = -2;
    color = !c ? 0 : 1;
    unicode = "";
}
chessPiece::chessPiece(int c, int n) {
    position.first = -1;
    position.first = -1;
    if (!c) { //white
        color = 0;
        switch(n) {
            case 0: //pawn
                piece = 0;
                unicode = "\u2659";
                pawn = 0;
                break;
            case 1: //rook
                piece = 1;
                unicode = "\u2656";
                pawn = -1;
                castle = 0;
                break;
            case 2: //knight
                piece = 2;
                unicode = "\u2658";
                pawn = -1;
                break;
            case 3: //bishop
                piece = 3;
                unicode = "\u2657";
                pawn = -1;
                break;
            case 4: //queen
                piece = 4;
                unicode = "\u2655";
                pawn = -1;
                break;
            case 5: //white king
                piece = 5;
                unicode = "\u2654";
                pawn = -1;
                castle = 0;
                break;
            default:
                break;
        }
    }
    else {
        color = 1;
        switch(n) {
            case 0: //pawn
                piece = 0;
                unicode = "\u265F";
                pawn = 0;
                break;
            case 1: //rook
                piece = 1;
                unicode = "\u265C";
                pawn = -1;
                castle = 0;
                break;
            case 2: //knight
                piece = 2;
                unicode = "\u265E";
                pawn = -1;
                break;
            case 3: //bishop
                piece = 3;
                unicode = "\u265D";
                pawn = -1;
                break;
            case 4: //queen
                piece = 4;
                unicode = "\u265B";
                pawn = -1;
                break;
            case 5: //black king
                piece = 6;
                unicode = "\u265A";
                pawn = -1;
                castle = 0;
                break;
            default:
                break;
        }
    }
}

void chessPiece::printPiece() const {
    std::cout << unicode;
}

int chessPiece::getPiece() const {
    return piece;
}

int chessPiece::getColor() const {
    return color;
}

void chessPiece::setPawn() {
    pawn++;
}

int chessPiece::getPawn() const {
    return pawn;
}

void chessPiece::setPosition(int x, int y) {
    position.first = x;
    position.second = y;
}

std::pair<int, int> chessPiece::getPosition() const { 
    return position;
}

int chessPiece::getCastle() const {
    return castle;
}

void chessPiece::setCastle() {
    castle++;
}

