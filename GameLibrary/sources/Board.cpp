#include<iostream>
#include<sstream>

#include<vector>
#include<algorithm>
#include<stdlib.h>
#include<QJsonArray>

#include "../headers/Board.h"
#include "../headers/Tile.h"
#include "../headers/Command.h"

/**
 * @brief Board::Board
 *
 * Creates a board with a given amount of layers with given dimensions
 *
 * @param layers - The number of rendering layers
 * @param width - Number of rooms wide the dungeon is
 * @param height - Number of rooms high the dungeon is
 */

Board::Board(int layers, int width, int height){

  // Initiate Tile reference objeccts for flyweight pattern 
  empty_tile_ref_ = new EmptyTile();
  wall_tile_ref_ = new WallTile();
  player_tile_ = new PlayerTile();
  exit_tile_ = new ExitTile();
  void_tile_ref_ = new VoidTile();
  chest_closed_tile_ref_ = new ChestClosedTile();
  chest_opened_tile_ref_ = new ChestOpenedTile();

  // Initiate Command objects for command pattern
  up_command_ = new UpCommand();
  right_command_ = new RightCommand();
  down_command_ = new DownCommand();
  left_command_ = new LeftCommand();

  layers_ = layers;

  // Number of rooms wide/high
  width_ = width;
  height_ = height;

  // Number of sprites wide/high
  width_res_ = width * 6 + 1;
  height_res_ = height * 6 + 1;

  // setup board data
  level_ = 0;

  NewLevel();
}

/**
 * @brief Board::NewLevel
 *
 * Creates a new level by doing the following:
 *  - Setting all board layeres to default values
 *  - Generating new maze
 *  - Instantiate Tiles
 *  - Spawn enemies
 */

void Board::NewLevel(){
  std::vector< std::vector< std::vector<Tile*> > > temp_board = GenerateBlankBoard();

  // place player tile
  player_tile_->SetPosition(Position(3,3));
  temp_board[player_layer_id_][3][3] = player_tile_;

  // place exit tile
  temp_board[chest_layer_id_][height_res_-4][width_res_-4] = exit_tile_;

  board_ = temp_board;
  GenerateDungeon();
  FormatDungeon();
  SpawnEnemies();

  // update board data
  level_++;
}

/**
 * @brief Board::GenerateBlankBoard
 *
 * Creates a blank board where:
 *   - The first render layer is assumed to be all walls
 *   - Every other render layers is asumed to be all empty
 *
 * @return
 */

std::vector< std::vector< std::vector<Tile*> > > Board::GenerateBlankBoard(){
  std::vector< std::vector<Tile*> > blank_board;
  std::vector< std::vector< std::vector<Tile*> > > board;

  // make first layer all walls
  for(int i = 0; i < height_res_; i++){
    std::vector<Tile*> blank_row(width_res_, wall_tile_ref_);
    blank_board.push_back( blank_row );
  }

  board.push_back(blank_board);

  // make all other layers empty
  blank_board.clear();

  for(int i = 0; i < height_res_; i++){
    std::vector<Tile*> blank_row(width_res_, empty_tile_ref_);
    blank_board.push_back( blank_row );
  }

  for(int i = 1; i < layers_; i++){
    board.push_back(blank_board);
  }

  return board;
}

/**
 * @brief Board::GenerateDungeon
 *
 * Create the dungeon layout using a modified maze generation algorithm
 *
 * The dungeon is created with the following steps:
 *  1. Create a maze
 *  2. Make random sized rooms
 *  3. connect those rooms using the created maze
 *
 */

