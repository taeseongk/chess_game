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
   int bCounter1 = 0;
   int bCounter2 = 15;
   chessPiece whitePiece[16] = {wPawn, wPawn, wPawn, wPawn, wPawn, wPawn, wPawn, wPawn, 
                                 wRook, wKnight, wBishop, wQueen, wKing, wBishop, wKnight, wRook};
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
               whitePieces.push_back(whitePiece[wCounter1]);
               whitePieces.back().setPosition(i, j);
               whiteBoard[i][j] = whitePieces.back();
               wCounter1++;
               blackPieces.push_back(blackPiece[bCounter2]);
               blackPieces.back().setPosition(i, j);
               blackBoard[i][j] = blackPieces.back();
               bCounter2--;
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

bool chessBoard::checkMove(chessPiece &piece, int x, int y) const {
   int i = piece.getPosition().first;
   int j = piece.getPosition().second;
   int color = piece.getColor();
   chessPiece** board = !color ? whiteBoard : blackBoard;
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
            else if (((i-1 == x && j-1 == y) || (i-1 == x && j+1 == y)) && board[x][y].getColor() == !color) return true;
         }
         else if (piece.getPawn()) {
            if (i-1 == x && j == y && board[x][y].getPiece() == -1) return true; //if move is forward once
            else if (((i-1 == x && j-1 == y) || (i-1 == x && j+1 == y)) && board[x][y].getColor() == !color) return true;
         }
         break;
      case 1:
         if (i-x >= 1 && j == y) { //if move is forward
            for (int k = i-1; k > x; k--) {
               if (board[k][y].getPiece() != -1) return false;
            }
            goto HERE1;
         }
         else if (x-i >= 1 && j == y) { //if move is backward
            for (int k = i+1; k < x; k++) {
               if (board[k][y].getPiece() != -1) return false;
            }
            goto HERE1;
         }
         else if (i == x && j-y >= 1) { //if move is leftward
            for (int k = j-1; k > y; k--) {
               if (board[x][k].getPiece() != -1) return false;
            }
            goto HERE1;
         }
         else if (i == x && y-j >= 1) { //if move is rightward
            for (int k = j+1; k < y; k++) {
               if (board[x][k].getPiece() != -1) return false;
            }
            goto HERE1;
         }
         break;
      case 2:
         if ((i-2 == x && j-1 == y) || (i-2 == x && j+1 == y) || (i-1 == x && j+2 == y) || (i+1 == x && j+2 == y) || 
         (i+2 == x && j+1 == y) || (i+2 == x && j-1 == y) || (i+1 == x && j-2 == y) || (i-1 == x && j-2 == y)) goto HERE2;
         break;
      case 3:
         if (i-x >= 1 && j-y >= 1 && i-x == j-y) { //if move is up-left
            for (int k = 1; k < i-x; k++) {
               if (board[i-k][j-k].getPiece() != -1) return false;
            }
            goto HERE2;
         }
         else if (x-i >= 1 && j-y >= 1 && x-i == j-y) { //if move is down-left
            for (int k = 1; k < x-i; k++) {
               if (board[i+k][j-k].getPiece() != -1) return false;
            }
            goto HERE2;
         }
         else if (i-x >= 1 && y-j >= 1 && i-x == y-j) { //if move is up-right
            for (int k = 1; k < i-x; k++) {
               if (board[i-k][j+k].getPiece() != -1) return false;
            }
            goto HERE2;
         }
         else if (x-i >= 1 && y-j >= 1 && x-i == y-j) { //if move is down-right
            for (int k = 1; k < x-i; k++) {
               if (board[i+k][j+k].getPiece() != -1) return false;
            }
            goto HERE2;
         }
         break;
      case 4:
         if (i-x >= 1 && j == y) { //if move is forward
            for (int k = i-1; k > x; k--) {
               if (board[k][y].getPiece() != -1) return false;
            }
            goto HERE2;
         }
         else if (x-i >= 1 && j == y) { //if move is backward
            for (int k = i+1; k < x; k++) {
               if (board[k][y].getPiece() != -1) return false;
            }
            goto HERE2;
         }
         else if (i == x && j-y >= 1) { //if move is leftward
            for (int k = j-1; k > y; k--) {
               if (board[x][k].getPiece() != -1) return false;
            }
            goto HERE2;
         }
         else if (i == x && y-j >= 1) { //if move is rightward
            for (int k = j+1; k < y; k++) {
               if (board[x][k].getPiece() != -1) return false;
            }
            goto HERE2;
         }
         else if (i-x >= 1 && j-y >= 1 && i-x == j-y) { //if move is up-left
            for (int k = 1; k < i-x; k++) {
               if (board[i-k][j-k].getPiece() != -1) return false;
            }
            goto HERE2;
         }
         else if (x-i >= 1 && j-y >= 1 && x-i == j-y) { //if move is down-left
            for (int k = 1; k < x-i; k++) {
               if (board[i+k][j-k].getPiece() != -1) return false;
            }
            goto HERE2;
         }
         else if (i-x >= 1 && y-j >= 1 && i-x == y-j) { //if move is up-right
            for (int k = 1; k < i-x; k++) {
               if (board[i-k][j+k].getPiece() != -1) return false;
            }
            goto HERE2;
         }
         else if (x-i >= 1 && y-j >= 1 && x-i == y-j) { //if move is down-right
            for (int k = 1; k < x-i; k++) {
               if (board[i+k][j+k].getPiece() != -1) return false;
            }
            goto HERE2;
         }
         break;
      case 5:
         if (i-x == 1 && j == y) { //if move is forward
            if (board[x][y].getPiece() != -1) return false;
            goto HERE1;
         }
         else if (x-i == 1 && j == y) { //if move is backward
            if (board[x][y].getPiece() != -1) return false;
            goto HERE1;
         }
         else if (i == x && j-y == 1) { //if move is leftward
            if (board[x][y].getPiece() != -1) return false; 
            goto HERE1;
         }
         else if (i == x && y-j == 1) { //if move is rightward
            if (board[x][y].getPiece() != -1) return false;
            goto HERE1;
         }
         else if (i-x == 1 && j-y == 1) { //if move is up-left
            if (board[x][y].getPiece() != -1) return false;
            goto HERE1;
         }
         else if (x-i == 1 && j-y == 1) { //if move is down-left
            if (board[x][y].getPiece() != -1) return false;
            goto HERE1;
         }
         else if (i-x == 1 && y-j == 1) { //if move is up-right
            if (board[x][y].getPiece() != -1) return false;
            goto HERE1;
         }
         else if (x-i == 1 && y-j == 1) { //if move is down-right
            if (board[x][y].getPiece() != -1) return false;
            goto HERE1;
         }
         break;
      case 6:
         if (i-x == 1 && j == y) { //if move is forward
            if (board[x][y].getPiece() != -1) return false;
            goto HERE1;
         }
         else if (x-i == 1 && j == y) { //if move is backward
            if (board[x][y].getPiece() != -1) return false;
            goto HERE1;
         }
         else if (i == x && j-y == 1) { //if move is leftward
            if (board[x][y].getPiece() != -1) return false;
            goto HERE1;
         }
         else if (i == x && y-j == 1) { //if move is rightward
            if (board[x][y].getPiece() != -1) return false;
            goto HERE1;
         }
         else if (i-x == 1 && j-y == 1) { //if move is up-left
            if (board[x][y].getPiece() != -1) return false;
            goto HERE1;
         }
         else if (x-i == 1 && j-y == 1) { //if move is down-left
            if (board[x][y].getPiece() != -1) return false;
            goto HERE1;
         }
         else if (i-x == 1 && y-j == 1) { //if move is up-right
            if (board[x][y].getPiece() != -1) return false;
            goto HERE1;
         }
         else if (x-i == 1 && y-j == 1) { //if move is down-right
            if (board[x][y].getPiece() != -1) return false;
            goto HERE1;
         }
         break;
      default:
         if (false) {
            HERE1:
            if (color != board[x][y].getColor()) {
               piece.setCastle(); //after move has been made
               return true;
            }
            HERE2:
            if (color != board[x][y].getColor()) return true;
         }
         break;
   }
   return false;
}

