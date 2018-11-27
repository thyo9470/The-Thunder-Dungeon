
#include "../headers/Tile.h"
#include "../headers/Board.h"
#include <queue>
#include <vector>
#include <cmath>

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
    case 4:
      return "Exit";
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

/*
    Player class methods
*/

PlayerTile::PlayerTile():EntityTile(TileType::Player){
  pos_ = Position(3,3); 
}

void EntityTile::SetPosition(Position new_position){
  pos_ = new_position;
}

EnemyTile::EnemyTile(Position startPos):EntityTile(TileType::Enemy)
{
  pos_ = startPos;
  next_moves_.push_back(startPos);
}

/*
 * Moves an enemy according to dfs search
 *
 * @param board The board's tile information
 * */
void EnemyTile::DFSMove(std::vector< std::vector< std::vector<Tile*> > > &board)
{
  // Reset the algorithm after it has explored every option
  if(next_moves_.size() == 0){
      prev_moves_.clear();
      next_moves_.push_back(pos_);
  }

  // Get current moves
  Position next = next_moves_.back();
  next_moves_.pop_back();

  //Move the enemy
  pos_ = next;
  board[Board::entity_layer_id_][next.y_][next.x_] = this;

  // Gets all the possible moves - ones not in walls
  std::vector<Position> possible_moves = { Position(pos_.x_, pos_.y_+1), Position(pos_.x_+1, pos_.y_), Position(pos_.x_, pos_.y_-1), Position(pos_.x_-1, pos_.y_)};

  for(int i = possible_moves.size()-1; i >= 0; i--){
    Position p_move = possible_moves[i];
    for(int l = 0; l < board.size(); l++){
      if(l == Board::player_layer_id_){
        continue;
      }
      if(board[l][p_move.y_][p_move.x_]->get_type() != TileType::Empty){
          possible_moves.erase(possible_moves.begin() + i);
          break;
      }
    }
  }

  /*if(board[0][pos_.y_ + 1][pos_.x_]->get_type() == TileType::Empty){
      possible_moves.push_back(Position(pos_.x_, pos_.y_ + 1));
    }
  if(board[0][pos_.y_ - 1][pos_.x_]->get_type() == TileType::Empty){
      possible_moves.push_back(Position(pos_.x_, pos_.y_ - 1));
    }
  if(board[0][pos_.y_][pos_.x_ + 1]->get_type() == TileType::Empty){
      possible_moves.push_back(Position(pos_.x_ + 1, pos_.y_));
    }
  if(board[0][pos_.y_][pos_.x_ - 1]->get_type() == TileType::Empty){
      possible_moves.push_back(Position(pos_.x_ - 1, pos_.y_));
    }*/

  prev_moves_.push_back(next);

  // Test if any of the square adjacent are unvisited
  for(Position possible : possible_moves){

      // Check if any possible moves have been taken
      bool found = false;

      for(Position prev : prev_moves_){
          if(prev == possible){
              found=true;
              break;
            }
        }

      // Move
      if(!found){
          next_moves_.push_back(next);
          next_moves_.push_back(possible);
          break;
        }

    }
  Follow(board);
}

void EnemyTile::Follow(std::vector< std::vector< std::vector<Tile*> > > &board){

  std::vector< std::vector<int> > distances;

  for(unsigned long i = 0; i < board[0].size(); i++){
    std::vector<int> row(board[0][0].size(), 0);
    distances.push_back( row );
  }

  std::vector< Position > frontier;

  frontier.insert(frontier.begin(), pos_);

  while(frontier.size() > 0){
    Position cur_pos = frontier.back();
    frontier.pop_back();


  }
}