void Board::GenerateDungeon(){
  
  /*
     -------------------------------------------
      Part 1 - Setup for simple Maze generation
     -------------------------------------------
  */

  std::vector< std::vector<TileType> > dungeon;

  int temp_width = width_*2+1;
  int temp_height = height_*2+1;

  for(int i = 0; i < temp_height; i++){
    std::vector<TileType> blank_row(temp_width, TileType::Empty);
    dungeon.push_back( blank_row );
  }

  /*
     -------------------------------------------
      Part 2 - Generate maze using radnom Kruskel's algorithm
     -------------------------------------------
  */

  // stores all walls seperating two empty cells(rooms)
  std::vector<Position> walls;

  // stores the cells that are connected in sets
  // every cell will start in its own set
  std::vector< std::vector<Position> > cells;

  // create empty cells and populate walls and cells vector
  for(int x = 0; x < temp_width; x++){
    for(int y = 0; y < temp_height; y++){

      if( (x%2 == 0) || (y%2 == 0) ){
        dungeon[y][x] = TileType::Wall;
        // check if wall is not a perimeter wall
        if( x != 0 && y != 0 && x+1 != temp_width && y+1 != temp_height && ((x%2 == 0) != (y%2 == 0))){
          Position wall_pos(x,y);
          walls.push_back(wall_pos);
        }
      }else{
        std::vector<Position> cell_set;
        Position cell_pos(x, y);
        cell_set.push_back(cell_pos);
        cells.push_back(cell_set);
      }

    } 
  }
  
  // shuffle the walls for randomness
  std::random_shuffle(walls.begin(), walls.end());

  // while we still ahve walls to check
  while(walls.size()){

    Position cur = walls.back();

    bool side = true;
    if(cur.y_%2 == 0){
      side = false;
    }

    Position cell1;
    Position cell2;

    // get the cells that the current wall seperate
    if(side){
      cell1.x_ = cur.x_ - 1;
      cell1.y_ = cur.y_;

      cell2.x_ = cur.x_ + 1;
      cell2.y_ = cur.y_;
    }else{
      cell1.x_ = cur.x_;
      cell1.y_ = cur.y_ - 1;

      cell2.x_ = cur.x_;
      cell2.y_ = cur.y_ + 1;
    }

    int cell1_place;
    int cell2_place;

    for(unsigned int i = 0; i < cells.size(); i++){
      if( std::find(cells[i].begin(), cells[i].end(), cell1) != cells[i].end() ){
        cell1_place = i;
      }
      if( std::find(cells[i].begin(), cells[i].end(), cell2) != cells[i].end() ){
        cell2_place = i;
      }
    }

    // if the two cells are not in the same set
    if(cell1_place != cell2_place){
      
      // set wall to empty to connect cells
      dungeon[cur.y_][cur.x_] = TileType::Empty;       

      // store the vector cell2 in a temp value for clean code
      std::vector<Position> cell2_set = cells[cell2_place];

      // combine cell1 and cell2's sets
      cells[cell1_place].insert( cells[cell1_place].end(), cell2_set.begin(), cell2_set.end() );

      // free memory of values in cell2_set
      cells[cell2_place].clear();

      // remove cell2's vector from cells
      cells.erase( cells.begin() + cell2_place );

    } 
    
	
    walls.pop_back();
  }
	
  walls.clear();
  cells.clear();	

  /*
     -------------------------------------------
      Part 3 - Apply dungeon to actual board
     -------------------------------------------
  */

  for(int x = 0; x < temp_width; x++){
    for(int y = 0; y < temp_height; y++){
      if(dungeon[y][x] == TileType::Empty){
         
        // if this is the position of a room
        if( (x%2 == 1) && (y%2 == 1) ){

          Position room_center(x*3,y*3);
  
          int room_width = std::rand() % 4;
          int room_height = std::rand() % 4;

          // make room at position
          for(int i = room_center.x_-room_width; i <= room_center.x_+room_width; i++){
            for(int j = room_center.y_-room_height; j <= room_center.y_+room_height; j++){
              board_[0][j][i] = empty_tile_ref_;
            }
          }

          // add extras to room
          AddExtraToRoom(room_center.x_, room_center.y_, room_width, room_height);

        } 
        // if this is the position of a hallway
        else if( (x%2==1) || (y%2 == 1)  ){
          
          bool side = true;
          if(y%2 == 0){
            side = false;
          } 


          if(side){

            int x_start = (x-1)*3;

            int x_end = (x+1)*3;

            for(int i = x_start; i < x_end; i++){
              board_[0][y*3][i] = empty_tile_ref_;  
            }
          }else{
            int y_start = (y-1)*3;

            int y_end = (y+1)*3;

            for(int i = y_start; i < y_end; i++){
              board_[0][i][x*3] = empty_tile_ref_;  
            }
            
          }

        }
 
      } 
    }
  }

  // make sure boarder is all walls
  std::vector<Tile*> wall_row(width_res_, wall_tile_ref_);
  board_[0][0] = wall_row;
  board_[0][height_res_-1] = wall_row;

  for(int i = 0; i < height_res_; i++){
    board_[0][i][0] = wall_tile_ref_;
    board_[0][i][width_res_-1] = wall_tile_ref_;
  }

  // make sure player can move around exit
  for(int i = width_res_-5; i <= width_res_-3; i++){
    for(int j = height_res_-5; j <= height_res_-3; j++){
      board_[0][j][i] = empty_tile_ref_;
    }
  }

}

