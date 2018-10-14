#include<iostream>

#include<ctime>
#include<stdlib.h>

#include "Game.h"
#include "Board.h"
#include "Tile.h"

using namespace std;

int main(){

  srand(time(NULL));

  Game game;

  game.GameLoop();

  return 1;
}
