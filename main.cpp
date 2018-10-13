#include<iostream>

#include<ctime>
#include<stdlib.h>

#include "Board.h"
#include "Tile.h"

using namespace std;

int main(){

  srand(time(NULL));

  TileType test1 = TileType::Empty;

  Empty test2;

  std::cout << (test2 == test1) << std::endl;

  Board* board = new Board(2, 3, 7);


  board->GenerateDungeon();

  board->PrintBoard();

  return 1;
}
