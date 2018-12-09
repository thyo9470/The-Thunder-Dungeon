#include "headers/Window.h"
#include "ui_mainwindow.h"

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <iostream>
#include <array>
#include "./headers/Board.h"

#include "./headers/Tile.h"

Window::Window(QWidget *parent, int window_x, int window_y) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize the scene, which will hold all the objects to render
    scene_ = new QGraphicsScene();
    ui->graphicsView->setScene(scene_);

    // Keep scrollbars from appearing
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Keep the scene from resizing
    ui->graphicsView->setFixedSize(window_x, window_y);
    scene_->setSceneRect(0, 0, window_x, window_y);

    ui->equipmentFoundDialogue->setVisible(false);
    ui->consumableFoundDialogue->setVisible(false);
    ui->pauseMenu->setVisible(false);

    // Hold all the images
    sprite_sheet_ = QPixmap(":/images/Sprites.png");
    dungeon_sheet_ = QPixmap(":/images/tiles_dungeon_v1.1.png");
    player_sheet_ = QPixmap(":/images/Player.png");
    slime_sheet_ = QPixmap(":/images/Slime.png");

}

Window::~Window()
{
    delete ui;
}

void Window::keyPressEvent(QKeyEvent *event)
{
    if(paused_){ return; }
    emit KeyPressSignal(event);
}

/**
 * Used to determine whether to save item choice dialogue in the item save
 * @return
 */
bool Window::GetStillChoosingItem()
{
  return ui->equipmentFoundDialogue->isVisible() || ui->consumableFoundDialogue->isVisible();
}

/**
 * When called, re-renders the board. NOTE: currently doesn't delete the memory created
 *
 * @param tileInfo A 3 dimensional qlist representing the board's tiles to render
 */
void Window::UpdateBoard(std::vector< std::vector< std::vector<Tile*> > > tile_info)
{
  scene_->clear();
  for(unsigned y = 0; y < tile_info[0].size(); y++){
    for(unsigned int x = 0; x < tile_info[0][y].size(); x++){
      //Generate dungeon sprites
      Tile* dungeon_tile = tile_info[0][y][x];

      QGraphicsPixmapItem * pixmap;
      // get dungeon sprite
      if(dungeon_tile->get_type() == TileType::Wall){
        std::array<bool, 4> walls = {true, true, true, true};

        if(y <= 0 ){
          walls[0] = false;
        }else if(tile_info[0][y-1][x]->get_type() != TileType::Wall){ //check above
          walls[0] = false;
        }

        if(x >= tile_info[0][y].size()-1){
          walls[1] = false;
        }else if(tile_info[0][y][x+1]->get_type() != TileType::Wall){ // check right
          walls[1] = false;
        }

        if(y >= tile_info[0].size()-1){
          walls[2] = false;
        }else if(tile_info[0][y+1][x]->get_type() != TileType::Wall){ // check below
          walls[2] = false;
        }

        if(x <= 0){
          walls[3] = false;
        }else if(tile_info[0][y][x-1]->get_type() != TileType::Wall){ // check left
          walls[3] = false;
        }

        pixmap = GetWallSprite(walls);

      }else{
        pixmap = GetDungeonSprite(dungeon_tile);

      }

      pixmap->setPos(x * dungeon_sprite_size_ * dungeon_tile_scale_ , y * dungeon_sprite_size_ * dungeon_tile_scale_ );
      pixmap->setScale(pixmap->scale() * dungeon_tile_scale_);
      scene_->addItem(pixmap);

      // find the tile type to get sprite of
      Tile* tile = tile_info[1][y][x];
      for(unsigned int l = 1; l < tile_info.size(); l++){
          Tile cur_sq = (*tile_info[l][y][x]);
          if((cur_sq == TileType::Empty) == false){
            tile = tile_info[l][y][x];
          }
        }


      // Create and add the tile to the scene

      if(tile->get_type() != TileType::Empty){
        pixmap = GetDungeonSprite(tile);

        pixmap->setPos(x * dungeon_sprite_size_ * dungeon_tile_scale_ , y * dungeon_sprite_size_ * dungeon_tile_scale_ );
        pixmap->setScale(pixmap->scale() * dungeon_tile_scale_);
        scene_->addItem(pixmap);
      }

    }
  }
}

/**
 * @brief Window::GetWallSprite
 *
 * Given the an bool array of size four saying which tiles are walls and are not
 *  the function returns the Pixmap with the correct wall sprite
 *
 * @param wall_sides - array of which spaces are walls or not: [up, right, down, left]
 * @return The pixmap with the correct wall sprite
 */

