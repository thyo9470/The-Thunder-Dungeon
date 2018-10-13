

#ifndef _TILE_H_
#define _TILE_H_

#include<iostream>

enum class TileType {Empty, Wall, Player, Enemy};

std::string TileTypeToString(TileType tile);

class Tile{

public:
  Tile();
  Tile(TileType type);
 
  // Compare Tile to TileType 
  friend bool operator==(const TileType& tt, const Tile& tl);
  friend bool operator==(const Tile& tl, const TileType& tt);
  friend std::ostream& operator<<(std::ostream&, const Tile& tt);

protected:
  TileType type_;  

};

class Empty:public Tile{

public:
  Empty():Tile(TileType::Empty){};

};

class Wall:public Tile{

public:
  Wall():Tile(TileType::Wall){};

};

#endif // TILE_H
