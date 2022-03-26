#include "chessBoard.h"

chessBoard::chessBoard() {
   chessPiece wPawn = chessPiece(0, 0);
   chessPiece wRook = chessPiece(0, 1);
   chessPiece wKnight = chessPiece(0, 2);
   chessPiece wBishop = chessPiece(0, 3);
   chessPiece wQueen = chessPiece(0, 4);
   chessPiece wKing = chessPiece(0, 5);
   chessPiece bPawn = chessPiece(1, 0);
   chessPiece bRook = chessPiece(1, 1);
   chessPiece bKnight = chessPiece(1, 2);
   chessPiece bBishop = chessPiece(1, 3);
   chessPiece bQueen = chessPiece(1, 4);
   chessPiece bKing = chessPiece(1, 5);
   chessPiece blackPiece[16] = {bRook, bKnight, bBishop, bQueen, bKing, bBishop, bKnight, bRook, 
                                 bPawn, bPawn, bPawn, bPawn, bPawn, bPawn, bPawn, bPawn};
   int bCounter = 0;
   int bCounter1 = 0;
   int bCounter2 = 15;
   chessPiece whitePiece[16] = {wPawn, wPawn, wPawn, wPawn, wPawn, wPawn, wPawn, wPawn, 
                                 wRook, wKnight, wBishop, wQueen, wKing, wBishop, wKnight, wRook};
   whitePieces = new chessPiece[16];
   blackPieces = new chessPiece[16];
   int wCounter1 = 0;
   int wCounter2 = 15;
   whiteBoard = new chessPiece*[12];
   blackBoard = new chessPiece*[12];
   for (int i = 0; i < 12; i++) {
      whiteBoard[i] = new chessPiece[12];
      blackBoard[i] = new chessPiece[12];
   }
   for (int i = 0; i < 12; i++) {
      for (int j = 0; j < 12; j++) {
         if (j > 1 && j < 10) {
            if (i == 2 || i == 3) {
               whiteBoard[i][j] = blackPiece[bCounter1];
               whiteBoard[i][j].setPosition(i, j);
               bCounter1++;
               blackBoard[i][j] = whitePiece[wCounter2];
               blackBoard[i][j].setPosition(i, j);
               wCounter2--;
            }
            else if (i == 8 || i == 9) {
               whitePieces[wCounter1] = whitePiece[wCounter1];
               whitePieces[wCounter1].setPosition(i, j);
               whiteBoard[i][j] = whitePieces[wCounter1];
               wCounter1++;
               blackPieces[bCounter] = blackPiece[bCounter2];
               blackPieces[bCounter].setPosition(i, j);
               blackBoard[i][j] = blackPieces[bCounter];
               bCounter2--;
               bCounter++;
            }
            else if (i > 3 && i < 8) {
               chessPiece emptyPiece = chessPiece();
               whiteBoard[i][j] = emptyPiece;
               blackBoard[i][j] = emptyPiece;
            }
            else {
               chessPiece wWall = chessPiece(0);
               chessPiece bWall = chessPiece(1);
               whiteBoard[i][j] = wWall;
               blackBoard[i][j] = bWall;
            }
         }
         else {
            chessPiece wWall = chessPiece(0);
            chessPiece bWall = chessPiece(1);
            whiteBoard[i][j] = wWall;
            blackBoard[i][j] = bWall;
         }
      }
   }
}

chessBoard::~chessBoard() {
   delete whiteBoard;
   delete blackBoard;
}

void chessBoard::test() {

}

void chessBoard::printPieces(int color) const {
   chessPiece* array;
   array = !color ? whitePieces : blackPieces; 
   for (int i = 0; i < 16; i++) {
      std::cout << i << ": ";
      array[i].printPiece();  
      std::cout << std::endl; 
   }
}