/**
 * @brief Board::AddExtraToRoom
 *
 * Adds some kind of features to room (ie. chests)
 *
 * @param x - center of room x coordinate
 * @param y - center of room y coordinate
 * @param width - width of room
 * @param height - height of room
 */

void Board::AddExtraToRoom(int x, int y, int width, int height){

  double try_for_chest = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

  if(try_for_chest < chest_percent_){

      // The place in the room the chest will be placed
      int room_x = (rand() % ((2*width)+1)) - width;
      int room_y = (rand() % ((2*height)+1)) - height;

      // the place on the board the chest is placed
      int chest_x = x + room_x;
      int chest_y = y + room_y;

      Tile* test_placement = CheckCollision(Position(chest_x, chest_y));

      if(test_placement == empty_tile_ref_){
        board_[chest_layer_id_][chest_y][chest_x] = chest_closed_tile_ref_;
      }

  }

}

/**
 * @brief Board::FormatDungeon
 *
 * Convert any walls that aren't touching an empty square into void squares
 *  (Touching includes diagonal)
 *
 */

void Board::FormatDungeon(){
  // loop through each coordinate
  for(int y = 0; y < board_[0].size(); y++){
    for(int x = 0; x < board_[0][y].size(); x++){

      bool is_wall = false;

      // loop around values at coordinate
      for(int i = (y==0 ? y : y-1) ; i <= (y==board_[0].size()-1 ? y : y+1); i++){
        for(int j = (x==0 ? x : x-1); j <= (x==board_[0][0].size()-1 ? x : x+1); j++){
          if(board_[0][i][j]->get_type() == TileType::Empty){
            is_wall = true;
          }
        }
      }

      if(!is_wall){
        board_[0][y][x] = void_tile_ref_;
      }

    }
  }
}

/**
 * @brief Board::SpawnEnemies
 *
 * - Populate board with enemies
 * - Ony spawns enemies in the center of rooms
 *
 */

void Board::SpawnEnemies()
{
  ClearEnemies();

  // Spawn a bunch of enemies in a grid
  Position start_room_pos = Position(9, 3);
  int room_spacing = 6;
  Position end_room_pos = Position(width_ * room_spacing - 3, width_ * room_spacing - 3);
  for(int i = start_room_pos.y_; i < end_room_pos.y_; i+=room_spacing){
      for(int j = start_room_pos.x_; j < end_room_pos.x_; j+=room_spacing){
          EnemyTile * enemy = new EnemyTile(Position(i, j));
          board_[entity_layer_id_][j][i] = enemy;
          enemies_.push_back(enemy);
        }
    }
}

/**
 * @brief Board::MoveEnemies
 *
 * Makes all enemies take their turn
 *
 * @return Whether an enemy was encountered or not
 */

void Board::MoveEnemies()
{
  for(EnemyTile * enemy : enemies_){
      board_[entity_layer_id_][enemy->get_position().y_][enemy->get_position().x_] = empty_tile_ref_;
      //enemy->DFSMove(board_);
      enemy->Follow(board_);
  }
  Tile* test = CheckCollision(player_tile_->get_position());
  if(test->get_type() == TileType::Enemy){
      DeleteEnemy(player_tile_->get_position());
      emit StartBattle();
  }
}

