

#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>
#include <QJsonObject>
#include <QObject>

#include "Tile.h"
#include "Command.h"

enum class ActionType {Up=101, Right=102, Down=103, Left=104, TEST=999};

class Board : public QObject {
  Q_OBJECT

public:
  Board(int layers, int width, int height);

  std::vector< std::vector< std::vector<Tile*> > > get_board(){return board_;}
  int get_level() {return level_;}
  PlayerTile* get_player() {return player_tile_;}

  // Move Player
  void MovePlayer(ActionType action_type);

  void Read(const QJsonObject &json);
  void Write(QJsonObject &json) const;

  const int static player_layer_id_ = 2;
  const int static entity_layer_id_ = 3;
  const int chest_layer_id_ = 1;

signals:
  void StartBattle();
  void DropItemSignal();

private:
  // number of object layers
  int layers_;

  // The layer that contains enemies and the player

  // Number of rooms in each row and column
  int width_;
  int height_;

  // Number of tiles in each row and column
  int width_res_;
  int height_res_;

  // Pointers to Tile objects for flyweight
  Tile* empty_tile_ref_;
  Tile* void_tile_ref_;
  Tile* wall_tile_ref_;
  PlayerTile* player_tile_;
  Tile* exit_tile_;
  Tile* chest_closed_tile_ref_;
  Tile* chest_opened_tile_ref_;
  std::vector<EnemyTile *> enemies_;

  std::vector< std::vector< std::vector<Tile*> > > board_;

  // Board data
  int level_;
  double chest_percent_ = 0.25; // chance of making a chest in a room

  // Commands
  Command* up_command_;
  Command* right_command_;
  Command* down_command_;
  Command* left_command_;

  // Get the tile type at a given layer and position
  TileType GetTileAtPosition(int layer, Position pos);

  // Called at the start of a new level
  void NewLevel();
  std::vector< std::vector< std::vector<Tile*> > > GenerateBlankBoard();

  // Create dungeon
  void GenerateDungeon();
  void FormatDungeon();

  // Spawn and move enemies
  void SpawnEnemies();
  void MoveEnemies();
  void ClearEnemies();
  void DeleteEnemy(Position pos);
  void AddExtraToRoom(int x, int y, int width, int height);

  void GenerateChests();

  // checks it an entity tile has collided with another object
  Tile* CheckCollision(Position pos);
};


#endif // BOARD_H_