bool chessBoard::checkMove(chessPiece &piece, int x, int y) const {
   int i = piece.getPosition().first;
   int j = piece.getPosition().second;
   int color = piece.getColor();
   chessPiece** board;
   board = !color ? whiteBoard : blackBoard;
   switch (piece.getPiece()) {
      case 0: 
         if (!piece.getPawn()) {
            if (i-1 == x && j == y && board[x][y].getPiece() == -1) { //if move is forward once and no piece in front
               piece.setPawn();
               return true;
            }  
            else if(i-2 == x && j == y && board[x+1][y].getPiece() == -1 && board[x][y].getPiece() == -1) { //if move is forward twice
               piece.setPawn();
               return true;
            }
            else if (((i-1 == x && j-1 == y) || (i-1 == x && j+1 == y)) && board[x][y].getColor() == !color) {
               return true;
            }
         }
         else if (piece.getPawn()) {
            if (i-1 == x && j == y) { //if move is forward once
               if (whiteBoard[x][y].getPiece() == -1 && !piece.getColor()) { //if there is no piece in front
                  return true;
               }
               else if(blackBoard[x][y].getPiece() == -1 && piece.getColor()) {
                  return true;
               }
            }  
            else if (((i-1 == x && j-1 == y) || (i-1 == x && j+1 == y)) && whiteBoard[x][y].getColor() == 1 && !piece.getColor()) {
               return true;
            }
            else if (((i-1 == x && j-1 == y) || (i-1 == x && j+1 == y)) && blackBoard[x][y].getColor() == 0 && piece.getColor()) {
               return true;
            }
         }
         break;
      case 1:
         if (i-x >= 1 && j == y) { //if move is forward
            for (int k = i-1; k > x; k--) {
               if (whiteBoard[k][y].getPiece() != -1 && !piece.getColor()) {
                  return false;
               }
               else if(blackBoard[k][y].getPiece() != -1 && piece.getColor()) {
                  return false;
               }
            }
            goto HERE1;
         }
         else if (x-i >= 1 && j == y) { //if move is backward
            for (int k = i+1; k < x; k++) {
               if (whiteBoard[k][y].getPiece() != -1 && !piece.getColor()) {
                  return false;
               }
               else if(blackBoard[k][y].getPiece() != -1 && piece.getColor()) {
                  return false;
               }
            }
            goto HERE1;
         }
         else if (i == x && j-y >= 1) { //if move is leftward
            for (int k = j-1; k > y; k--) {
               if (whiteBoard[x][k].getPiece() != -1 && !piece.getColor()) {
                  return false;
               }
               else if(blackBoard[x][k].getPiece() != -1 && piece.getColor()) {
                  return false;
               }
            }
            goto HERE1;
         }
         else if (i == x && y-j >= 1) { //if move is rightward
            for (int k = j+1; k < y; k++) {
               if (whiteBoard[x][k].getPiece() != -1 && !piece.getColor()) {
                  return false;
               }
               else if(blackBoard[x][k].getPiece() != -1 && piece.getColor()) {
                  return false;
               }
            }
            goto HERE1;
         }
         if (false) {
            HERE1:
            if (piece.getColor() != whiteBoard[x][y].getColor() && !piece.getColor()) {
               if (piece.getPiece() == 1 || piece.getPiece() == 5) {
                  piece.setCastle(); //after move has been made
               }
               return true;
            }
            else if (piece.getColor() != blackBoard[x][y].getColor() && piece.getColor()) {
               if (piece.getPiece() == 1 || piece.getPiece() == 5) {
                  piece.setCastle();
               }
               return true;
            }
         }
         break;
      case 2:
         if ((i+1 == x && j-2 == y) || (i-1 == x && j-2 == y) || (i-2 == x && j-1 == y) || (i-2 == x && j+1 == y) || 
         (i-1 == x && j+2 == y) || (i-1 == x && j+2 == y) || (i-2 == x && j-1 == y) || (i-2 == x && j+1 == y)) {
            return true;
         }
         break;
      case 3:
         if (i-x >= 1 && j-y >= 1 && i-x == j-y) { //if move is up-left
            for (int k = 1; k < i-x; k++) {
               if (whiteBoard[i-k][j-k].getPiece() != -1 && !piece.getColor()) {
                  return false;
               }
               else if(blackBoard[i-k][j-k].getPiece() != -1 && piece.getColor()) {
                  return false;
               }
            }
            goto HERE2;
         }
         else if (x-i >= 1 && j-y >= 1 && x-i == j-y) { //if move is down-left
            for (int k = 1; k < x-i; k++) {
               if (whiteBoard[i+k][j-k].getPiece() != -1 && !piece.getColor()) {
                  return false;
               }
               else if(blackBoard[i+k][j-k].getPiece() != -1 && piece.getColor()) {
                  return false;
               }
            }
            goto HERE2;
         }
         else if (i-x >= 1 && y-j >= 1 && i-x == y-j) { //if move is up-right
            for (int k = 1; k < i-x; k++) {
               if (whiteBoard[i-k][j+k].getPiece() != -1 && !piece.getColor()) {
                  return false;
               }
               else if(blackBoard[i-k][j+k].getPiece() != -1 && piece.getColor()) {
                  return false;
               }
            }
            goto HERE2;
         }
         else if (x-i >= 1 && y-j >= 1 && x-i == y-j) { //if move is down-right
            for (int k = 1; k < x-i; k++) {
               if (whiteBoard[i+k][j+k].getPiece() != -1 && !piece.getColor()) {
                  return false;
               }
               else if(blackBoard[i+k][j+k].getPiece() != -1 && piece.getColor()) {
                  return false;
               }
            }
            goto HERE2;
         }
         if (false) {
            HERE2:
            if (piece.getColor() != whiteBoard[x][y].getColor() && !piece.getColor()) {
               std::cout << "TEST" << std::endl;
               return true;
            }
            else if (piece.getColor() != blackBoard[x][y].getColor() && piece.getColor()) {
               return true;
            }
         }
         break;
      case 4:
         if (i-x >= 1 && j == y) { //if move is forward
            for (int k = i-1; k > x; k--) {
               if (whiteBoard[k][y].getPiece() != -1 && !piece.getColor()) {
                  return false;
               }
               else if(blackBoard[k][y].getPiece() != -1 && piece.getColor()) {
                  return false;
               }
            }
            goto HERE3;
         }
         else if (x-i >= 1 && j == y) { //if move is backward
            for (int k = i+1; k < x; k++) {
               if (whiteBoard[k][y].getPiece() != -1 && !piece.getColor()) {
                  return false;
               }
               else if(blackBoard[k][y].getPiece() != -1 && piece.getColor()) {
                  return false;
               }
            }
            goto HERE3;
         }
         else if (i == x && j-y >= 1) { //if move is leftward
            for (int k = j-1; k > y; k--) {
               if (whiteBoard[x][k].getPiece() != -1 && !piece.getColor()) {
                  return false;
               }
               else if(blackBoard[x][k].getPiece() != -1 && piece.getColor()) {
                  return false;
               }
            }
            goto HERE3;
         }
         else if (i == x && y-j >= 1) { //if move is rightward
            for (int k = j+1; k < y; k++) {
               if (whiteBoard[x][k].getPiece() != -1 && !piece.getColor()) {
                  return false;
               }
               else if(blackBoard[x][k].getPiece() != -1 && piece.getColor()) {
                  return false;
               }
            }
            goto HERE3;
         }
         else if (i-x >= 1 && j-y >= 1 && i-x == j-y) { //if move is up-left
            for (int k = 1; k < i-x; k++) {
               if (whiteBoard[i-k][j-k].getPiece() != -1 && !piece.getColor()) {
                  return false;
               }
               else if(blackBoard[i-k][j-k].getPiece() != -1 && piece.getColor()) {
                  return false;
               }
            }
            goto HERE3;
         }
         else if (x-i >= 1 && j-y >= 1 && x-i == j-y) { //if move is down-left
            for (int k = 1; k < x-i; k++) {
               if (whiteBoard[i+k][j-k].getPiece() != -1 && !piece.getColor()) {
                  return false;
               }
               else if(blackBoard[i+k][j-k].getPiece() != -1 && piece.getColor()) {
                  return false;
               }
            }
            goto HERE3;
         }
         else if (i-x >= 1 && y-j >= 1 && i-x == y-j) { //if move is up-right
            for (int k = 1; k < i-x; k++) {
               if (whiteBoard[i-k][j+k].getPiece() != -1 && !piece.getColor()) {
                  return false;
               }
               else if(blackBoard[i-k][j+k].getPiece() != -1 && piece.getColor()) {
                  return false;
               }
            }
            goto HERE3;
         }
         else if (x-i >= 1 && y-j >= 1 && x-i == y-j) { //if move is down-right
            for (int k = 1; k < x-i; k++) {
               if (whiteBoard[i+k][j+k].getPiece() != -1 && !piece.getColor()) {
                  return false;
               }
               else if(blackBoard[i+k][j+k].getPiece() != -1 && piece.getColor()) {
                  return false;
               }
            }
            goto HERE3;
         }
         if (false) {
            HERE3:
            if (whiteBoard[x][y].getColor() != 0 && !piece.getColor()) {
               return true;
            }
            else if (blackBoard[x][y].getColor() != 1 && piece.getColor()) {
               return true;
            }
         }
         break;
      case 5:
         if (i-x == 1 && j == y) { //if move is forward
            if (whiteBoard[x][y].getPiece() != -1) {
               return false;
            }
            goto HERE4;
         }
         else if (x-i == 1 && j == y) { //if move is backward
            if (whiteBoard[x][y].getPiece() != -1) {
               return false;
            }
            goto HERE4;
         }
         else if (i == x && j-y == 1) { //if move is leftward
            if (whiteBoard[x][y].getPiece() != -1) {
               return false;
            }
            goto HERE4;
         }
         else if (i == x && y-j == 1) { //if move is rightward
            if (whiteBoard[x][y].getPiece() != -1) {
               return false;
            }
            goto HERE4;
         }
         else if (i-x == 1 && j-y == 1) { //if move is up-left
            if (whiteBoard[x][y].getPiece() != -1) {
               return false;
            }
            goto HERE4;
         }
         else if (x-i == 1 && j-y == 1) { //if move is down-left
            if (whiteBoard[x][y].getPiece() != -1) {
               return false;
            }
            goto HERE4;
         }
         else if (i-x == 1 && y-j == 1) { //if move is up-right
            if (whiteBoard[x][y].getPiece() != -1) {
               return false;
            }
            goto HERE4;
         }
         else if (x-i == 1 && y-j == 1) { //if move is down-right
            if (whiteBoard[x][y].getPiece() != -1) {
               return false;
            }
            goto HERE4;
         }
         if (false) {
            HERE4:
            if (whiteBoard[x][y].getColor() != 0) {
               return true;
            }
         }
         break;
      case 6:
         if (i-x == 1 && j == y) { //if move is forward
            if (blackBoard[x][y].getPiece() != -1) {
               return false;
            }
            goto HERE5;
         }
         else if (x-i == 1 && j == y) { //if move is backward
            if (blackBoard[x][y].getPiece() != -1) {
               return false;
            }
            goto HERE5;
         }
         else if (i == x && j-y == 1) { //if move is leftward
            if (blackBoard[x][y].getPiece() != -1) {
               return false;
            }
            goto HERE5;
         }
         else if (i == x && y-j == 1) { //if move is rightward
            if (blackBoard[x][y].getPiece() != -1) {
               return false;
            }
            goto HERE5;
         }
         else if (i-x == 1 && j-y == 1) { //if move is up-left
            if (blackBoard[x][y].getPiece() != -1) {
               return false;
            }
            goto HERE5;
         }
         else if (x-i == 1 && j-y == 1) { //if move is down-left
            if (blackBoard[x][y].getPiece() != -1) {
               return false;
            }
            goto HERE5;
         }
         else if (i-x == 1 && y-j == 1) { //if move is up-right
            if (blackBoard[x][y].getPiece() != -1) {
               return false;
            }
            goto HERE5;
         }
         else if (x-i == 1 && y-j == 1) { //if move is down-right
            if (blackBoard[x][y].getPiece() != -1) {
               return false;
            }
            goto HERE5;
         }
         if (false) {
            HERE5:
            if (blackBoard[x][y].getColor() != 1) {
               return true;
            }
         }
         break;
      default:
         break;
   }
   return false;
}