QGraphicsPixmapItem* Window::GetWallSprite(std::array<bool, 4> wall_sides){
  // pink square to show when a sprite isn't loaded properly
  int tile_pos_x = 15;
  int tile_pos_y = 8;

  // all the wall choices
  std::array<bool, 4> all_sides = {true, true, true, true}; // all sides are walls

  std::array<bool, 4> up_right = {true, true, false, false}; // up-right corner
  std::array<bool, 4> up_left = {true, false, false, true}; // up-left corner
  std::array<bool, 4> down_right = {false, true, true, false}; // down-right corner
  std::array<bool, 4> down_left = {false, false, true, true}; // down-left corner

  std::array<bool, 4> up_right_left = {true, true, false, true}; // up-right-left intersection
  std::array<bool, 4> down_right_left = {false, true, true, true}; // down-right-left intersection
  std::array<bool, 4> up_down_right = {true, true, true, false}; // up-down-right intersection
  std::array<bool, 4> up_down_left = {true, false, true, true}; // up-down-left intersection

  std::array<bool, 4> right_left = {false, true, false, true}; // right-left
  std::array<bool, 4> up_down = {true, false, true, false}; // up-down

  std::array<bool, 4> right_end = {false, false, false, true}; // right-end
  std::array<bool, 4> left_end = {false, true, false, false}; // ledr-end

  std::array<bool, 4> up_end = {false, false, true, false}; // up-end
  std::array<bool, 4> down_end = {true, false, false, false}; // down-end

  // match wall and get the possition of the proper sprite
  if(wall_sides == all_sides){
    tile_pos_x = 3;
    tile_pos_y = 21;
  }else if(wall_sides == down_right_left){
    tile_pos_x = 3;
    tile_pos_y = 21;
  }else if(wall_sides == up_right_left){
    tile_pos_x = 3;
    tile_pos_y = 22;
  }else if(wall_sides == up_down_right){
    tile_pos_x = 3;
    tile_pos_y = 23;
  }else if(wall_sides == up_right){
    tile_pos_x = 1;
    tile_pos_y = 22;
  }else if(wall_sides == up_left){
    tile_pos_x = 2;
    tile_pos_y = 22;
  }else if(wall_sides == down_right){
    tile_pos_x = 1;
    tile_pos_y = 21;
  }else if(wall_sides == down_left){
    tile_pos_x = 2;
    tile_pos_y = 21;
  }else if(wall_sides == up_down_left){
    tile_pos_x = 1;
    tile_pos_y = 23;
  }else if(wall_sides == right_left){
    tile_pos_x = 2;
    tile_pos_y = 20;
  }else if(wall_sides == up_down){
    tile_pos_x = 0;
    tile_pos_y = 22;
  }else if(wall_sides == right_end){
    tile_pos_x = 3;
    tile_pos_y = 20;
  }else if(wall_sides == left_end){
    tile_pos_x = 1;
    tile_pos_y = 20;
  }else if(wall_sides == up_end){
    tile_pos_x = 0;
    tile_pos_y = 21;
  }else if(wall_sides == down_end){
    tile_pos_x = 0;
    tile_pos_y = 23;
  }

  // create wall pixmap
  QGraphicsPixmapItem * pixmap = new QGraphicsPixmapItem();
  pixmap->setPixmap(dungeon_sheet_.copy(tile_pos_x * dungeon_sprite_size_, tile_pos_y * dungeon_sprite_size_, dungeon_sprite_size_, dungeon_sprite_size_));

  return pixmap;
}

/**
 * @brief Window::GetDungeonSprite
 *
 * Given a tile this returns the pixmap with corerct sprite
 *
 * @param tile - the tile you want the pixmap for
 * @return The pixmap of the tile with the proper sprite
 */

