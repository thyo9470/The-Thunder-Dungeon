

#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>
#include "Tile.h"




struct Position{
  int x_;
  int y_;

  Position():x_(0),y_(0){}

  Position(int x, int y){
    x_ = x;
    y_ = y;
  }

  bool operator==(const Position &other) {
    return x_ == other.x_ && y_ == other.y_;
  }

};

class Board{


public:
  Board(int layers, int width, int height);

  // Create dungeon
  void GenerateDungeon();

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

  std::vector< std::vector< std::vector<TileType> > > board_test_;
  std::vector< std::vector< std::vector<Tile*> > > board_;


};


#endif // BOARD_H_