bool chessBoard::checkSurr(chessPiece piece) const {
   int i = piece.getPosition().first;
   int j = piece.getPosition().second;
   int color = piece.getColor();
   chessPiece** board = !color ? whiteBoard : blackBoard;
   switch (piece.getPiece()) {
      case 0:
         if (board[i-1][j].getPiece() == -1 || board[i-1][j-1].getColor() == !color ||
         board[i-1][j+1].getColor() == !color) return true;
         break;
      case 1:
         if (board[i-1][j].getColor() != color || board[i+1][j].getColor() != color || 
         board[i][j-1].getColor() != color || board[i][j+1].getColor() != color) return true;
         break;
      case 2:
         if (board[i-2][j-1].getColor() != color || board[i-2][j+1].getColor() != color || board[i-1][j+2].getColor() != color || 
         board[i+1][j+2].getColor() != color || board[i+2][j+1].getColor() != color || board[i+2][j-1].getColor() != color || 
         board[i+1][j-2].getColor() != color || board[i-1][j-2].getColor() != color) return true;
         break;
      case 3:
         if (board[i-1][j-1].getColor() != color || board[i-1][j+1].getColor() != color ||
         board[i+1][j-1].getColor() != color || board[i+1][j+1].getColor() != color) return true;
         break;
      case 4:
         if (board[i-1][j].getColor() != color || board[i+1][j].getColor() != color || board[i][j-1].getColor() != color || 
         board[i][j+1].getColor() != color || board[i-1][j-1].getColor() != color || board[i-1][j+1].getColor() != color || 
         board[i+1][j-1].getColor() != color || board[i+1][j+1].getColor() != color) return true;
         break;
      case 5:
         if (board[i-1][j].getColor() != color || board[i+1][j].getColor() != color || board[i][j-1].getColor() != color || 
         board[i][j+1].getColor() != color || board[i-1][j-1].getColor() != color || board[i-1][j+1].getColor() != color || 
         board[i+1][j-1].getColor() != color || board[i+1][j+1].getColor() != color) return true;
         break;
      case 6:
         if (board[i-1][j].getColor() != color || board[i+1][j].getColor() != color || board[i][j-1].getColor() != color || 
         board[i][j+1].getColor() != color || board[i-1][j-1].getColor() != color || board[i-1][j+1].getColor() != color || 
         board[i+1][j-1].getColor() != color || board[i+1][j+1].getColor() != color) return true;
         break;
      default:
         break;
   }
   return false;
}

bool chessBoard::isCheck(chessPiece piece) const { //return true if move caused check for opponent
   int i = piece.getPosition().first;
   int j = piece.getPosition().second;
   int color = piece.getColor();
   int king = !color ? 6 : 5;
   chessPiece** board = !color ? whiteBoard : blackBoard;
   switch (piece.getPiece()) {
      case 0:
         if (board[i-1][j-1].getPiece() == king || board[i-1][j+1].getPiece() == king) return true;
         break;
      case 1:
         for (int k = 1; k < 8; k++) { //left
            if (board[i][j-k].getPiece() == king) return true;
            else if (board[i][j-k].getPiece() != -1) break;
         }
         for (int k = 1; k < 8; k++) { //right
            if (board[i][j+k].getPiece() == king) return true;
            else if (board[i][j+k].getPiece() != -1) break;
         }
         for (int k = 1; k < 8; k++) { //up
            if (board[i-k][j].getPiece() == king) return true;
            else if (board[i-k][j].getPiece() != -1) break;
         }
         for (int k = 1; k < 8; k++) { //down
            if (board[i+k][j].getPiece() == king) return true;
            else if (board[i+k][j].getPiece() != -1) break;
         }
         break;
      case 2:
         if (board[i-2][j-1].getPiece() == king || board[i-2][j+1].getPiece() == king || board[i-1][j+2].getPiece() == king || 
         board[i+1][j+2].getPiece() == king || board[i+2][j+1].getPiece() == king || board[i+2][j-1].getPiece() == king || 
         board[i+1][j-2].getPiece() == king || board[i-1][j-2].getPiece() == king) return true;
         break;
      case 3:
         for (int k = 1; k < 8; k++) { //up-left
            if (board[i-k][j-k].getPiece() == king) return true;
            else if (board[i-k][j-k].getPiece() != -1) break;
         }
         for (int k = 1; k < 8; k++) { //up-right
            if (board[i-k][j+k].getPiece() == king) return true;
            else if (board[i-k][j+k].getPiece() != -1) break;
         }
         for (int k = 1; k < 8; k++) { //down-left
            if (board[i+k][j-k].getPiece() == king) return true;
            else if (board[i+k][j-k].getPiece() != -1) break;
         }
         for (int k = 1; k < 8; k++) { //down-right
            if (board[i+k][j+k].getPiece() == king) return true;
            else if (board[i+k][j+k].getPiece() != -1) break;
         }
         break;
      case 4:
         for (int k = 1; k < 8; k++) { //left
            if (board[i][j-k].getPiece() == king) return true;
            else if (board[i][j-k].getPiece() != -1) break;
         }
         for (int k = 1; k < 8; k++) { //right
            if (board[i][j+k].getPiece() == king) return true;
            else if (board[i][j+k].getPiece() != -1) break;
         }
         for (int k = 1; k < 8; k++) { //up
            if (board[i-k][j].getPiece() == king) return true;
            else if (board[i-k][j].getPiece() != -1) break;
         }
         for (int k = 1; k < 8; k++) { //down
            if (board[i+k][j].getPiece() == king) return true;
            else if (board[i+k][j].getPiece() != -1) break;
         }
         for (int k = 1; k < 8; k++) { //up-left
            if (board[i-k][j-k].getPiece() == king) return true;
            else if (board[i-k][j-k].getPiece() != -1) break;
         }
         for (int k = 1; k < 8; k++) { //up-right
            if (board[i-k][j+k].getPiece() == king) return true;
            else if (board[i-k][j+k].getPiece() != -1) break;
         }
         for (int k = 1; k < 8; k++) { //down-left
            if (board[i+k][j-k].getPiece() == king) return true;
            else if (board[i+k][j-k].getPiece() != -1) break;
         }
         for (int k = 1; k < 8; k++) { //down-right
            if (board[i+k][j+k].getPiece() == king) return true;
            else if (board[i+k][j+k].getPiece() != -1) break;
         }
         break;
      case 5:
         if (board[i][j-1].getPiece() == king || board[i][j+1].getPiece() == king || board[i-1][j].getPiece() == king ||
         board[i+1][j].getPiece() == king || board[i-1][j-1].getPiece() == king || board[i-1][j+1].getPiece() == king ||
         board[i+1][j-1].getPiece() == king || board[i+1][j+1].getPiece() == king) return true;
         break;
      case 6:
         if (board[i][j-1].getPiece() == king || board[i][j+1].getPiece() == king || board[i-1][j].getPiece() == king ||
         board[i+1][j].getPiece() == king || board[i-1][j-1].getPiece() == king || board[i-1][j+1].getPiece() == king ||
         board[i+1][j-1].getPiece() == king || board[i+1][j+1].getPiece() == king) return true;
         break;
      default:
         break;
   }
   return false;
}

