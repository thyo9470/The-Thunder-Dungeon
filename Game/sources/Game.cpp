#include<iostream>
#include<thread>
#include<chrono>
#include <QMediaPlaylist>
#include <QApplication>
#include <QKeyEvent>
#include <QPushButton>
#include <QJsonDocument>

#include "../headers/Game.h"
#include "./headers/Board.h"
#include "headers/Entityfactory.h"

#include <QTextStream>

Game::Game()
{
  menu_window_ = new MenuWindow(); // Represents the starting window
  win_window_ = new WinWindow();

  menu_window_->show();

  QFile loadFile(QStringLiteral("save.dat")); // Check to see if a load save exists
  menu_window_->UpdateWindow(loadFile.open(QIODevice::ReadOnly));

  playing_ = false;

  connect(menu_window_, &MenuWindow::StartGameSignal, this, &Game::NewGame);
  connect(menu_window_, &MenuWindow::LoadGameSignal, this, &Game::LoadGame);

  // Loops the music
  QMediaPlaylist * playlist = new QMediaPlaylist();
  playlist->addMedia(QUrl("qrc:/sounds/Main Theme.mp3"));
  playlist->setPlaybackMode(QMediaPlaylist::Loop);

  // Play the background music
  QMediaPlayer * music = new QMediaPlayer();
  music->setMedia(playlist);
  music->play();

  fx_player_ = new QMediaPlayer();
  
  connect(win_window_, &WinWindow::NewGameSignal, this, &Game::QuitGame);
}

Game::~Game(){
  delete window_;
  delete fight_window_;
  delete menu_window_;
  delete win_window_;
  delete board_;
  delete battle_sim_;
  delete player_;
}

void Game::NewWindows()
{
  window_ = new Window(); // Represents the board window
  fight_window_ = new FightWindow(); // Represents the fight scene window

  connect(window_, &Window::KeyPressSignal, this, &Game::GetInputBoard);
  connect(window_, &Window::SaveGameSignal, this, &Game::SaveGame);
  connect(window_, &Window::EquipItemSignal, this, &Game::EquipItem);
  connect(window_, &Window::QuitGameSignal, this, &Game::QuitGame);

  connect(fight_window_, &FightWindow::ButtonPressedSignal, this, &Game::GetInputBattleSim);
  connect(fight_window_, &FightWindow::GameOverSignal, this, &Game::QuitGame);
  connect(fight_window_, &FightWindow::ToBoardSignal, this, &Game::GoToBoard);
}

/**
 * After initializing a new game, or loading a previous game, this function sets up
 * the rest of the game
 */
void Game::StartGame()
{
  connect(board_, &Board::StartBattle, this, &Game::StartBattle);
  connect(board_, &Board::DropItemSignal, this, &Game::DropRandomItem);

  // Update the window with the player's stats
  window_->UpdatePlayerStats(*player_);
  window_->UpdateItems(player_->GetEquipment());

  // set difficulty
  difficulty = Difficulty::Hard;

  menu_window_->hide();
  window_->show();
  playing_ = true;
  GameLoop();
}

/**
 * Starts a new game by instantiating a new board and player
 */
void Game::NewGame()
{
  NewWindows();
  // setup board
  int rooms_wide = 5;
  int rooms_tall = 5;
  board_ = new Board(4, rooms_wide, rooms_tall);
  player_ = EntityFactory::GeneratePlayer();

  StartGame();
}

/**
 * @brief Game::LoadGame
 *
 * Opens the json read file if it exists, and loads the game with the data
 *
 * @return
 */
bool Game::LoadGame(){
  NewWindows();

  // Have the option to save in two different formats:
  // JSON, or unreadable binary
  QFile loadFile(QStringLiteral("save.dat"));

      if (!loadFile.open(QIODevice::ReadOnly)) {
          qWarning("Couldn't open save file.");
          return false;
      }

      QByteArray save_data = loadFile.readAll();

      QJsonDocument loadDoc(QJsonDocument::fromBinaryData(save_data));

      Read(loadDoc.object());

      // Visually updates after reading
      GameLoop();
      window_->UpdatePlayerStats(*player_);
      window_->UpdateItems(player_->GetEquipment());

      StartGame(); // Start the game after a successful load

      return true;
}

/**
 * @brief Game::SaveGame
 *
 * Saves the game by creating a new file and writing the json object to it
 *
 * @return
 */
bool Game::SaveGame() const{
  QFile saveFile(QStringLiteral("save.dat"));

     if (!saveFile.open(QIODevice::WriteOnly)) {
         qWarning("Couldn't open save file.");
         return false;
     }

     QJsonObject game_object;
     Write(game_object);
     QJsonDocument saveDoc(game_object);
     saveFile.write(saveDoc.toBinaryData());

     return true;
}

/**
 * @brief Game::Read
 *
 * Loads a previous gae save from json object
 *
 * @param json - json objct with game save data
 */

void Game::Read(const QJsonObject &json){
  if (!json.contains("board") || !json["board"].isObject() ||
      !json.contains("player") || !json["player"].isObject()){
      qWarning("Load failed: Game data is either missing or corrupted.");
      return;
  }
  // setup board
  int rooms_wide = 5;
  int rooms_tall = 5;
  board_ = new Board(4, rooms_wide, rooms_tall);
  board_->Read(json["board"].toObject());
  delete player_;
  player_ = new Entity(json["player"].toObject());

  if(json.contains("item_to_equip") && json["item_to_equip"].isObject()){
      item_to_equip_ = Item(json["item_to_equip"].toObject());
      window_->ShowItemDropUI(item_to_equip_, player_->GetEquipment());
    }
}


