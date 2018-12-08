

#ifndef _TILE_H_
#define _TILE_H_

#include<iostream>
#include<vector>

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

  bool operator!=(const Position &other) {
    return x_ != other.x_ || y_ != other.y_;
  }

  // Override + operator
  Position operator+(const Position &other){
    Position ret_pos;
    ret_pos.x_ = x_ + other.x_;
    ret_pos.y_ = y_ + other.y_;
    return ret_pos;
  } 
};

enum class TileType {Empty, Wall, Player, Enemy, Exit, Void, Chest};

std::string TileTypeToString(TileType tile);

class Tile{

public:
  Tile();
  Tile(TileType type);

  TileType get_type(){return type_;}
 
  // Compare Tile to TileType 
  friend bool operator==(const TileType& tt, const Tile& tl);
  friend bool operator==(const Tile& tl, const TileType& tt);

protected:
  TileType type_;  

};

class EmptyTile:public Tile{

public:
  EmptyTile():Tile(TileType::Empty){}

};

class WallTile:public Tile{

public:
  WallTile():Tile(TileType::Wall){}

};

class ExitTile:public Tile{

public:
  ExitTile():Tile(TileType::Exit){}
};

class ChestTile:public Tile{

public:
  ChestTile():Tile(TileType::Chest){}
};

/*
    moveable objects
*/

class EntityTile:public Tile{

public:
  EntityTile(TileType type):Tile(type){}

  virtual Position get_position(){return pos_;}
  virtual void SetPosition(Position new_pos);

protected:
  Position pos_;
};

class PlayerTile:public EntityTile{

public:
  PlayerTile();
  
};

// Represents a specific type of enemy with its own movement algorithm
class EnemyTile:public EntityTile{

public:
  EnemyTile(Position startPos);
  void DFSMove(std::vector< std::vector< std::vector<Tile*> > > &board);
  void Follow(std::vector< std::vector< std::vector<Tile*> > > &board);

private:
  int follow_distance_ = 4;

  std::vector<Position> next_moves_;
  std::vector<Position> prev_moves_;

};

class VoidTile:public Tile{

public:
  VoidTile():Tile(TileType::Void){}
};


#endif // TILE_H