bool chessBoard::isCheckmate(int color) {
   std::vector<chessPiece> pieces = !color ? whitePieces : blackPieces;
   for (std::vector<chessPiece>::iterator i = pieces.begin(); i != pieces.end(); ++i) {
      if (checkPiece1(*i) && checkPiece2(*i)) {
         return false;
      }
   }
   return true;
}

bool chessBoard::isStalemate(int color) {
   std::vector<chessPiece> pieces = !color ? whitePieces : blackPieces;
   for (std::vector<chessPiece>::iterator i = pieces.begin(); i != pieces.end(); ++i) {
      if (checkPiece2(*i)) {
         return false;
      }
   }
   return true;
}

bool chessBoard::checkQueue(int color, int prevX, int prevY, int x, int y, chessPiece &piece) { //checks move to see if it prevents check
   std::deque<chessPiece>* q1 = !color ? &whiteCheck : &blackCheck;
   std::deque<chessPiece> q2 = !color ? whiteCheck : blackCheck;
   bool check = movePiece(color, prevX, prevY, x, y, piece, true, false, true);
   while (!q1->empty()) { //checks if piece can be moved otherwise causing check
      if (isCheck(q1->front())) {
         if (check) {
            movePiece(color, x, y, prevX, prevY, piece, false, true, true);
            q1 = &q2;
         }
         else {
            movePiece(color, x, y, prevX, prevY, piece, false, false, true);
         }
         return false;
      }
      q1->pop_front();
   }
   if (check) {
      movePiece(color, x, y, prevX, prevY, piece, false, true, true);
      q1 = &q2;
   } 
   else {
      movePiece(color, x, y, prevX, prevY, piece, false, false, true);
   }
   return true;
}

bool chessBoard::checkArray(int color, int prevX, int prevY, int x, int y, chessPiece &piece) { //checks every possible move
   std::vector<chessPiece>* pieces = !color ? &blackPieces : &whitePieces;
   std::deque<chessPiece>* q1 = !color ? &whiteCheck : &blackCheck;
   std::deque<chessPiece> q2 = !color ? whiteCheck : blackCheck;
   bool check = movePiece(color, prevX, prevY, x, y, piece, true, false, true);
   for (std::vector<chessPiece>::iterator i = pieces->begin(); i != pieces->end(); ++i) { //checks if move causes check
      if (isCheck(*i)) { //checks if piece causes check
         if (check) {
            movePiece(color, x, y, prevX, prevY, piece, false, true, true);
            q1 = &q2;
         }
         else {
            movePiece(color, x, y, prevX, prevY, piece, false, false, true);
         }
         return false;
      }
   }
   if (check) {
      movePiece(color, x, y, prevX, prevY, piece, false, true, true);
      q1 = &q2;
   }
   else {
      movePiece(color, x, y, prevX, prevY, piece, false, false, true);
   }
   return true;
}