/**
 * @brief Game::Write
 *
 * Reads all data from a game into a json object
 *
 * @param json - the json object to write to
 */

void Game::Write(QJsonObject &json) const{
  QJsonObject board_object;
  board_->Write(board_object);
  json["board"] = board_object;

  QJsonObject player_object;
  player_->Write(player_object);
  player_object["max_health"] = 100;
  player_object["max_magic"] = 100;
  json["player"] = player_object;

  if(window_->GetStillChoosingItem()){
      json["item_to_equip"] = item_to_equip_.Write();
    }
  else{
      json.remove("item_to_equip");
    }
}

/**
 * @brief Game::GetInputBoard
 *
 * Recieved the input from the player and move the game forward
 *
 * @param event
 */

void Game::GetInputBoard(QKeyEvent* event){
  if(!playing_) return;

  if(event->key() == Qt::Key_W){
    board_->MovePlayer(ActionType::Up);
  }else if(event->key() == Qt::Key_D){
    board_->MovePlayer(ActionType::Right);
  }else if(event->key() == Qt::Key_S){
    board_->MovePlayer(ActionType::Down);
  }else if(event->key() == Qt::Key_A){
    board_->MovePlayer(ActionType::Left);
  }else if(event->key() == Qt::Key_Dollar){
    board_->MovePlayer(ActionType::TEST);
  }
  GameLoop();
}

/**
 * @brief Game::GetInputBattleSim
 *
 * Gets called whenever the input buttons are pressed in the battle sim e.g. when a skill button is pressed
 *
 * @param skill_id
 */
void Game::GetInputBattleSim(int skill_id){
  BattleState battle_state = battle_sim_->GetState();
  if(battle_state == BattleState::Active){
    battle_sim_->PlayerTurn(skill_id);
  }
  fight_window_->UpdateFightWindow(battle_sim_);
}

/**
 * Returns from the battle simulation back to the board
 */
void Game::GoToBoard()
{
  battle_sim_->DeactivateBattle();
  EndBattle();
}

/**
 * Show the game over dialogue
 */
void Game::GameOver()
{
  fight_window_->ShowGameOver("Slime", board_->get_level());
}

/**
 * Generate a new item drop, and show the item drop dialogue
 */
void Game::DropRandomItem()
{
  item_to_equip_ = item_factory_.GenerateItem(board_->get_level());
  window_->ShowItemDropUI(item_to_equip_, player_->GetEquipment());
  playing_ = false;
}

/**
 * Generate a new item drop from the enemy equipment, and show the item drop dialogue
 */
void Game::EnemyDropItem()
{
  std::map<EquipType, Item> item_drops = battle_sim_->GetEnemy()->GetEquipment();
  item_to_equip_ = item_drops[static_cast<EquipType>(qrand() % 4)];
  window_->ShowItemDropUI(item_to_equip_, player_->GetEquipment());
  playing_ = false;
}

/**
 * @brief Game::GameLoop
 *
 * Updating the board
 */
void Game::GameLoop() const{
  window_->UpdateBoard(board_->get_board());
  window_->AddLighting(board_->get_board(), board_->get_player());
  player_->SetLevel(board_->get_level());
  window_->UpdateLevel(board_->get_level());
}

/**
 * @brief Game::WinGame
 *
 * Call this when the player wins the game
 *
 */

void Game::WinGame() const{
  window_->hide();
  fight_window_->hide();
  win_window_->show();
}

/**
 * @brief Game::StartBattle
 */

void Game::StartBattle(){

  // set difficulty of the battle
  int minimax_depth = 0;

  switch (difficulty) {
    case Difficulty::Easy:
      minimax_depth = 3;
      break;
    case Difficulty::Medium:
      minimax_depth = 6;
      break;
    case Difficulty::Hard:
      minimax_depth = 9;
      break;
    case Difficulty::Extreme:
      minimax_depth = 12;
      break;
  }

  battle_sim_ = new BattleSim(player_, fx_player_, minimax_depth);
  battle_sim_->ActivateBattle();
  connect(battle_sim_, &BattleSim::DropItemSignal, this, &Game::EnemyDropItem);
  connect(battle_sim_, &BattleSim::GameOverSignal, this, &Game::GameOver);
  connect(battle_sim_, &BattleSim::AnimateAttackSignal, fight_window_, &FightWindow::AnimateAttack);
  fight_window_->UpdateFightWindow(battle_sim_);
  window_->hide();
  fight_window_->show();
}

/**
 * @brief Game::StartBattle
 */
void Game::EndBattle(){

  // check if the player has won the game
  if(board_->get_level() >= end_level){
    WinGame();
  }else{
    window_->show();
    fight_window_->hide();
    window_->UpdatePlayerStats(*player_);
  }
}

/**
 * Slot that equips an item if the player clicks the "equip" button
 *
 * Or simply resumes the game if the items is tossed away
 *
 * @param equip_item
 */
void Game::EquipItem(bool equip_item)
{
  if(equip_item){
    player_->EquipItem(item_to_equip_);
    window_->UpdatePlayerStats(*player_);
    window_->UpdateItems(player_->GetEquipment());
    }

  playing_ = true;
}

/**
 * Returns the window to the start menu
 */
void Game::QuitGame()
{
  playing_ = false;
  delete window_;
  delete fight_window_;
  win_window_->hide();
  menu_window_->show();

  // Update the menu_window
  QFile loadFile(QStringLiteral("save.dat")); // Check to see if a load save exists
  menu_window_->UpdateWindow(loadFile.open(QIODevice::ReadOnly));
}
