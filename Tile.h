

#ifndef _TILE_H_
#define _TILE_H_

enum class TileType {Empty, Wall, Player, Enemy};

class Tile{

public:
  Tile();
  Tile(TileType type);

protected:
  TileType type_;  

};

class Empty:public Tile{

public:
  Empty():Tile(TileType::Empty);

};

class Wall:public Tile{

public:
  Wall():Tile(TileType::Wall);

};

#endif // TILE_H
