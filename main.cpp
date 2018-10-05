#include<iostream>

#include "Board.h"

using namespace std;

int main(){

  Board* board = new Board(2, 20, 20);

  board->print_board();

  return 1;
}