bool chessBoard::checkPiece1(chessPiece piece) { //check every possible move and see if it prevents check -> if none do then return false
   int i = piece.getPosition().first;
   int j = piece.getPosition().second;
   int color = piece.getColor();
   int k;
   chessPiece** board = !color ? whiteBoard : blackBoard;
   switch (piece.getPiece()) {
      case 0: 
         if (!piece.getPawn()) {
            if (board[i-1][j].getPiece() == -1 && checkQueue(color, i, j, i-1, j, piece)) return true; //if move is forward once and no piece in front
            else if(board[i-1][j].getPiece() == -1 && board[i-2][j].getPiece() == -1 && 
            checkQueue(color, i, j, i-2, j, piece)) return true; //if move is forward twice
            else if (board[i-1][j-1].getColor() == !color && checkQueue(color, i, j, i-1, j-1, piece)) return true;
            else if (board[i-1][j+1].getColor() == !color && checkQueue(color, i, j, i-1, j+1, piece)) return true;
         }
         else if (piece.getPawn()) {
            if (board[i-1][j].getPiece() == -1 && checkQueue(color, i, j, i-1, j, piece)) return true; //if move is forward once
            else if (board[i-1][j-1].getColor() == !color && checkQueue(color, i, j, i-1, j-1, piece)) return true;
            else if (board[i-1][j+1].getColor() == !color && checkQueue(color, i, j, i-1, j+1, piece)) return true;
         }
         break;
      case 1:
         k = i - 1;
         while (board[k][j].getPiece() == -1 || board[k][j].getColor() == !color) { //upward
            if (checkQueue(color, i, j, k, j, piece)) return true;
            if (board[k][j].getColor() == !color) break;
            k--;
         }
         k = i + 1;
         while (board[k][j].getPiece() == -1 || board[k][j].getColor() == !color) { //downward
            if (checkQueue(color, i, j, k, j, piece)) return true;
            if (board[k][j].getColor() == !color) break;
            k++;
         }
         k = j - 1;
         while (board[i][k].getPiece() == -1 || board[i][k].getColor() == !color) { //leftward
            if (checkQueue(color, i, j, i, k, piece)) return true;
            if (board[i][k].getColor() == !color) break;
            k--;
         }
         k = j + 1;
         while (board[i][k].getPiece() == -1 || board[i][k].getColor() == !color) { //rightward
            if (checkQueue(color, i, j, i, k, piece)) return true;
            if (board[i][k].getColor() == !color) break;
            k++;
         }        
         break;
      case 2:
         if ((board[i-2][j-1].getPiece() == -1 || board[i-2][j-1].getColor() == !color) && checkQueue(color, i, j, i-2, j-1, piece)) return true;
         else if ((board[i-2][j+1].getPiece() == -1 || board[i-2][j+1].getColor() == !color) && checkQueue(color, i, j, i-2, j+1, piece)) return true;
         else if ((board[i-1][j+2].getPiece() == -1 || board[i-1][j+2].getColor() == !color) && checkQueue(color, i, j, i-1, j+2, piece)) return true;
         else if ((board[i+1][j+2].getPiece() == -1 || board[i+1][j+2].getColor() == !color) && checkQueue(color, i, j, i+1, j+2, piece)) return true;
         else if ((board[i+2][j+1].getPiece() == -1 || board[i+2][j+1].getColor() == !color) && checkQueue(color, i, j, i+2, j+1, piece)) return true;
         else if ((board[i+2][j-1].getPiece() == -1 || board[i+2][j-1].getColor() == !color) && checkQueue(color, i, j, i+2, j-1, piece)) return true;
         else if ((board[i+1][j-2].getPiece() == -1 || board[i+1][j-2].getColor() == !color) && checkQueue(color, i, j, i+1, j-2, piece)) return true;
         else if ((board[i-1][j-2].getPiece() == -1 || board[i-1][j-2].getColor() == !color) && checkQueue(color, i, j, i-1, j-2, piece)) return true;
         break;
      case 3:
         k = 1;
         while (board[i-k][j-k].getPiece() == -1 || board[i-k][j-k].getColor() == !color) { //up-left
            if (checkQueue(color, i, j, i-k, j-k, piece)) return true;
            if (board[i-k][j-k].getColor() == !color) break;
            k++;
         }
         k = 1;
         while (board[i+k][j-k].getPiece() == -1 || board[i+k][j-k].getColor() == !color) { //down-left
            if (checkQueue(color, i, j, i+k, j-k, piece)) return true;
            if (board[i+k][j-k].getColor() == !color) break;
            k++;
         }
         k = 1;
         while (board[i-k][j+k].getPiece() == -1 || board[i-k][j+k].getColor() == !color) {
            if (checkQueue(color, i, j, i-k, j+k, piece)) return true;
            if (board[i-k][j+k].getColor() == !color) break;
            k++;
         }
         k = 1;
         while (board[i+k][j+k].getPiece() == -1 || board[i+k][j+k].getColor() == !color) {
            if (checkQueue(color, i, j, i+k, j+k, piece)) return true;
            if (board[i+k][j+k].getColor() == !color) break;
            k++;
         }
         break;
      case 4:
         k = i - 1;
         while (board[k][j].getPiece() == -1 || board[k][j].getColor() == !color) { //upward
            if (checkQueue(color, i, j, k, j, piece)) return true;
            if (board[k][j].getColor() == !color) break;
            k--;
         }
         k = i + 1;
         while (board[k][j].getPiece() == -1 || board[k][j].getColor() == !color) { //downward
            if (checkQueue(color, i, j, k, j, piece)) return true;
            if (board[k][j].getColor() == !color) break;
            k++;
         }
         k = j - 1;
         while (board[i][k].getPiece() == -1 || board[i][k].getColor() == !color) { //leftward
            if (checkQueue(color, i, j, i, k, piece)) return true;
            if (board[i][k].getColor() == !color) break;
            k--;
         }
         k = j + 1;
         while (board[i][k].getPiece() == -1 || board[i][k].getColor() == !color) { //rightward
            if (checkQueue(color, i, j, i, k, piece)) return true;
            if (board[i][k].getColor() == !color) break;
            k++;
         }        
         k = 1;
         while (board[i-k][j-k].getPiece() == -1 || board[i-k][j-k].getColor() == !color) { //up-left
            if (checkQueue(color, i, j, i-k, j-k, piece)) return true;
            if (board[i-k][j-k].getColor() == !color) break;
            k++;
         }
         k = 1;
         while (board[i+k][j-k].getPiece() == -1 || board[i+k][j-k].getColor() == !color) { //down-left
            if (checkQueue(color, i, j, i+k, j-k, piece)) return true;
            if (board[i+k][j-k].getColor() == !color) break;
            k++;
         }
         k = 1;
         while (board[i-k][j+k].getPiece() == -1 || board[i-k][j+k].getColor() == !color) {
            if (checkQueue(color, i, j, i-k, j+k, piece)) return true;
            if (board[i-k][j+k].getColor() == !color) break;
            k++;
         }
         k = 1;
         while (board[i+k][j+k].getPiece() == -1 || board[i+k][j+k].getColor() == !color) {
            if (checkQueue(color, i, j, i+k, j+k, piece)) return true;
            if (board[i+k][j+k].getColor() == !color) break;
            k++;
         }
         break;
      case 5:
         if ((board[i-1][j].getPiece() == -1 || board[i-1][j].getColor() == !color) && checkQueue(color, i, j, i-1, j, piece)) return true;
         else if ((board[i+1][j].getPiece() == -1 || board[i+1][j].getColor() == !color) && checkQueue(color, i, j, i+1, j, piece)) return true;
         else if ((board[i][j-1].getPiece() == -1 || board[i][j-1].getColor() == !color) && checkQueue(color, i, j, i, j-1, piece)) return true;
         else if ((board[i][j+1].getPiece() == -1 || board[i][j+1].getColor() == !color) && checkQueue(color, i, j, i, j+1, piece)) return true;
         else if ((board[i-1][j-1].getPiece() == -1 || board[i-1][j-1].getColor() == !color) && checkQueue(color, i, j, i-1, j-1, piece)) return true;
         else if ((board[i+1][j-1].getPiece() == -1 || board[i+1][j-1].getColor() == !color) && checkQueue(color, i, j, i+1, j-1, piece)) return true;
         else if ((board[i-1][j+1].getPiece() == -1 || board[i-1][j+1].getColor() == !color) && checkQueue(color, i, j, i-1, j+1, piece)) return true;
         else if ((board[i+1][j+1].getPiece() == -1 || board[i+1][j+1].getColor() == !color) && checkQueue(color, i, j, i+1, j+1, piece)) return true;
         break;
      case 6:
         if ((board[i-1][j].getPiece() == -1 || board[i-1][j].getColor() == !color) && checkQueue(color, i, j, i-1, j, piece)) return true;
         else if ((board[i+1][j].getPiece() == -1 || board[i+1][j].getColor() == !color) && checkQueue(color, i, j, i+1, j, piece)) return true;
         else if ((board[i][j-1].getPiece() == -1 || board[i][j-1].getColor() == !color) && checkQueue(color, i, j, i, j-1, piece)) return true;
         else if ((board[i][j+1].getPiece() == -1 || board[i][j+1].getColor() == !color) && checkQueue(color, i, j, i, j+1, piece)) return true;
         else if ((board[i-1][j-1].getPiece() == -1 || board[i-1][j-1].getColor() == !color) && checkQueue(color, i, j, i-1, j-1, piece)) return true;
         else if ((board[i+1][j-1].getPiece() == -1 || board[i+1][j-1].getColor() == !color) && checkQueue(color, i, j, i+1, j-1, piece)) return true;
         else if ((board[i-1][j+1].getPiece() == -1 || board[i-1][j+1].getColor() == !color) && checkQueue(color, i, j, i-1, j+1, piece)) return true;
         else if ((board[i+1][j+1].getPiece() == -1 || board[i+1][j+1].getColor() == !color) && checkQueue(color, i, j, i+1, j+1, piece)) return true;
         break;
      default:
         break;
   }
   return false;
}