/**
 * @brief Board::ClearEnemies
 *
 * Properly delete all enemies
 *
 */

void Board::ClearEnemies()
{
  for(int i = 0; i < enemies_.size(); i++){
    delete enemies_[i];
  }
  enemies_.clear();
}

void Board::DeleteEnemy(Position pos){
  board_[entity_layer_id_][pos.y_][pos.x_] = empty_tile_ref_;

  for(int i = 0; i < enemies_.size(); i++){
    if(enemies_[i]->get_position() == pos){
      enemies_.erase(enemies_.begin() + i);
    }
    }
}

/**
 * @brief Board::MovePlayer
 *
 * Moves the player directed by the given action
 * Calls move enemies after
 *
 * @param action_type - The move the player is going to take
 */

void Board::MovePlayer(ActionType action_type){
  //int type = static_cast<int>(action_type);
  Position old_pos =  player_tile_->get_position(); 
  board_[player_layer_id_][old_pos.y_][old_pos.x_] = empty_tile_ref_;
  Position attempted_pos = old_pos;
  switch(action_type){
    case ActionType::Up : // up
      attempted_pos = old_pos + Position(0,-1);
      if(GetTileAtPosition(0, attempted_pos) == TileType::Empty){
        up_command_->execute(player_tile_);
      }
      break;
    case ActionType::Right: // right
      attempted_pos = old_pos + Position(1, 0);
      if(GetTileAtPosition(0, attempted_pos) == TileType::Empty){
        right_command_->execute(player_tile_);
      }
      break;
    case ActionType::Down: // down
      attempted_pos = old_pos + Position(0, 1);
      if(GetTileAtPosition(0, attempted_pos) == TileType::Empty){
        down_command_->execute(player_tile_);
      }
      break;
    case ActionType::Left: // left
      attempted_pos = old_pos + Position(-1, 0);
      if(GetTileAtPosition(0, attempted_pos) == TileType::Empty){
        left_command_->execute(player_tile_);
      }
      break;
  }
  // move player
  Position new_pos =  player_tile_->get_position(); 
  board_[player_layer_id_][new_pos.y_][new_pos.x_] = player_tile_;
  // test for collision
  Tile* test = CheckCollision(new_pos);
  switch(test->get_type()){
    case TileType::Exit: // move to next level
      NewLevel();
      emit StartBattle();
      break;
    case TileType::Enemy: // fight enemy
      DeleteEnemy(player_tile_->get_position());
      emit StartBattle();
      break;
    case TileType::ChestClosed:
      board_[chest_layer_id_][new_pos.y_][new_pos.x_] = chest_opened_tile_ref_;
      emit DropItemSignal();
      break;
    default: // have enemies take their turn
      MoveEnemies();
      break;
  }
}

/**
 * @brief Board::Read
 *
 * Loads the board from previous save
 *
 * @param json - The save json object to load
 */