QGraphicsPixmapItem* Window::GetDungeonSprite(Tile* tile){
  // show pink square when sprite doesn't load properly
  int tile_pos_x = 15;
  int tile_pos_y = 8;

  // player
  if(tile->get_type() == TileType::Player){
    tile_pos_x = 0;
    tile_pos_y = 0;

    QGraphicsPixmapItem * pixmap = new QGraphicsPixmapItem();
    pixmap->setPixmap(player_sheet_.copy(tile_pos_x * dungeon_sprite_size_, tile_pos_y * dungeon_sprite_size_, dungeon_sprite_size_, dungeon_sprite_size_));
    return pixmap;
  }

  // enemy
  if(tile->get_type() == TileType::Enemy){
    tile_pos_x = 0;
    tile_pos_y = 0;

    QGraphicsPixmapItem * pixmap = new QGraphicsPixmapItem();
    pixmap->setPixmap(slime_sheet_.copy(tile_pos_x * dungeon_sprite_size_, tile_pos_y * dungeon_sprite_size_, dungeon_sprite_size_, dungeon_sprite_size_));
    return pixmap;
  }


  switch (tile->get_type()) {

    case TileType::Empty:
      tile_pos_x = 0;
      tile_pos_y = 4;
      break;
    case TileType::Exit:
      tile_pos_x = 9;
      tile_pos_y = 16;
      break;
    case TileType::Void:
      tile_pos_x = 3;
      tile_pos_y = 0;
      break;
    case TileType::ChestClosed:
      tile_pos_x = 14;
      tile_pos_y = 16;
      break;
    case TileType::ChestOpened:
      tile_pos_x = 15;
      tile_pos_y = 16;
      break;
  }

  // create pixmap
  QGraphicsPixmapItem * pixmap = new QGraphicsPixmapItem();
  pixmap->setPixmap(dungeon_sheet_.copy(tile_pos_x * dungeon_sprite_size_, tile_pos_y * dungeon_sprite_size_, dungeon_sprite_size_, dungeon_sprite_size_));

  return pixmap;
}

/**
 * @brief Window::AddLighting
 *
 * - Adds a lighting affect tot he scene so that you can only see within a distance
 * - Uses breadth first search to find distance from player which is the brightness
 *
 * @param board - The board of tiles
 * @param player - The player tile
 */

void Window::AddLighting(std::vector< std::vector< std::vector<Tile*> > > board, PlayerTile* player){

  // create varibale for playe position
  Position pos = player->get_position();

  // create 2d array for distances
  std::vector< std::vector<int> > distances;

  for(unsigned long i = 0; i < board[0].size(); i++){
    std::vector<int> row(board[0][0].size(), -1);
    distances.push_back( row );
  }

  // setup for bfs
  std::vector< Position > frontier;

  frontier.insert(frontier.begin(), pos);
  distances[pos.y_][pos.x_] = 0;

  Position player_pos;

  // bfs
  while(frontier.size() > 0){
    // get front element
    Position cur_pos = frontier.back();
    frontier.pop_back();

    // the possible places the places the light can go at cur_pos
    std::vector<Position> possible_moves = { Position(cur_pos.x_, cur_pos.y_+1), Position(cur_pos.x_+1, cur_pos.y_), Position(cur_pos.x_, cur_pos.y_-1), Position(cur_pos.x_-1, cur_pos.y_)};

    for(Position next_pos : possible_moves){
      int dist = distances[cur_pos.y_][cur_pos.x_] + 1;

      // if the next place not empty
      if(board[0][cur_pos.y_][cur_pos.x_]->get_type() != TileType::Empty){
        continue;
      }

      // if place unvisited
      if(distances[next_pos.y_][next_pos.x_] == -1){

        // if the distance is within the lighting distance bound add to frontier
        if(dist < lighting_distance_){

          // update distance
          distances[next_pos.y_][next_pos.x_] = dist;
          frontier.insert(frontier.begin(), next_pos);
        }
      }
    }
  }

  // Create lighting squares
  for(int y = 0; y < board[0].size(); y++){
    for(int x = 0; x < board[0][0].size(); x++){
        // adding lighting
        QGraphicsRectItem * pixmap;

        // create black square
        pixmap = new QGraphicsRectItem( QRect(x * dungeon_sprite_size_ * dungeon_tile_scale_, y * dungeon_sprite_size_ * dungeon_tile_scale_, dungeon_sprite_size_ * dungeon_tile_scale_, dungeon_sprite_size_ * dungeon_tile_scale_), 0 );
        pixmap->setBrush(Qt::black);
        pixmap->setPen(Qt::NoPen);
        if(distances[y][x] != -1){
          // change opacity if within lighting distance
          double brightness = (distances[y][x] * 1.0)/lighting_distance_;
          pixmap->setOpacity(brightness);
        }

        scene_->addItem(pixmap);
    }
  }
}

/**
 * Updates the sidebar that shows the player health, magic, and speed - called whenever a battle is finished
 *
 * @param player
 */
void Window::UpdatePlayerStats(Entity &player)
{
  ui->playerHealth->setText("Health: " + QString::number((int)player.GetHealth()) + " / " + QString::number((int)player.GetMaxHealth()));
  ui->playerMagic->setText("Magic: " + QString::number((int)player.GetMagic()) + " / " + QString::number(((int)player.GetMaxMagic())));
}

void Window::UpdateLevel(int level)
{
  ui->currentLevel->setText("Current Level: " + QString::number(level));
}

/**
 * Update the sidebar equipment panel with the player's equipment
 *
 * @param items
 */
