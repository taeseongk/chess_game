//A simple chess game
#include <iostream>
#include <chrono>
#include <thread>
#include "chessBoard.h"

bool gameOver = false;

int main() {
  chessBoard board;
  std::chrono::seconds dura(1);
  while (!gameOver) {
    board.printBoard(0);
    if (board.makeMove(0)) break;
    board.printBoard(0);
    std::cout << std::endl;
    std::this_thread::sleep_for(dura);
    board.printBoard(1);
    if(board.makeMove(1)) break;
    board.printBoard(1);
    std::cout << std::endl;
    std::this_thread::sleep_for(dura);
  }
  return 0;
}


  