bool chessBoard::checkSurr(chessPiece piece) const {
   int i = piece.getPosition().first;
   int j = piece.getPosition().second;
   switch (piece.getPiece()) {
      case 0:
         if ((whiteBoard[i-1][j].getPiece() == -1 || whiteBoard[i-1][j-1].getColor() == 1 ||
         whiteBoard[i-1][j+1].getColor() == 1) && !piece.getColor()) {
            return true;
         }
         else if ((blackBoard[i-1][j].getPiece() == -1 || blackBoard[i-1][j-1].getColor() == 0 ||
         blackBoard[i-1][j+1].getColor() == 0) && piece.getColor()) {
            return true;
         }
         break;
      case 1:
         if ((whiteBoard[i-1][j].getColor() != 0 || whiteBoard[i+1][j].getColor() != 0 || 
         whiteBoard[i][j-1].getColor() != 0 || whiteBoard[i][j+1].getColor() != 0) && !piece.getColor()) {
            return true;
         }
         else if ((blackBoard[i-1][j].getColor() != 1 || blackBoard[i+1][j].getColor() != 1 || 
         blackBoard[i][j-1].getColor() != 1 || blackBoard[i][j+1].getColor() != 1) && piece.getColor()) {
            return true;
         }
         break;
      case 2:
         if ((whiteBoard[i+1][j-2].getColor() != 0 || whiteBoard[i-1][j-2].getColor() != 0 || whiteBoard[i-2][j-1].getColor() != 0 || 
         whiteBoard[i-2][j+1].getColor() != 0 || whiteBoard[i-1][j+2].getColor() != 0 || whiteBoard[i-1][j+2].getColor() != 0 || 
         whiteBoard[i-2][j-1].getColor() != 0 || whiteBoard[i-2][j+1].getColor() != 0) && !piece.getColor()) {
            return true;
         }
         else if ((blackBoard[i+1][j-2].getColor() != 1 || blackBoard[i-1][j-2].getColor() != 1 || blackBoard[i-2][j-1].getColor() != 1 || 
         blackBoard[i-2][j+1].getColor() != 1 || blackBoard[i-1][j+2].getColor() != 1 || blackBoard[i-1][j+2].getColor() != 1 || 
         blackBoard[i-2][j-1].getColor() != 1 || blackBoard[i-2][j+1].getColor() != 1) && piece.getColor()) {
            return true;
         }
         break;
      case 3:
         if ((whiteBoard[i-1][j-1].getColor() != 0 || whiteBoard[i-1][j+1].getColor() != 0 ||
         whiteBoard[i+1][j-1].getColor() != 0 || whiteBoard[i+1][j+1].getColor() != 0) && !piece.getColor()) {
            return true;
         }
         else if ((blackBoard[i-1][j-1].getColor() != 1 || blackBoard[i-1][j+1].getColor() != 1 ||
         blackBoard[i+1][j-1].getColor() != 1 || blackBoard[i+1][j+1].getColor() != 1) && piece.getColor()) {
            return true;
         }
         break;
      case 4:
         if ((whiteBoard[i-1][j].getColor() != 0 || whiteBoard[i+1][j].getColor() != 0 || whiteBoard[i][j-1].getColor() != 0 || 
         whiteBoard[i][j+1].getColor() != 0 || whiteBoard[i-1][j-1].getColor() != 0 || whiteBoard[i-1][j+1].getColor() != 0 || 
         whiteBoard[i+1][j-1].getColor() != 0 || whiteBoard[i+1][j+1].getColor() != 0) && !piece.getColor()) {
            return true;
         }
         else if ((blackBoard[i-1][j].getColor() != 1 || blackBoard[i+1][j].getColor() != 1 || blackBoard[i][j-1].getColor() != 1 || 
         blackBoard[i][j+1].getColor() != 1 || blackBoard[i-1][j-1].getColor() != 1 || blackBoard[i-1][j+1].getColor() != 1 || 
         blackBoard[i+1][j-1].getColor() != 1 || blackBoard[i+1][j+1].getColor() != 1) && piece.getColor()) {
            return true;
         }
         break;
      case 5:
         if (whiteBoard[i-1][j].getColor() != 0 || whiteBoard[i+1][j].getColor() != 0 || whiteBoard[i][j-1].getColor() != 0 || 
         whiteBoard[i][j+1].getColor() != 0 || whiteBoard[i-1][j-1].getColor() != 0 || whiteBoard[i-1][j+1].getColor() != 0 || 
         whiteBoard[i+1][j-1].getColor() != 0 || whiteBoard[i+1][j+1].getColor() != 0) {
            return true;
         }
      case 6:
         if (blackBoard[i-1][j].getColor() != 1 || blackBoard[i+1][j].getColor() != 1 || blackBoard[i][j-1].getColor() != 1 || 
         blackBoard[i][j+1].getColor() != 1 || blackBoard[i-1][j-1].getColor() != 1 || blackBoard[i-1][j+1].getColor() != 1 || 
         blackBoard[i+1][j-1].getColor() != 1 || blackBoard[i+1][j+1].getColor() != 1) {
            return true;
         }
         break;
      default:
         break;
   }
   return false;
}

