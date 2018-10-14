
#include "../headers/Tile.h"
/*
  Convert a given TileType to a string

  @param  (TileType) tile - The tile you want the type of in a string
  @return (string)        - The tile type as a string 
*/
std::string TileTypeToString(TileType tile){
  int type = static_cast<int>(tile);
  switch(type){
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

std::ostream& operator<<(std::ostream& os, const Tile& tt){
  
  int current = static_cast<int>(tt.type_);
  switch(current){
	  case 0:
	    os << "  ";
	    break;
	  case 1:
	    os << "██";
	    break;
    case 2:;
      os << ":(";
  }
  return os;
}

Tile::Tile(){
  type_ = TileType::Empty;
}

Tile::Tile(TileType type){
  type_ = type;
}

/*
    Player class methods
*/

PlayerTile::PlayerTile():EntityTile(TileType::Player){
  pos_ = Position(3,3); 
}

void EntityTile::SetPosition(Position new_position){
  pos_ = new_position;
}

