#include<iostream>

#include<ctime>
#include<stdlib.h>

#include "Board.h"

using namespace std;

int main(){

  srand(time(NULL));

  Board* board = new Board(2, 4, 2);


  board->GenerateDungeon();

  board->PrintBoard();

  return 1;
}