bool chessBoard::isCheck(chessPiece piece) const { //return true if move caused check for opponent
   int i = piece.getPosition().first;
   int j = piece.getPosition().second;
   switch (piece.getPiece()) {
      case 0:
         if ((whiteBoard[i-1][j-1].getPiece() == 6 || whiteBoard[i-1][j+1].getPiece() == 6) && !piece.getColor()) {
            return true;
         }
         else if ((blackBoard[i-1][j-1].getPiece() == 5 || blackBoard[i-1][j+1].getPiece() == 5) && piece.getColor()) {
            return true;
         }
         break;
      case 1:
         for (int k = 1; k < 8; k++) { //left
            if ((whiteBoard[i][j-k].getPiece() == 6 && !piece.getColor()) || 
            (blackBoard[i][j-k].getPiece() == 5 && piece.getColor())) {
               return true;
            } 
            else if ((whiteBoard[i][j-k].getPiece() != -1 && !piece.getColor()) || 
            (blackBoard[i][j-k].getPiece() != -1 && piece.getColor())) {
               break;
            }
         }
         for (int k = 1; k < 8; k++) { //right
            if ((whiteBoard[i][j+k].getPiece() == 6 && !piece.getColor()) || 
            (blackBoard[i][j+k].getPiece() == 5 && piece.getColor())) {
               return true;
            } 
            else if ((whiteBoard[i][j+k].getPiece() != -1 && !piece.getColor()) || 
            (blackBoard[i][j+k].getPiece() != -1 && piece.getColor())) {
               break;
            }
         }
         for (int k = 1; k < 8; k++) { //up
            if ((whiteBoard[i-k][j].getPiece() == 6 && !piece.getColor()) || 
            (blackBoard[i-k][j].getPiece() == 5 && piece.getColor())) {
               return true;
            } 
            else if ((whiteBoard[i-k][j].getPiece() != -1 && !piece.getColor()) || 
            (blackBoard[i-k][j].getPiece() != -1 && piece.getColor())) {
               break;
            }
         }
         for (int k = 1; k < 8; k++) { //down
            if ((whiteBoard[i+k][j].getPiece() == 6 && !piece.getColor()) || 
            (blackBoard[i+k][j].getPiece() == 5 && piece.getColor())) {
               return true;
            } 
            else if ((whiteBoard[i+k][j].getPiece() != -1 && !piece.getColor()) || 
            (blackBoard[i+k][j].getPiece() != -1 && piece.getColor())) {
               break;
            }
         }
         break;
      case 2:
         if ((whiteBoard[i+1][j-2].getPiece() == 6 || whiteBoard[i-1][j-2].getPiece() == 6 || whiteBoard[i-2][j-1].getPiece() == 6 || 
         whiteBoard[i-2][j+1].getPiece() == 6 || whiteBoard[i-1][j+2].getPiece() == 6 || whiteBoard[i-1][j+2].getPiece() == 6 || 
         whiteBoard[i-2][j-1].getPiece() == 6 || whiteBoard[i-2][j+1].getPiece() == 6) && !piece.getColor()) {
            return true;
         }
         else if ((blackBoard[i+1][j-2].getPiece() == 5 || blackBoard[i-1][j-2].getPiece() == 5 || blackBoard[i-2][j-1].getPiece() == 5 || 
         blackBoard[i-2][j+1].getPiece() == 5 || blackBoard[i-1][j+2].getPiece() == 5 || blackBoard[i-1][j+2].getPiece() == 5 || 
         blackBoard[i-2][j-1].getPiece() == 5 || blackBoard[i-2][j+1].getPiece() == 5) && piece.getColor()) {
            return true;
         }
         break;
      case 3:
         for (int k = 1; k < 8; k++) { //up-left
            if ((whiteBoard[i-k][j-k].getPiece() == 6 && !piece.getColor()) || 
            (blackBoard[i-k][j-k].getPiece() == 5 && piece.getColor())) {
               return true;
            } 
            else if ((whiteBoard[i-k][j-k].getPiece() != -1 && !piece.getColor()) || 
            (blackBoard[i-k][j-k].getPiece() != -1 && piece.getColor())) {
               break;
            }
         }
         for (int k = 1; k < 8; k++) { //up-right
            if ((whiteBoard[i-k][j+k].getPiece() == 6 && !piece.getColor()) || 
            (blackBoard[i-k][j+k].getPiece() == 5 && piece.getColor())) {
               return true;
            } 
            else if ((whiteBoard[i-k][j+k].getPiece() != -1 && !piece.getColor()) || 
            (blackBoard[i-k][j+k].getPiece() != -1 && piece.getColor())) {
               break;
            }
         }
         for (int k = 1; k < 8; k++) { //down-left
            if ((whiteBoard[i+k][j-k].getPiece() == 6 && !piece.getColor()) || 
            (blackBoard[i+k][j-k].getPiece() == 5 && piece.getColor())) {
               return true;
            } 
            else if ((whiteBoard[i+k][j-k].getPiece() != -1 && !piece.getColor()) || 
            (blackBoard[i+k][j-k].getPiece() != -1 && piece.getColor())) {
               break;
            }
         }
         for (int k = 1; k < 8; k++) { //down-right
            if ((whiteBoard[i+k][j+k].getPiece() == 6 && !piece.getColor()) || 
            (blackBoard[i+k][j+k].getPiece() == 5 && piece.getColor())) {
               return true;
            } 
            else if ((whiteBoard[i+k][j+k].getPiece() != -1 && !piece.getColor()) || 
            (blackBoard[i+k][j+k].getPiece() != -1 && piece.getColor())) {
               break;
            }
         }
         break;
      case 4:
         for (int k = 1; k < 8; k++) { //left
            if ((whiteBoard[i][j-k].getPiece() == 6 && !piece.getColor()) || 
            (blackBoard[i][j-k].getPiece() == 5 && piece.getColor())) {
               return true;
            } 
            else if ((whiteBoard[i][j-k].getPiece() != -1 && !piece.getColor()) || 
            (blackBoard[i][j-k].getPiece() != -1 && piece.getColor())) {
               break;
            }
         }
         for (int k = 1; k < 8; k++) { //right
            if ((whiteBoard[i][j+k].getPiece() == 6 && !piece.getColor()) || 
            (blackBoard[i][j+k].getPiece() == 5 && piece.getColor())) {
               return true;
            } 
            else if ((whiteBoard[i][j+k].getPiece() != -1 && !piece.getColor()) || 
            (blackBoard[i][j+k].getPiece() != -1 && piece.getColor())) {
               break;
            }
         }
         for (int k = 1; k < 8; k++) { //up
            if ((whiteBoard[i-k][j].getPiece() == 6 && !piece.getColor()) || 
            (blackBoard[i-k][j].getPiece() == 5 && piece.getColor())) {
               return true;
            } 
            else if ((whiteBoard[i-k][j].getPiece() != -1 && !piece.getColor()) || 
            (blackBoard[i-k][j].getPiece() != -1 && piece.getColor())) {
               break;
            }
         }
         for (int k = 1; k < 8; k++) { //down
            if ((whiteBoard[i+k][j].getPiece() == 6 && !piece.getColor()) || 
            (blackBoard[i+k][j].getPiece() == 5 && piece.getColor())) {
               return true;
            } 
            else if ((whiteBoard[i+k][j].getPiece() != -1 && !piece.getColor()) || 
            (blackBoard[i+k][j].getPiece() != -1 && piece.getColor())) {
               break;
            }
         }
         for (int k = 1; k < 8; k++) { //up-left
            if ((whiteBoard[i-k][j-k].getPiece() == 6 && !piece.getColor()) || 
            (blackBoard[i-k][j-k].getPiece() == 5 && piece.getColor())) {
               return true;
            } 
            else if ((whiteBoard[i-k][j-k].getPiece() != -1 && !piece.getColor()) || 
            (blackBoard[i-k][j-k].getPiece() != -1 && piece.getColor())) {
               break;
            }
         }
         for (int k = 1; k < 8; k++) { //up-right
            if ((whiteBoard[i-k][j+k].getPiece() == 6 && !piece.getColor()) || 
            (blackBoard[i-k][j+k].getPiece() == 5 && piece.getColor())) {
               return true;
            } 
            else if ((whiteBoard[i-k][j+k].getPiece() != -1 && !piece.getColor()) || 
            (blackBoard[i-k][j+k].getPiece() != -1 && piece.getColor())) {
               break;
            }
         }
         for (int k = 1; k < 8; k++) { //down-left
            if ((whiteBoard[i+k][j-k].getPiece() == 6 && !piece.getColor()) || 
            (blackBoard[i+k][j-k].getPiece() == 5 && piece.getColor())) {
               return true;
            } 
            else if ((whiteBoard[i+k][j-k].getPiece() != -1 && !piece.getColor()) || 
            (blackBoard[i+k][j-k].getPiece() != -1 && piece.getColor())) {
               break;
            }
         }
         for (int k = 1; k < 8; k++) { //down-right
            if ((whiteBoard[i+k][j+k].getPiece() == 6 && !piece.getColor()) || 
            (blackBoard[i+k][j+k].getPiece() == 5 && piece.getColor())) {
               return true;
            } 
            else if ((whiteBoard[i+k][j+k].getPiece() != -1 && !piece.getColor()) || 
            (blackBoard[i+k][j+k].getPiece() != -1 && piece.getColor())) {
               break;
            }
         }
         break;
      default:
         break;
   }
   return false;
}