bool chessBoard::checkPiece2(chessPiece piece) { //check every possible move and see if it creates check -> if check return false
   int i = piece.getPosition().first;
   int j = piece.getPosition().second;
   int color = piece.getColor();
   int k;
   chessPiece** board = !color ? whiteBoard : blackBoard;
   switch (piece.getPiece()) {
      case 0: 
         if (!piece.getPawn()) {
            if (board[i-1][j].getPiece() == -1 && checkArray(color, i, j, i-1, j, piece)) return true; //if move is forward once and no piece in front
            else if(board[i-1][j].getPiece() == -1 && board[i-2][j].getPiece() == -1 && 
            checkArray(color, i, j, i-2, j, piece)) return true; //if move is forward twice
            else if (board[i-1][j-1].getColor() == !color && checkArray(color, i, j, i-1, j-1, piece)) return true;
            else if (board[i-1][j+1].getColor() == !color && checkArray(color, i, j, i-1, j+1, piece)) return true;
         }
         else if (piece.getPawn()) {
            if (board[i-1][j].getPiece() == -1 && checkArray(color, i, j, i-1, j, piece)) return true; //if move is forward once
            else if (board[i-1][j-1].getColor() == !color && checkArray(color, i, j, i-1, j-1, piece)) return true;
            else if (board[i-1][j+1].getColor() == !color && checkArray(color, i, j, i-1, j+1, piece)) return true;
         }
         break;
      case 1:
         k = i - 1;
         while (board[k][j].getPiece() == -1 || board[k][j].getColor() == !color) { //upward
            if (checkArray(color, i, j, k, j, piece)) return true;
            if (board[k][j].getColor() == !color) break;
            k--;
         }
         k = i + 1;
         while (board[k][j].getPiece() == -1 || board[k][j].getColor() == !color) { //downward
            if (checkArray(color, i, j, k, j, piece)) return true;
            if (board[k][j].getColor() == !color) break;
            k++;
         }
         k = j - 1;
         while (board[i][k].getPiece() == -1 || board[i][k].getColor() == !color) { //leftward
            if (checkArray(color, i, j, i, k, piece)) return true;
            if (board[i][k].getColor() == !color) break;
            k--;
         }
         k = j + 1;
         while (board[i][k].getPiece() == -1 || board[i][k].getColor() == !color) { //rightward
            if (checkArray(color, i, j, i, k, piece)) return true;
            if (board[i][k].getColor() == !color) break;
            k++;
         }        
         break;
      case 2:
         if ((board[i-2][j-1].getPiece() == -1 || board[i-2][j-1].getColor() == !color) && checkArray(color, i, j, i-2, j-1, piece)) return true;
         else if ((board[i-2][j+1].getPiece() == -1 || board[i-2][j+1].getColor() == !color) && checkArray(color, i, j, i-2, j+1, piece)) return true;
         else if ((board[i-1][j+2].getPiece() == -1 || board[i-1][j+2].getColor() == !color) && checkArray(color, i, j, i-1, j+2, piece)) return true;
         else if ((board[i+1][j+2].getPiece() == -1 || board[i+1][j+2].getColor() == !color) && checkArray(color, i, j, i+1, j+2, piece)) return true;
         else if ((board[i+2][j+1].getPiece() == -1 || board[i+2][j+1].getColor() == !color) && checkArray(color, i, j, i+2, j+1, piece)) return true;
         else if ((board[i+2][j-1].getPiece() == -1 || board[i+2][j-1].getColor() == !color) && checkArray(color, i, j, i+2, j-1, piece)) return true;
         else if ((board[i+1][j-2].getPiece() == -1 || board[i+1][j-2].getColor() == !color) && checkArray(color, i, j, i+1, j-2, piece)) return true;
         else if ((board[i-1][j-2].getPiece() == -1 || board[i-1][j-2].getColor() == !color) && checkArray(color, i, j, i-1, j-2, piece)) return true;
         break;
      case 3:
         k = 1;
         while (board[i-k][j-k].getPiece() == -1 || board[i-k][j-k].getColor() == !color) { //up-left
            if (checkArray(color, i, j, i-k, j-k, piece)) return true;
            if (board[i-k][j-k].getColor() == !color) break;
            k++;
         }
         k = 1;
         while (board[i+k][j-k].getPiece() == -1 || board[i+k][j-k].getColor() == !color) { //down-left
            if (checkArray(color, i, j, i+k, j-k, piece)) return true;
            if (board[i+k][j-k].getColor() == !color) break;
            k++;
         }
         k = 1;
         while (board[i-k][j+k].getPiece() == -1 || board[i-k][j+k].getColor() == !color) {
            if (checkArray(color, i, j, i-k, j+k, piece)) return true;
            if (board[i-k][j+k].getColor() == !color) break;
            k++;
         }
         k = 1;
         while (board[i+k][j+k].getPiece() == -1 || board[i+k][j+k].getColor() == !color) {
            if (checkArray(color, i, j, i+k, j+k, piece)) return true;
            if (board[i+k][j+k].getColor() == !color) break;
            k++;
         }
         break;
      case 4:
         k = i - 1;
         while (board[k][j].getPiece() == -1 || board[k][j].getColor() == !color) { //upward
            if (checkArray(color, i, j, k, j, piece)) return true;
            if (board[k][j].getColor() == !color) break;
            k--;
         }
         k = i + 1;
         while (board[k][j].getPiece() == -1 || board[k][j].getColor() == !color) { //downward
            if (checkArray(color, i, j, k, j, piece)) return true;
            if (board[k][j].getColor() == !color) break;
            k++;
         }
         k = j - 1;
         while (board[i][k].getPiece() == -1 || board[i][k].getColor() == !color) { //leftward
            if (checkArray(color, i, j, i, k, piece)) return true;
            if (board[i][k].getColor() == !color) break;
            k--;
         }
         k = j + 1;
         while (board[i][k].getPiece() == -1 || board[i][k].getColor() == !color) { //rightward
            if (checkArray(color, i, j, i, k, piece)) return true;
            if (board[i][k].getColor() == !color) break;
            k++;
         }        
         k = 1;
         while (board[i-k][j-k].getPiece() == -1 || board[i-k][j-k].getColor() == !color) { //up-left
            if (checkArray(color, i, j, i-k, j-k, piece)) return true;
            if (board[i-k][j-k].getColor() == !color) break;
            k++;
         }
         k = 1;
         while (board[i+k][j-k].getPiece() == -1 || board[i+k][j-k].getColor() == !color) { //down-left
            if (checkArray(color, i, j, i+k, j-k, piece)) return true;
            if (board[i+k][j-k].getColor() == !color) break;
            k++;
         }
         k = 1;
         while (board[i-k][j+k].getPiece() == -1 || board[i-k][j+k].getColor() == !color) {
            if (checkArray(color, i, j, i-k, j+k, piece)) return true;
            if (board[i-k][j+k].getColor() == !color) break;
            k++;
         }
         k = 1;
         while (board[i+k][j+k].getPiece() == -1 || board[i+k][j+k].getColor() == !color) {
            if (checkArray(color, i, j, i+k, j+k, piece)) return true;
            if (board[i+k][j+k].getColor() == !color) break;
            k++;
         }
         break;
      case 5:
         if ((board[i-1][j].getPiece() == -1 || board[i-1][j].getColor() == !color) && checkArray(color, i, j, i-1, j, piece)) return true;
         else if ((board[i+1][j].getPiece() == -1 || board[i+1][j].getColor() == !color) && checkArray(color, i, j, i+1, j, piece)) return true;
         else if ((board[i][j-1].getPiece() == -1 || board[i][j-1].getColor() == !color) && checkArray(color, i, j, i, j-1, piece)) return true;
         else if ((board[i][j+1].getPiece() == -1 || board[i][j+1].getColor() == !color) && checkArray(color, i, j, i, j+1, piece)) return true;
         else if ((board[i-1][j-1].getPiece() == -1 || board[i-1][j-1].getColor() == !color) && checkArray(color, i, j, i-1, j-1, piece)) return true;
         else if ((board[i+1][j-1].getPiece() == -1 || board[i+1][j-1].getColor() == !color) && checkArray(color, i, j, i+1, j-1, piece)) return true;
         else if ((board[i-1][j+1].getPiece() == -1 || board[i-1][j+1].getColor() == !color) && checkArray(color, i, j, i-1, j+1, piece)) return true;
         else if ((board[i+1][j+1].getPiece() == -1 || board[i+1][j+1].getColor() == !color) && checkArray(color, i, j, i+1, j+1, piece)) return true;
         break;
      case 6:
         if ((board[i-1][j].getPiece() == -1 || board[i-1][j].getColor() == !color) && checkArray(color, i, j, i-1, j, piece)) return true;
         else if ((board[i+1][j].getPiece() == -1 || board[i+1][j].getColor() == !color) && checkArray(color, i, j, i+1, j, piece)) return true;
         else if ((board[i][j-1].getPiece() == -1 || board[i][j-1].getColor() == !color) && checkArray(color, i, j, i, j-1, piece)) return true;
         else if ((board[i][j+1].getPiece() == -1 || board[i][j+1].getColor() == !color) && checkArray(color, i, j, i, j+1, piece)) return true;
         else if ((board[i-1][j-1].getPiece() == -1 || board[i-1][j-1].getColor() == !color) && checkArray(color, i, j, i-1, j-1, piece)) return true;
         else if ((board[i+1][j-1].getPiece() == -1 || board[i+1][j-1].getColor() == !color) && checkArray(color, i, j, i+1, j-1, piece)) return true;
         else if ((board[i-1][j+1].getPiece() == -1 || board[i-1][j+1].getColor() == !color) && checkArray(color, i, j, i-1, j+1, piece)) return true;
         else if ((board[i+1][j+1].getPiece() == -1 || board[i+1][j+1].getColor() == !color) && checkArray(color, i, j, i+1, j+1, piece)) return true;
         break;
      default:
         break;
   }
   return false;
}