void Board::Read(const QJsonObject &json)
{
  // Make sure that all part of the board save exist
  if (!json.contains("level") || !json["level"].toInt() ||
      !json.contains("board") || !json["board"].isArray() ||
      !json.contains("player") || !json["player"].isObject() ||
      !json.contains("enemies") || !json["enemies"].isArray()){
      qWarning("There is no board save - couldn't load the board.");
      return;
    }

  level_ = json["level"].toInt();

  // Clean the board and enemies before proceeding
  ClearEnemies();
  board_ = GenerateBlankBoard();

  // Load the static tiles by setting them to the board reference
  QJsonArray board_array = json["board"].toArray();
  for (int l = 0; l < board_array.size(); l++) {
      QJsonArray level_array = board_array[l].toArray();
      for (int y = 0; y < level_array.size(); y++) {
          QJsonArray row_array = level_array[y].toArray();
          for (int x = 0; x < row_array.size(); x++) {
              switch ((TileType)row_array[x].toInt()) {
                case TileType::Empty:
                  board_[l][y][x] = empty_tile_ref_;
                  break;
                case TileType::Void:
                  board_[l][y][x] = void_tile_ref_;
                  break;
                case TileType::Wall:
                  board_[l][y][x] = wall_tile_ref_;
                  break;
                case TileType::Exit:
                  board_[l][y][x] = exit_tile_;
                  break;
                case TileType::ChestClosed:
                  board_[l][y][x] = chest_closed_tile_ref_;
                  break;
                case TileType::ChestOpened:
                  board_[l][y][x] = chest_opened_tile_ref_;
                  break;
                }
            }
        }
    }

  // Load the player - currently just set the position of the player tile
  QJsonObject player_save = json["player"].toObject();
  Position player_pos = Position(player_save["pos_x"].toInt(), player_save["pos_y"].toInt());

  player_tile_->SetPosition(player_pos);
  board_[player_layer_id_][player_pos.y_][player_pos.x_] = player_tile_;

  // Load the enemy tiles
  QJsonArray enemies = json["enemies"].toArray();
  for(int i = 0; i < enemies.size(); i++){
      QJsonObject enemy_save = enemies[i].toObject();
      Position enemy_pos = Position(enemy_save["pos_x"].toInt(), enemy_save["pos_y"].toInt());

      EnemyTile * enemy = new EnemyTile(enemy_pos);
      board_[entity_layer_id_][enemy_pos.y_][enemy_pos.x_] = enemy;
      enemies_.push_back(enemy);
    }
}

/**
 * @brief Board::Write
 *
 * Save the current board to Json
 *
 * @param json - The save Json object to save to
 */

void Board::Write(QJsonObject &json) const
{
  // Save the static tiles into a 3D QJsonArray (tiles are saved by the integer in the TileType enum)
  QJsonArray board_array;
  for (const std::vector< std::vector<Tile*> > &level : board_) {
        QJsonArray level_array;
        for (const std::vector<Tile*> &row : level) {
            QJsonArray row_array;
            for (Tile* tile : row) {
              row_array.append(QJsonValue((int)tile->get_type()));
          }
            level_array.append(row_array);
       }
        board_array.append(level_array);
    }

  // Save the enemies into an array of objects
  QJsonArray enemies;
  for(EnemyTile * enemy : enemies_){
      QJsonObject enemy_save;
      enemy_save["type"] = (int)enemy->get_type(); // Currently represents the enemy TileType
      enemy_save["pos_x"] = enemy->get_position().x_;
      enemy_save["pos_y"] = enemy->get_position().y_;
      enemies.append(enemy_save);
    }

  // Save the player into an object
  QJsonObject player_save;
  player_save["pos_x"] =  QJsonValue((int)player_tile_->get_position().x_);
  player_save["pos_y"] =  QJsonValue((int)player_tile_->get_position().y_);

  json["board"] = board_array;
  json["level"] = level_; // Save the current level the player was on
  json["enemies"] = enemies;
  json["player"] = player_save;
}

/**
 * @brief Board::GetTileAtPosition
 *
 * Gets the tile on a layer at a position
 *
 * @param layer - The layer the tile is on
 * @param pos - The position the tile is at
 * @return The wanted tile
 */

TileType Board::GetTileAtPosition(int layer, Position pos){
  if(pos.x_ >= 0 && pos.y_ >= 0 && pos.x_ < width_res_ && pos.y_ < height_res_){
      return board_[layer][pos.y_][pos.x_]->get_type();
  }
  throw std::invalid_argument( "index out of range" );
}

/**
 * @brief Board::CheckCollision
 *
 * Checks if an entity ha collided with something else
 *  (Can only see one collision at a time)
 *
 * @param entity - The entity to check colliions with
 * @return The tile the entity collided with (empty if nothing)
 */
::
Tile* Board::CheckCollision(Position pos){
  if(pos.x_ == 0 || pos.y_ == 0 || pos.x_ == width_res_-1 || pos.y_ == height_res_-1){
    return wall_tile_ref_;
  }
  for(int i = 0; i < layers_; i++){
    Tile* check_tile = board_[i][pos.y_][pos.x_];
    if( !((*check_tile) == TileType::Empty) && check_tile != player_tile_){
        return check_tile;
    }
  }
  return empty_tile_ref_;
}
