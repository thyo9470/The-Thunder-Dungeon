#include<iostream>

#include<ctime>
#include<stdlib.h>

#include "Board.h"

using namespace std;

int main(){

  srand(time(NULL));

  Board* board = new Board(2, 3, 5);

  board->PrintBoard();

  board->GenerateDungeon();

  return 1;
}