void Window::UpdateItems(std::map<EquipType, Item> items)
{
  for(std::pair<EquipType, Item> kv : items){
      QLabel * equipment_icon;

      // Determine which image to update based on the equipment type
      switch (kv.first) {
        case EquipType::Weapon:
          equipment_icon = ui->equipmentImage0;
          break;
        case EquipType::Armor:
          equipment_icon = ui->equipmentImage1;
          break;
        case EquipType::Trinket:
          equipment_icon = ui->equipmentImage2;
          break;
        case EquipType::Special:
          equipment_icon = ui->equipmentImage3;
          break;
        }

      // Set the EPIC tooltip
      equipment_icon->setToolTip(ItemToHTML(kv.second));
      QPixmap image = QPixmap(kv.second.get_icon());
      equipment_icon->setPixmap( image );
    }
}

/**
 * Formats the item modifiers and skill to html for the tooltip
 * @param item
 * @return
 */
QString Window::ItemToHTML(Item item)
{
  // Add the beginning of the html and the title of the item
  QString item_string =
      "<html> \
      <head/> \
      <body align='center'> \
        <b><p style='color:goldenrod; font-size: 24px;'>" + item.get_name() + "</p></b>"
        "<b><p>Item Level: " + QString::number(item.get_level()) + "</p></b>";

  // Add all of the modifiers that the item has
  for(Modifier mod : item.get_modifiers()){
      item_string += "<b><p>" + mod.ToString() + "</p></b>";
    }

  // Add the item descriptioin
  item_string += "<b><p style='color:darkslateblue'>" + item.get_description() + "</p></b>";

  // Display the skill's stats in detail
  if(item.get_has_skill()){
      item_string += "<b><p style='color:darkslateblue; font-size: 20px;'>Skill: " + item.get_skill().get_name() + "</p></b>";
      if(item.get_skill().get_magic_cost() != 0){
        item_string += "<b><p> Cost: " + QString::number(item.get_skill().get_magic_cost()) + " magic</p></b>";
        }
      for(Modifier mod : item.get_skill().get_modifiers()){
          item_string += "<b><p> Skill Effect: " + mod.ToString() + "</p></b>";
        }
    }

  item_string += "</body></html>";

  return item_string;
}

/**
 * Whenever an item is found, this dialogue window will pop to let the player
 * decide if they want the item or not
 *
 * @param item The item to be equipped
 */
void Window::ShowItemDropUI(Item new_item, std::map<EquipType, Item> equipment)
{
  // If consumable, show the single item drop UI
  if(new_item.get_equip_type() == EquipType::Consumable){
      ui->consumableFoundDialogue->setVisible(true);

      // Set the images and tooltip of the newly found item
      ui->newItemImage_2->setToolTip(ItemToHTML(new_item));
      ui->newItemImage_2->setPixmap(QPixmap(new_item.get_icon()));
    }
  else{
      ui->equipmentFoundDialogue->setVisible(true);

      // Set the images and tooltip of the newly found item
      ui->newItemImage->setToolTip(ItemToHTML(new_item));
      ui->newItemImage->setPixmap(QPixmap(new_item.get_icon()));

      // Set the currently equipped item
      ui->currentItemImage->setToolTip(ItemToHTML(equipment.at(new_item.get_equip_type())));
      ui->currentItemImage->setPixmap(QPixmap(equipment.at(new_item.get_equip_type()).get_icon()));
    }
}

void Window::on_save_button_clicked()
{
    emit SaveGameSignal();
}

void Window::on_equipButton_clicked()
{
    ui->equipmentFoundDialogue->setVisible(false);
    emit EquipItemSignal(true);
}

void Window::on_throwAwayButton_clicked()
{
    ui->equipmentFoundDialogue->setVisible(false);
    emit EquipItemSignal(false);
}

/**
 * The second buttons are for the 'consumable' items dialogue where a comparison of equipment doesn't make sense
 */
void Window::on_equipButton_2_clicked()
{
  ui->consumableFoundDialogue->setVisible(false);
  emit EquipItemSignal(true);
}

void Window::on_throwAwayButton_2_clicked()
{
  ui->consumableFoundDialogue->setVisible(false);
  emit EquipItemSignal(false);
}

void Window::on_resumeButton_clicked()
{
  ui->pauseMenu->setVisible(false);
  paused_ = false;
}

void Window::on_quitButton_clicked()
{
  on_resumeButton_clicked();
  ui->equipmentFoundDialogue->setVisible(false);
  ui->consumableFoundDialogue->setVisible(false);
  emit QuitGameSignal();
}

void Window::on_pauseButton_clicked()
{
  ui->pauseMenu->setVisible(true);
  paused_ = true;
}
