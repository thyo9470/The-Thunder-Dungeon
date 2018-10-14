

#ifndef _TILE_H_
#define _TILE_H_

#include<iostream>

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

enum class TileType {Empty, Wall, Player, Enemy};

std::string TileTypeToString(TileType tile);

class Tile{

public:
  Tile();
  Tile(TileType type);
 
  // Compare Tile to TileType 
  friend bool operator==(const TileType& tt, const Tile& tl);
  friend bool operator==(const Tile& tl, const TileType& tt);
  friend std::ostream& operator<<(std::ostream& os, const Tile& tt);

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

class Player:public Tile{

public:
  Player();

private:
  Position pos_;

};

#endif // TILE_H
