
#include "Tile.h"
/*
  Convert a given TileType to a string

  @param  (TileType) tile - The tile you want the type of in a string
  @return (string)        - The tile type as a string 
*/
std::string TileTypeToString(TileType tile){
  int test = static_cast<int>(tile);
  switch(test){
    case 0:
      return "Empty";
    case 1:
      return "Wall";
    case 2:
      return "Player";
    case 3:
      return "Enemy";
    default:
      return "UNKNOWN";
  }
}


/*
    Compare an instance of the Tile class to an instance of the TileType class
*/
bool operator==(const TileType& tt, const Tile& tl){
  return tt == tl.type_;
}

bool operator==(const Tile& tl, const TileType& tt){
  return tt == tl.type_;
}

Tile::Tile(){
  type_ = TileType::Empty;
}

Tile::Tile(TileType type){
  type_ = type;
}

