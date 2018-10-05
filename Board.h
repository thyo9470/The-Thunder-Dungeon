

#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>

enum class TileType {Empty, Wall, Player, Enemy};

std::string TileTypeToString(TileType tile);

class Board{

public:
  Board(int layers, int width, int height);

  void print_board(); //TESTING FUNCTION DO NOT KEEP

private:
  int layers_;
  int width_;
  int height_;

  std::vector< std::vector< std::vector<TileType> > > board_;


};


#endif // BOARD_H_
