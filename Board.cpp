#include<iostream>

#include "Board.h"

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

  Creates a board with a given amount of layers with given dimensions

  @param  (int) layers - The number of rendering layers needed
          (int) width - The width of the dungeon
          (int) height - The height of the dungeon
*/
Board::Board(int layers, int width, int height){
 
  layers_ = layers;
  height_ = height;
  width_ = width;
 
  std::vector< std::vector<TileType> > blank_board;
 
  for(int i = 0; i < height; i++){
    std::vector<TileType> blank_row(width, TileType::Empty);
    blank_board.push_back( blank_row );
  }

  std::vector< std::vector< std::vector<TileType> > > temp_board(layers, blank_board);

  board_ = temp_board;

}

/*
  TEST FUNCTION NOT TO KEEP

  Print the board in a visually pleasing way
*/
void Board::print_board(){

  std::cout << "Thunder Dungeon" <<std::endl;


  for(int x = 0; x < width_; x++){
    for(int y = 0; y < height_; y++){
      std::cout << static_cast<int>(board_[0][y][x]) << " ";
    } 
    std::cout << std::endl;
  }

}
