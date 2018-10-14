

#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>
#include "Tile.h"





class Board{


public:
  Board(int layers, int width, int height);

  // Create dungeon
  void GenerateDungeon();

  // Move Player
  void MovePlayer();

  void PrintBoard(); //TESTING FUNCTION DO NOT KEEP

private:
  // number of object layers
  int layers_;
  // Number of rooms in each row and column
  int width_;
  int height_;

  // Number of tiles in each row and column
  int width_res_;
  int height_res_;

  //Pointers to Tile objects for flyweight
  Tile* empty_ref_;
  Tile* wall_ref_;
  Tile* player_;

  std::vector< std::vector< std::vector<Tile*> > > board_;


};


#endif // BOARD_H_