bool chessBoard::checkQueue(int color) {
   std::queue<chessPiece> q;
   q = !color ? whiteCheck : blackCheck;
   while (!q.empty()) { //checks if piece can be moved otherwise causing check
      if (isCheck(q.front())) {
         return false;
      }
      q.pop();
   }
   return true;
}

bool chessBoard::checkPiece(chessPiece piece) { //first piece moves to prevent check, second piece causes check
   int i = piece.getPosition().first;
   int j = piece.getPosition().second;
   int color = piece.getColor();
   switch (piece.getPiece()) {
      case 0:
         if (!piece.getPawn()) {
            movePiece(color, i, j, i-1, j, piece, true);
            if (i-1 == x && j == y) { //if move is forward once
               if (whiteBoard[x][y].getPiece() == -1 && !piece.getColor()) { //if there is no piece in front
                  piece.setPawn();
                  return true;
               }
               else if (blackBoard[x][y].getPiece() == -1 && piece.getColor()) {
                  piece.setPawn();
                  return true;
               }
            }  
            else if(i-2 == x && j == y) { //if move is forward twice
               if (whiteBoard[x+1][y].getPiece() == -1 && whiteBoard[x][y].getPiece() == -1 && !piece.getColor()) {
                  piece.setPawn();
                  return true;
               }
               else if (blackBoard[x+1][y].getPiece() == -1 && blackBoard[x][y].getPiece() == -1 && piece.getColor()){
                  piece.setPawn();
                  return true;
               }
            }
            else if (((i-1 == x && j-1 == y) || (i-1 == x && j+1 == y)) && whiteBoard[x][y].getColor() == 1 && !piece.getColor()) {
               return true;
            }
            else if (((i-1 == x && j-1 == y) || (i-1 == x && j+1 == y)) && blackBoard[x][y].getColor() == 0 && piece.getColor()) {
               return true;
            }
         }
         else if (piece.getPawn()) {
            if (i-1 == x && j == y) { //if move is forward once
               if (whiteBoard[x][y].getPiece() == -1 && !piece.getColor()) { //if there is no piece in front
                  return true;
               }
               else if(blackBoard[x][y].getPiece() == -1 && piece.getColor()) {
                  return true;
               }
            }  
            else if (((i-1 == x && j-1 == y) || (i-1 == x && j+1 == y)) && whiteBoard[x][y].getColor() == 1 && !piece.getColor()) {
               return true;
            }
            else if (((i-1 == x && j-1 == y) || (i-1 == x && j+1 == y)) && blackBoard[x][y].getColor() == 0 && piece.getColor()) {
               return true;
            }
         }
         break;
      case 1:
         for (int k = 1; k < 8; k++) { //left
            if ((whiteBoard[i][j-k].getPiece() == 6 && !piece.getColor()) || 
            (blackBoard[i][j-k].getPiece() == 5 && piece.getColor())) {
               return true;
            } 
            else if ((whiteBoard[i][j-k].getPiece() != -1 && !piece.getColor()) || 
            (blackBoard[i][j-k].getPiece() != -1 && piece.getColor())) {
               break;
            }
         }
         for (int k = 1; k < 8; k++) { //right
            if ((whiteBoard[i][j+k].getPiece() == 6 && !piece.getColor()) || 
            (blackBoard[i][j+k].getPiece() == 5 && piece.getColor())) {
               return true;
            } 
            else if ((whiteBoard[i][j+k].getPiece() != -1 && !piece.getColor()) || 
            (blackBoard[i][j+k].getPiece() != -1 && piece.getColor())) {
               break;
            }
         }
         for (int k = 1; k < 8; k++) { //up
            if ((whiteBoard[i-k][j].getPiece() == 6 && !piece.getColor()) || 
            (blackBoard[i-k][j].getPiece() == 5 && piece.getColor())) {
               return true;
            } 
            else if ((whiteBoard[i-k][j].getPiece() != -1 && !piece.getColor()) || 
            (blackBoard[i-k][j].getPiece() != -1 && piece.getColor())) {
               break;
            }
         }
         for (int k = 1; k < 8; k++) { //down
            if ((whiteBoard[i+k][j].getPiece() == 6 && !piece.getColor()) || 
            (blackBoard[i+k][j].getPiece() == 5 && piece.getColor())) {
               return true;
            } 
            else if ((whiteBoard[i+k][j].getPiece() != -1 && !piece.getColor()) || 
            (blackBoard[i+k][j].getPiece() != -1 && piece.getColor())) {
               break;
            }
         }
         break;
      case 2:
         if ((whiteBoard[i+1][j-2].getPiece() == 6 || whiteBoard[i-1][j-2].getPiece() == 6 || whiteBoard[i-2][j-1].getPiece() == 6 || 
         whiteBoard[i-2][j+1].getPiece() == 6 || whiteBoard[i-1][j+2].getPiece() == 6 || whiteBoard[i-1][j+2].getPiece() == 6 || 
         whiteBoard[i-2][j-1].getPiece() == 6 || whiteBoard[i-2][j+1].getPiece() == 6) && !piece.getColor()) {
            return true;
         }
         else if ((blackBoard[i+1][j-2].getPiece() == 5 || blackBoard[i-1][j-2].getPiece() == 5 || blackBoard[i-2][j-1].getPiece() == 5 || 
         blackBoard[i-2][j+1].getPiece() == 5 || blackBoard[i-1][j+2].getPiece() == 5 || blackBoard[i-1][j+2].getPiece() == 5 || 
         blackBoard[i-2][j-1].getPiece() == 5 || blackBoard[i-2][j+1].getPiece() == 5) && piece.getColor()) {
            return true;
         }
         break;
      case 3:
         for (int k = 1; k < 8; k++) { //up-left
            if ((whiteBoard[i-k][j-k].getPiece() == 6 && !piece.getColor()) || 
            (blackBoard[i-k][j-k].getPiece() == 5 && piece.getColor())) {
               return true;
            } 
            else if ((whiteBoard[i-k][j-k].getPiece() != -1 && !piece.getColor()) || 
            (blackBoard[i-k][j-k].getPiece() != -1 && piece.getColor())) {
               break;
            }
         }
         for (int k = 1; k < 8; k++) { //up-right
            if ((whiteBoard[i-k][j+k].getPiece() == 6 && !piece.getColor()) || 
            (blackBoard[i-k][j+k].getPiece() == 5 && piece.getColor())) {
               return true;
            } 
            else if ((whiteBoard[i-k][j+k].getPiece() != -1 && !piece.getColor()) || 
            (blackBoard[i-k][j+k].getPiece() != -1 && piece.getColor())) {
               break;
            }
         }
         for (int k = 1; k < 8; k++) { //down-left
            if ((whiteBoard[i+k][j-k].getPiece() == 6 && !piece.getColor()) || 
            (blackBoard[i+k][j-k].getPiece() == 5 && piece.getColor())) {
               return true;
            } 
            else if ((whiteBoard[i+k][j-k].getPiece() != -1 && !piece.getColor()) || 
            (blackBoard[i+k][j-k].getPiece() != -1 && piece.getColor())) {
               break;
            }
         }
         for (int k = 1; k < 8; k++) { //down-right
            if ((whiteBoard[i+k][j+k].getPiece() == 6 && !piece.getColor()) || 
            (blackBoard[i+k][j+k].getPiece() == 5 && piece.getColor())) {
               return true;
            } 
            else if ((whiteBoard[i+k][j+k].getPiece() != -1 && !piece.getColor()) || 
            (blackBoard[i+k][j+k].getPiece() != -1 && piece.getColor())) {
               break;
            }
         }
         break;
      case 4:
         for (int k = 1; k < 8; k++) { //left
            if ((whiteBoard[i][j-k].getPiece() == 6 && !piece.getColor()) || 
            (blackBoard[i][j-k].getPiece() == 5 && piece.getColor())) {
               return true;
            } 
            else if ((whiteBoard[i][j-k].getPiece() != -1 && !piece.getColor()) || 
            (blackBoard[i][j-k].getPiece() != -1 && piece.getColor())) {
               break;
            }
         }
         for (int k = 1; k < 8; k++) { //right
            if ((whiteBoard[i][j+k].getPiece() == 6 && !piece.getColor()) || 
            (blackBoard[i][j+k].getPiece() == 5 && piece.getColor())) {
               return true;
            } 
            else if ((whiteBoard[i][j+k].getPiece() != -1 && !piece.getColor()) || 
            (blackBoard[i][j+k].getPiece() != -1 && piece.getColor())) {
               break;
            }
         }
         for (int k = 1; k < 8; k++) { //up
            if ((whiteBoard[i-k][j].getPiece() == 6 && !piece.getColor()) || 
            (blackBoard[i-k][j].getPiece() == 5 && piece.getColor())) {
               return true;
            } 
            else if ((whiteBoard[i-k][j].getPiece() != -1 && !piece.getColor()) || 
            (blackBoard[i-k][j].getPiece() != -1 && piece.getColor())) {
               break;
            }
         }
         for (int k = 1; k < 8; k++) { //down
            if ((whiteBoard[i+k][j].getPiece() == 6 && !piece.getColor()) || 
            (blackBoard[i+k][j].getPiece() == 5 && piece.getColor())) {
               return true;
            } 
            else if ((whiteBoard[i+k][j].getPiece() != -1 && !piece.getColor()) || 
            (blackBoard[i+k][j].getPiece() != -1 && piece.getColor())) {
               break;
            }
         }
         for (int k = 1; k < 8; k++) { //up-left
            if ((whiteBoard[i-k][j-k].getPiece() == 6 && !piece.getColor()) || 
            (blackBoard[i-k][j-k].getPiece() == 5 && piece.getColor())) {
               return true;
            } 
            else if ((whiteBoard[i-k][j-k].getPiece() != -1 && !piece.getColor()) || 
            (blackBoard[i-k][j-k].getPiece() != -1 && piece.getColor())) {
               break;
            }
         }
         for (int k = 1; k < 8; k++) { //up-right
            if ((whiteBoard[i-k][j+k].getPiece() == 6 && !piece.getColor()) || 
            (blackBoard[i-k][j+k].getPiece() == 5 && piece.getColor())) {
               return true;
            } 
            else if ((whiteBoard[i-k][j+k].getPiece() != -1 && !piece.getColor()) || 
            (blackBoard[i-k][j+k].getPiece() != -1 && piece.getColor())) {
               break;
            }
         }
         for (int k = 1; k < 8; k++) { //down-left
            if ((whiteBoard[i+k][j-k].getPiece() == 6 && !piece.getColor()) || 
            (blackBoard[i+k][j-k].getPiece() == 5 && piece.getColor())) {
               return true;
            } 
            else if ((whiteBoard[i+k][j-k].getPiece() != -1 && !piece.getColor()) || 
            (blackBoard[i+k][j-k].getPiece() != -1 && piece.getColor())) {
               break;
            }
         }
         for (int k = 1; k < 8; k++) { //down-right
            if ((whiteBoard[i+k][j+k].getPiece() == 6 && !piece.getColor()) || 
            (blackBoard[i+k][j+k].getPiece() == 5 && piece.getColor())) {
               return true;
            } 
            else if ((whiteBoard[i+k][j+k].getPiece() != -1 && !piece.getColor()) || 
            (blackBoard[i+k][j+k].getPiece() != -1 && piece.getColor())) {
               break;
            }
         }
         break;
      default:
         break;
   }
   return false;
}