bool chessBoard::canCastleQueen(int color) {
   chessPiece rook = !color ? whiteBoard[9][2] : blackBoard[9][9];
   chessPiece king = !color ? whiteBoard[9][6] : blackBoard[9][5];
   bool check = false;
   if (!color) {
      if (rook.getPiece() == 1 && king.getPiece() == 5) { //checks if king or rook have moved
         if (!rook.getCastle() && !king.getCastle() && whiteCheck.empty()) { 
            if (whiteBoard[9][3].getPiece() == -1 && whiteBoard[9][4].getPiece() == -1 && whiteBoard[9][5].getPiece() == -1) {
               movePiece(color, 9, 6, 9, 4, king, true, false, true); //temp move king
               check = true;
            }
         }
      }
      for (std::vector<chessPiece>::iterator i = whitePieces.begin(); i != whitePieces.end(); ++i) { //checks if move causes check
         if (i->getPiece() != -1) { //checks every single piece on board
            if (isCheck(*i)) return false; //checks if piece causes check
         }
      }
      if (check) {
         movePiece(color, 9, 4, 9, 6, king, false, false, true);
         return true;
      }
   }
   else {
      if (rook.getPiece() == 1 && king.getPiece() == 6) { //checks if king or rook have moved
         if (!rook.getCastle() && !king.getCastle() && blackCheck.empty()) { 
            if (blackBoard[9][6].getPiece() == -1 && blackBoard[9][7].getPiece() == -1 && blackBoard[9][8].getPiece() == -1) {
               movePiece(color, 9, 5, 9, 7, king, true, false, true); //temp move king
               check = true;
            }
         }
      }
      for (std::vector<chessPiece>::iterator i = blackPieces.begin(); i != blackPieces.end(); ++i) { //checks if move causes check
         if (i->getPiece() != -1) { //checks every single piece on board
            if (isCheck(*i)) return false; //checks if piece causes check
         }
      }
      if (check) {
         movePiece(color, 9, 7, 9, 5, king, false, false, true);
         return true;
      }
   }
   return false;
}

