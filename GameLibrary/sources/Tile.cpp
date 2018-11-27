
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
  board[Board::entity_layer_id_][pos_.y_][pos_.x_] = this;

  // Gets all the possible moves - ones not in walls
  std::vector<Position> possible_moves = { Position(pos_.x_, pos_.y_+1), Position(pos_.x_+1, pos_.y_), Position(pos_.x_, pos_.y_-1), Position(pos_.x_-1, pos_.y_)};

  // randomize the possible moves order
  for(int i = 0; i < possible_moves.size(); i++){
    int new_index = rand() % (int)possible_moves.size();

    Position temp_pos = possible_moves[i];
    possible_moves[i] = possible_moves[new_index];
    possible_moves[new_index] = temp_pos;
  }

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
}

void EnemyTile::Follow(std::vector< std::vector< std::vector<Tile*> > > &board){

  std::vector< std::vector<int> > distances;
  std::vector< std::vector<Position> > pred;

  for(unsigned long i = 0; i < board[0].size(); i++){
    std::vector<int> row1(board[0][0].size(), -1);
    distances.push_back( row1 );

    std::vector<Position> row2(board[0][0].size(), Position(-1, -1));
    pred.push_back( row2 );
  }

  std::vector< Position > frontier;

  frontier.insert(frontier.begin(), pos_);
  distances[pos_.y_][pos_.x_] = 0;

  Position player_pos;

  // bfs to finnd player
  while(frontier.size() > 0){
    Position cur_pos = frontier.back();
    frontier.pop_back();

    if(board[Board::player_layer_id_][cur_pos.y_][cur_pos.x_]->get_type() == TileType::Player){
      player_pos = cur_pos;
      break;
    }

    std::vector<Position> possible_moves = { Position(cur_pos.x_, cur_pos.y_+1), Position(cur_pos.x_+1, cur_pos.y_), Position(cur_pos.x_, cur_pos.y_-1), Position(cur_pos.x_-1, cur_pos.y_)};

    for(Position next_pos : possible_moves){
      // skip walls
      if(board[0][next_pos.y_][next_pos.x_]->get_type() != TileType::Empty){
        continue;
      }
      if(distances[next_pos.y_][next_pos.x_] == -1){
        // update distance
        distances[next_pos.y_][next_pos.x_] = distances[cur_pos.y_][cur_pos.x_] + 1;
        // udate predecessor
        pred[next_pos.y_][next_pos.x_] = cur_pos;
        // add next_post to frontier
        frontier.insert(frontier.begin(), next_pos);
      }
    }
  }

  int length = 0;
  Position cur_pos = player_pos;

  // Get the path to the playaer
  while(length < follow_distance_){
    Position pred_pos = pred[cur_pos.y_][cur_pos.x_];
    //move player
    if(pred_pos == pos_){
      pos_ = cur_pos;
      board[Board::entity_layer_id_][pos_.y_][pos_.x_] = this;
      break;
    }
    length++;
    cur_pos = pred_pos;
  }
  if(length  == follow_distance_){
    DFSMove(board);
  }
}