bool chessBoard::canCastleQueen(int color) {
   chessPiece rook;
   chessPiece king;
   bool check = false;
   if (!color) {
      rook = whiteBoard[9][2];
      king = whiteBoard[9][6];
      if (rook.getPiece() == 1 && king.getPiece() == 5) { //checks if king or rook have moved
         if (rook.getCastle() && king.getCastle() && whiteCheck.empty()) { 
            if (whiteBoard[9][3].getPiece() == -1 && whiteBoard[9][4].getPiece() == -1 && whiteBoard[9][5].getPiece() == -1) {
               movePiece(color, 9, 6, 9, 4, king, true); //temp move king
               check = true;
            }
         }
      }
      for (int i = 0; i < 16; i++) { //checks if move causes check
         if (whitePieces[i].getPiece() != -1) { //checks every single piece on board
            if (isCheck(whitePieces[i])) { //checks if piece causes check
               return false;
            }
         }
      }
      if (check) {
         movePiece(color, 9, 4, 9, 6, king, true);
         return true;
      }
   }
   else {
      rook = blackBoard[9][9];
      king = blackBoard[9][5];
      if (rook.getPiece() == 1 && king.getPiece() == 6) { //checks if king or rook have moved
         if (rook.getCastle() && king.getCastle() && blackCheck.empty()) { 
            if (blackBoard[9][6].getPiece() == -1 && blackBoard[9][7].getPiece() == -1 && blackBoard[9][8].getPiece() == -1) {
               movePiece(color, 9, 5, 9, 7, king, true); //temp move king
               check = true;
            }
         }
      }
      for (int i = 0; i < 16; i++) { //checks if move causes check
         if (blackPieces[i].getPiece() != -1) { //checks every single piece on board
            if (isCheck(blackPieces[i])) { //checks if piece causes check
               return false;
            }
         }
      }
      if (check) {
         movePiece(color, 9, 7, 9, 5, king, true);
         return true;
      }
   }
   return false;
}

