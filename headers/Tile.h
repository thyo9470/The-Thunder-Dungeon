

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

  // Override + operator
  Position operator+(const Position &other){
    Position ret_pos;
    ret_pos.x_ = x_ + other.x_;
    ret_pos.y_ = y_ + other.y_;
    return ret_pos;
  } 
};

enum class TileType {Empty, Wall, Player, Enemy};

std::string TileTypeToString(TileType tile);

class Tile{

public:
  Tile();
  Tile(TileType type);

  TileType get_type(){return type_;}
 
  // Compare Tile to TileType 
  friend bool operator==(const TileType& tt, const Tile& tl);
  friend bool operator==(const Tile& tl, const TileType& tt);
  friend std::ostream& operator<<(std::ostream& os, const Tile& tt);

protected:
  TileType type_;  

};

class EmptyTile:public Tile{

public:
  EmptyTile():Tile(TileType::Empty){};

};

class WallTile:public Tile{

public:
  WallTile():Tile(TileType::Wall){};

};

/*
    moveable objects
*/

class EntityTile:public Tile{

public:
  EntityTile(TileType type):Tile(type){};

  virtual Position get_position(){return pos_;};
  virtual void SetPosition(Position new_pos);

protected:
  Position pos_;
};

class PlayerTile:public EntityTile{

public:
  PlayerTile();
  
};


#endif // TILE_H
