

#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>

#include "Tile.h"
#include "Command.h"


enum class ActionType {Up=101, Right=102, Down=103, Left=104};

class Board{


public:
  Board(int layers, int width, int height);

  std::vector< std::vector< std::vector<Tile*> > > get_board(){return board_;}

  // Create dungeon
  void GenerateDungeon();

  // Move Player
  void MovePlayer(ActionType action_type);

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
  Tile* empty_tile_ref_;
  Tile* wall_tile_ref_;
  PlayerTile* player_tile_;

  std::vector< std::vector< std::vector<Tile*> > > board_;

  // Commands
  Command* up_command_;
  Command* right_command_;
  Command* down_command_;
  Command* left_command_;

};


#endif // BOARD_H_