bool chessBoard::canCastleKing(int color) {
   chessPiece rook;
   chessPiece king;
   bool check = false;
   if (!color) {
      rook = whiteBoard[9][9];
      king = whiteBoard[9][6];
      if (rook.getPiece() == 1 && king.getPiece() == 5) { //checks if king or rook have moved
         if (rook.getCastle() && king.getCastle() && whiteCheck.empty()) { 
            if (whiteBoard[9][7].getPiece() == -1 && whiteBoard[9][8].getPiece() == -1) {
               movePiece(color, 9, 6, 9, 8, king, true); //temp move king
               check = true;
            }
         }
      }
      for (int i = 0; i < 16; i++) { //checks if move causes check
         if (whitePieces[i].getPiece() != -1) { //checks every single piece on board
            if (isCheck(whitePieces[i])) { //checks if piece causes check
               return false;
            }
         }
      }
      if (check) {
         movePiece(color, 9, 8, 9, 6, king, true);
         return true;
      }
   }
   else {
      rook = blackBoard[9][2];
      king = blackBoard[9][5];
      if (rook.getPiece() == 1 && king.getPiece() == 6) { //checks if king or rook have moved
         if (rook.getCastle() && king.getCastle() && blackCheck.empty()) { 
            if (blackBoard[9][3].getPiece() == -1 && blackBoard[9][4].getPiece() == -1) {
               movePiece(color, 9, 5, 9, 3, king, true); //temp move king
               check = true;
            }
         }
      }
      for (int i = 0; i < 16; i++) { //checks if move causes check
         if (blackPieces[i].getPiece() != -1) { //checks every single piece on board
            if (isCheck(blackPieces[i])) { //checks if piece causes check
               return false;
            }
         }
      }
      if (check) {
         movePiece(color, 9, 3, 9, 5, king, true);
         return true;
      }
   }
   return false;
}