bool chessBoard::canCastleKing(int color) {
   chessPiece rook = !color ? whiteBoard[9][9] : blackBoard[9][2];
   chessPiece king = !color ? whiteBoard[9][6] : blackBoard[9][5];
   bool check = false;
   if (!color) {
      if (rook.getPiece() == 1 && king.getPiece() == 5) { //checks if king or rook have moved
         if (!rook.getCastle() && !king.getCastle() && whiteCheck.empty()) { 
            if (whiteBoard[9][7].getPiece() == -1 && whiteBoard[9][8].getPiece() == -1) {
               movePiece(color, 9, 6, 9, 8, king, true, false, true); //temp move king
               check = true;
            }
         }
      }
      for (std::vector<chessPiece>::iterator i = whitePieces.begin(); i != whitePieces.end(); ++i) { //checks if move causes check
         if (i->getPiece() != -1) { //checks every single piece on board
            if (isCheck(*i)) return false; //checks if piece causes check
         }
      }
      if (check) {
         movePiece(color, 9, 8, 9, 6, king, false, false, true);
         return true;
      }
   }
   else {
      if (rook.getPiece() == 1 && king.getPiece() == 6) { //checks if king or rook have moved
         if (!rook.getCastle() && !king.getCastle() && blackCheck.empty()) { 
            if (blackBoard[9][3].getPiece() == -1 && blackBoard[9][4].getPiece() == -1) {
               movePiece(color, 9, 5, 9, 3, king, true, false, true); //temp move king
               check = true;
            }
         }
      }
      for (std::vector<chessPiece>::iterator i = blackPieces.begin(); i != blackPieces.end(); ++i) { //checks if move causes check
         if (i->getPiece() != -1) { //checks every single piece on board
            if (isCheck(*i)) return false; //checks if piece causes check
         }
      }
      if (check) {
         movePiece(color, 9, 3, 9, 5, king, false, false, true);
         return true;
      }
   }
   return false;
}

void chessBoard::castleQueen(int color) {
   chessPiece rook = !color ? whiteBoard[9][2] : blackBoard[9][9];
   chessPiece king = !color ? whiteBoard[9][6] : blackBoard[9][5];
   if (!color) {
      movePiece(color, 9, 2, 9, 5, rook, true, false, false);
      movePiece(color, 9, 6, 9, 4, king, true, false, false);
   }
   else {
      movePiece(color, 9, 9, 9, 6, rook, true, false, false);
      movePiece(color, 9, 5, 9, 7, king, true, false, false);
   }
}

void chessBoard::castleKing(int color) {
   chessPiece rook = !color ? whiteBoard[9][9] : blackBoard[9][2];
   chessPiece king = !color ? whiteBoard[9][6] : blackBoard[9][5];
   if (!color) {
      movePiece(color, 9, 9, 9, 7, rook, true, false, false);
      movePiece(color, 9, 6, 9, 8, king, true, false, false);
   }
   else {
      movePiece(color, 9, 2, 9, 4, rook, true, false, false);
      movePiece(color, 9, 5, 9, 3, king, true, false, false);
   }
}

void chessBoard::promotion(int color, char p, int x, int y) {
   chessPiece** board1 = !color ? whiteBoard : blackBoard;
   chessPiece piece;
   switch (p) {
      case 'R':
         piece = chessPiece(color, 1);
         break;
      case 'N':
         piece = chessPiece(color, 2);
         break;  
      case 'B':
         piece = chessPiece(color, 3);
         break;
      case 'Q':
         piece = chessPiece(color, 4);
         break;
      default:
         break;
   }
   piece.setPosition(x, y);
   if (!color) {
      whiteBoard[x][y] = piece;
      whitePieces.push_back(piece);
      piece.setPosition(abs(x-11), abs(y-11));
      blackBoard[abs(x-11)][abs(y-11)] = piece;
      blackPieces.push_back(piece);
   }
   else {
      blackBoard[x][y] = piece;
      blackPieces.push_back(piece);
      piece.setPosition(abs(x-11), abs(y-11));
      whiteBoard[abs(x-11)][abs(y-11)] = piece;
      whitePieces.push_back(piece);
   }
}