void chessBoard::makeMove(int color) {
   char array1[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
   char array2[8] = {'H', 'G', 'F', 'E', 'D', 'C', 'B', 'A'};
   std::string piece;
   std::pair<int, int> pieceP;
   chessPiece p;
   bool check1 = false;
   bool check2 = false;
   std::string position;
   int x, y;
   std::queue<chessPiece> q1;
   std::queue<chessPiece> q2;
   chessPiece* pieces;
   do {
      std::cout << "Which piece: ";
      std::cin >> piece;
      if (piece == "Castle") {
         if (canCastleQueen(color) || canCastleKing(color)) {
            std::cout << "TEST" << std::endl;
            goto HERE7;
         }
         continue;
      }
      std::stringstream n1;
      int n_1;
      n1 << piece[1];
      n1 >> n_1;
      pieceP.first = !color ? 10 - n_1 : n_1+1;
      for (int i = 0; i < 8; i++) {
         if (array1[i] == piece[0] && !color) {
            pieceP.second = i+2;
         }
         else if (array2[i] == piece[0] && color) {
            pieceP.second = i+2;
         }
      }
      if (pieceP.first < 2 || pieceP.first > 9 || pieceP.second < 2 || pieceP.second > 9) {
         continue;
      }
      p = !color ? whiteBoard[pieceP.first][pieceP.second] : blackBoard[pieceP.first][pieceP.second];
      q1 = !color ? whiteCheck : blackCheck;
      q2 = !color ? whiteCheck : blackCheck;
      pieces = !color ? blackPieces : whitePieces;
      while (!q1.empty()) { //checks if piece can be moved otherwise causing check
         if (isCheck(q1.front())) {
            std::cout << "Check" << std::endl;
            break;
         }
         q1.pop();
      }
      if (!q1.empty()) {
         continue;
      }
      if (!checkSurr(p)) {
         std::cout << "Surr" << std::endl;
         continue;
      }
      if (p.getColor() == color) {
         std::cout << "Color" << std::endl;
         check1 = true;
      }
   } while (!check1);
   do {
      std::cout << "Move to: ";
      std::cin >> position;
      std::stringstream n2;
      int n_2;
      n2 << position[1];
      n2 >> n_2;
      x = !color ? 10 - n_2 : n_2+1;
      for (int i = 0; i < 8; i++) {
         if (array1[i] == position[0] && !color) {
            y = i+2;
         }
         else if (array2[i] == position[0] && color) {
            y = i+2;
         }
      }
      if (x < 2 || x > 9 || y < 2 || y > 9) { //checks if out of bounds
         std::cout << "Not possible move" << std::endl;
         continue;
      }
      if (!checkMove(p, x, y)) { //checks if move is legal
         std::cout << "Not possible move" << std::endl;
         continue;
      }
      movePiece(color, pieceP.first, pieceP.second, x, y, p, true); //here temporarily move piece and take back
      for (int i = 0; i < 16; i++) { //checks if move causes check
         if (pieces[i].getPiece() != -1) { //checks every single piece on board
            if (isCheck(pieces[i])) { //checks if piece causes check
               std::cout << "Check1" << std::endl;
               goto HERE6;
            }
         }
      }
      while (!q2.empty()) { //checks if move prevents check (check all pieces to see if they target enemy king)
         if (isCheck(q2.front())) {
            std::cout << "Check2" << std::endl;
            goto HERE6;
         }
         q2.pop();
      }
      check2 = true;
      HERE6:
      movePiece(color, x, y, pieceP.first, pieceP.second, p, true); //take back
   } while (!check2);
   movePiece(color, pieceP.first, pieceP.second, x, y, p, false);
   if (false) { //castling 
      HERE7:
      std::string side;
      bool check3 = false;
      do {
         std::cout << "Which side: ";
         std::cin >> side;
         if (side != "K" && side != "Q") {
            continue;
         }
         if (canCastleQueen(color)) {
            if (side != "Q") {
               continue;
            }
            castleQueen(color);
         }
         else if (canCastleKing(color)) {
            if (side != "K") {
               continue;
            }
            castleKing(color);
         }
         else if (canCastleQueen(color) && canCastleKing(color)) {
            if (side == "Q") {
               castleQueen(color);
            }
            else if (side == "K") {
               castleKing(color);
            }
         }
         check3 = true;
      } while (!check3);
   }
}

void chessBoard::castleQueen(int color) {
   chessPiece rook;
   chessPiece king;
   if (!color) {
      rook = whiteBoard[9][2];
      king = whiteBoard[9][6];
      movePiece(color, 9, 2, 9, 5, rook, false);
      movePiece(color, 9, 6, 9, 4, king, false);
   }
   else {
      rook = blackBoard[9][9];
      king = blackBoard[9][5];
      movePiece(color, 9, 9, 9, 6, rook, false);
      movePiece(color, 9, 5, 9, 7, king, false);
   }
}

void chessBoard::castleKing(int color) {
   chessPiece rook;
   chessPiece king;
   if (!color) {
      rook = whiteBoard[9][9];
      king = whiteBoard[9][6];
      movePiece(color, 9, 9, 9, 7, rook, false);
      movePiece(color, 9, 6, 9, 8, king, false);
   }
   else {
      rook = blackBoard[9][2];
      king = blackBoard[9][5];
      movePiece(color, 9, 2, 9, 4, rook, false);
      movePiece(color, 9, 5, 9, 3, king, false);
   }
}

void chessBoard::movePiece(int color, int prevX, int prevY, int x, int y, chessPiece &piece, bool temp) {
   chessPiece emptyPiece = chessPiece();
   int prevX1, prevY1;
   int x1, y1;
   if (!color) {
      whiteBoard[prevX][prevY] = emptyPiece; //sets previous spot as empty
      prevX1 = abs(prevX - 11);
      prevY1 = abs(prevY - 11);
      blackBoard[prevX1][prevY1] = emptyPiece;
      for (int i = 0; i < 16; i++) {
         if (piece.getPosition().first == whitePieces[i].getPosition().first && 
         piece.getPosition().second == whitePieces[i].getPosition().second) { 
            piece.setPosition(x, y);
            whitePieces[i] = piece;
            break;
         }
      }
      x1 = abs(x - 11);
      y1 = abs(y - 11);
      if (whiteBoard[x][y].getColor() == 1) {
         for (int i = 0; i < 16; i++) {
            if (x1 == blackPieces[i].getPosition().first && y1 == blackPieces[i].getPosition().second) {
               blackPieces[i] = emptyPiece;
               break;
            }
         }
      }
      whiteBoard[x][y] = piece; //sets new spot as piece
      blackBoard[x1][y1] = piece;
      blackBoard[x1][y1].setPosition(x1, y1);
      if (isCheck(piece) && !temp) {
         blackCheck.push(piece);
      }
   }
   else {
      blackBoard[prevX][prevY] = emptyPiece; //sets previous spot as empty
      prevX1 = abs(prevX - 11);
      prevY1 = abs(prevY - 11);
      whiteBoard[prevX1][prevY1] = emptyPiece;
      for (int i = 0; i < 16; i++) {
         if (piece.getPosition().first == blackPieces[i].getPosition().first &&
         piece.getPosition().second == blackPieces[i].getPosition().second) {
            piece.setPosition(x, y);
            blackPieces[i] = piece;
            break;
         }
      }
      x1 = abs(x - 11);
      y1 = abs(y - 11);
      if (blackBoard[x][y].getColor() == 0) {
         for (int i = 0; i < 16; i++) {
            if (x1 == whitePieces[i].getPosition().first && y1 == whitePieces[i].getPosition().second) {
               whitePieces[i] = emptyPiece;
               break;
            }
         }
      }
      blackBoard[x][y] = piece; //sets new spot as piece
      whiteBoard[x1][y1] = piece;
      whiteBoard[x1][y1].setPosition(x1, y1);
      if (isCheck(piece) && !temp) {
         whiteCheck.push(piece);
      }
   }
}

void chessBoard::printBoard(int color) const{
   //system("clear");
   char array[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
   int counter = !color ? 0 : 7;
   if (!color) {
      std::cout << "Player 1:" << std::endl;
   }
   else {
      std::cout << "Player 2:" << std::endl;
   }
   std::cout << "  ";
   for (int i = 0; i <= 48; i++) {
      if ((i-3) % 6 == 0) {
         std::cout << array[counter];
         if (!color) {
            counter++;
         }
         else {
            counter--;
         }
      }
      else if (i == 48) {
         std::cout << std::endl;
      }
      else {
         std::cout << " ";
      }
   }
   std::cout << "  ";
   for (int i = 0; i < 25; i++) {
      std::cout << "# ";
   }
   std::cout << std::endl;
   for (int i = 8; i > 0; i--) {
      int k = 10 - i;
      if (!color) {
         std::cout << i << " ";
      }
      else {
         std::cout << 9-i << " ";
      }
      for (int j = 0; j <= 48; j++) {
         if (j == 0) {
            std::cout << "#";
         }
         else if (j == 48) {
            std::cout << "#" << std::endl;
         }
         else if (j % 6 == 0) {
            std::cout << "|";
         }
         else if((j-3) % 6 == 0) {
            if (!color) {
               whiteBoard[k][((j-3)/6)+2].printPiece();
            }
            else {
               blackBoard[k][((j-3)/6)+2].printPiece();
            }
         }
         else {
            std::cout << " ";
         }
      }
      if (i != 1) {
         std::cout << "  ";
         for (int j = 0; j <= 48; j++) {
            if (j == 0) {
               std::cout << "#";
            }
            else if (j == 48) {
               std::cout << "#" << std::endl;
            }
            else if (j % 6 != 0) {
               std::cout << "-";
            }
            else {
               std::cout << " ";
            }
         }
      }
   }
   std::cout << "  ";
   for (int i = 0; i < 25; i++) {
      std::cout << "# ";
   }
   std::cout << std::endl;
}