bool chessBoard::makeMove(int color) {
   std::string array = !color ? "ABCDEFGH" : "HGFEDCBA";
   std::string piece;
   std::pair<int, int> pieceP;
   chessPiece p;
   bool check1 = false;
   bool check2 = false;
   std::string position;
   int x, y;
   std::string prom;
   std::string answer;
   bool check3 = false;
   bool check5 = false;
   std::deque<chessPiece> q = !color ? whiteCheck : blackCheck;
   if (!q.empty()) {
      if (isCheckmate(color)) {
         if (!color) {
            std::cout << "Checkmate: Player 2 wins!" << std::endl;
            return true;
         }
         else {
            std::cout << "Checkmate: Player 1 wins!" << std::endl;
            return true;
         }
      }
   }
   else {
      if (isStalemate(color)) {
         std::cout << "Game Over: Tie!" << std::endl;
         return true;
      }
   }
   do {
      std::cout << "Which piece: ";
      std::cin >> piece;
      if (piece == "Castle") {
         if (canCastleQueen(color) || canCastleKing(color)) goto HERE4;
         continue;
      }
      if (piece == "Draw") {
         do {
            std::cout << "Does other player agree: ";
            std::cin >> answer;
            if (answer != "Y" && answer != "N") {
               continue;
            }
            if (answer == "Y") {
               std::cout << "Game Over: Tie!" << std::endl;
               return true;
            }
            check5 = true;
         } while (!check5);
      }
      if (piece == "Resign") {
         if (!color) {
            std::cout << "Game Over: Player 2 Wins!" << std::endl;
            return true;
         }
         else {
            std::cout << "Game Over: Player 1 Wins!" << std::endl;
            return true;
         }
      }
      std::stringstream n1;
      int n_1;
      n1 << piece[1];
      n1 >> n_1;
      pieceP.first = !color ? 10 - n_1 : n_1+1;
      for (int i = 0; i < 8; i++) {
         if (array[i] == piece[0]) {
            pieceP.second = i+2;
         }
      }
      if (pieceP.first < 2 || pieceP.first > 9 || pieceP.second < 2 || pieceP.second > 9) continue;
      p = !color ? whiteBoard[pieceP.first][pieceP.second] : blackBoard[pieceP.first][pieceP.second];
      if (!checkSurr(p)) continue;
      if (p.getColor() != color) continue;
      if (!checkPiece1(p)) continue;
      if (!checkPiece2(p)) continue;
      check1 = true;
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
         if (array[i] == position[0]) {
            y = i+2;
         }
      }
      if (x < 2 || x > 9 || y < 2 || y > 9) continue; //checks if out of bounds
      if (!checkMove(p, x, y)) continue; //checks if move is legal
      if (!checkQueue(color, pieceP.first, pieceP.second, x, y, p)) continue;
      if (!checkArray(color, pieceP.first, pieceP.second, x, y, p)) continue;
      if (p.getPiece() == 0 && x == 2) {
         do {
            std::cout << "Which piece: ";
            std::cin >> prom;
            if (prom != "Q" && prom != "R" && prom != "N" && prom != "B") continue;
            check3 = true;
         } while (!check3);
      }
      check2 = true;
   } while (!check2);
   movePiece(color, pieceP.first, pieceP.second, x, y, p, true, false, false);
   if (check3) {
      promotion(color, prom[0], x, y);
   }
   if (false) { //castling 
      HERE4:
      std::string side;
      bool check4 = false;
      do {
         std::cout << "Which side: ";
         std::cin >> side;
         if (side != "K" && side != "Q") continue;
         if (canCastleQueen(color)) {
            if (side != "Q") continue;
            castleQueen(color);
         }
         else if (canCastleKing(color)) {
            if (side != "K") continue;
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
         check4 = true;
      } while (!check4);
   }
   return false;
}

bool chessBoard::movePiece(int color, int prevX, int prevY, int x, int y, chessPiece &piece, bool temp1, bool temp2, bool temp3) {
   chessPiece emptyPiece = chessPiece();
   int prevX1 = abs(prevX - 11);
   int prevY1 = abs(prevY - 11);
   int x1 = abs(x - 11);
   int y1 = abs(y - 11);
   bool check = false;
   if (!color) {
      whiteBoard[prevX][prevY] = emptyPiece; //sets previous spot as empty
      blackBoard[prevX1][prevY1] = emptyPiece;
      for (std::vector<chessPiece>::iterator i = whitePieces.begin(); i != whitePieces.end(); ++i) {
         if (piece.getPosition().first == i->getPosition().first && 
         piece.getPosition().second == i->getPosition().second) { 
            piece.setPosition(x, y);
            *i = piece;
            break;
         }
      }
      if (whiteBoard[x][y].getColor() == 1) {
         for (std::vector<chessPiece>::iterator i = blackPieces.begin(); i != blackPieces.end(); ++i) {
            if (x1 == i->getPosition().first && y1 == i->getPosition().second) {
               if (temp1) {
                  reservePiece = *i;
                  reservePos.first = x1;
                  reservePos.second = y1;
                  check = true;
               }
               blackPieces.erase(i);
               break;
            }
         }
         for (std::deque<chessPiece>::iterator j = whiteCheck.begin(); j != whiteCheck.end(); ++j) {
            if (x1 == j->getPosition().first && y1 == j->getPosition().second) {
               whiteCheck.erase(j);
               break;
            }
         }
      }
      whiteBoard[x][y] = piece; //sets new spot as piece
      blackBoard[x1][y1] = piece;
      blackBoard[x1][y1].setPosition(x1, y1);
      if (isCheck(piece) && !temp3) {
         blackCheck.push_back(piece);
      }
      if (temp2) {
         blackBoard[reservePos.first][reservePos.second] = reservePiece;
         whiteBoard[abs(reservePos.first-11)][abs(reservePos.second-11)] = reservePiece;
         blackPieces.push_back(reservePiece);
      }
   }
   else {
      blackBoard[prevX][prevY] = emptyPiece; //sets previous spot as empty
      whiteBoard[prevX1][prevY1] = emptyPiece;
      for (std::vector<chessPiece>::iterator i = blackPieces.begin(); i != blackPieces.end(); ++i) {
         if (piece.getPosition().first == i->getPosition().first &&
         piece.getPosition().second == i->getPosition().second) {
            piece.setPosition(x, y);
            *i = piece;
            break;
         }
      }
      if (blackBoard[x][y].getColor() == 0) {
         for (std::vector<chessPiece>::iterator i = whitePieces.begin(); i != whitePieces.end(); ++i) {
            if (x1 == i->getPosition().first && y1 == i->getPosition().second) {
               if (temp1) {
                  reservePiece = *i;
                  reservePos.first = x1;
                  reservePos.second = y1;
                  check = true;
               }
               whitePieces.erase(i);
               break;
            }
         }
         for (std::deque<chessPiece>::iterator j = blackCheck.begin(); j != blackCheck.end(); ++j) {
            if (x1 == j->getPosition().first && y1 == j->getPosition().second) {
               blackCheck.erase(j);
               break;
            }
         }
      }
      blackBoard[x][y] = piece; //sets new spot as piece
      whiteBoard[x1][y1] = piece;
      whiteBoard[x1][y1].setPosition(x1, y1);
      if (isCheck(piece) && !temp3) {
         whiteCheck.push_back(piece);
      }
      if (temp2) {
         whiteBoard[reservePos.first][reservePos.second] = reservePiece;
         blackBoard[abs(reservePos.first-11)][abs(reservePos.second-11)] = reservePiece;
         whitePieces.push_back(reservePiece);
      }
   }
   return check;
}

void chessBoard::printBoard(int color) const{
   system("clear");
   std::string array = !color ? "ABCDEFGH" : "HGFEDCBA";
   int counter = 0;
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
         counter++;
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