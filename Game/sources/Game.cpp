#include<iostream>
#include<thread>
#include<chrono>


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

  player_ = EntityFactory::GeneratePlayer();

  // setup ui

  int rooms_wide = 5;
  int rooms_tall = 5;

  // set difficulty
  difficulty = Difficulty::Hard;

  window_ = new Window(); // Represents the board window
  fight_window_ = new FightWindow(); // Represents the fight scene window

  // Update the window to show the player stats
  window_->UpdatePlayerStats(*player_);
  window_->UpdateItems(player_->GetEquipment());

  playing_ = true;

  // setup board

  board_ = new Board(4, rooms_wide, rooms_tall);
  connect(board_, &Board::StartBattle, this, &Game::StartBattle);

  window_->show();

  connect(window_, &Window::KeyPressSignal, this, &Game::GetInputBoard);
  connect(window_, &Window::SaveGameSignal, this, &Game::SaveGame);
  connect(window_, &Window::LoadGameSignal, this, &Game::LoadGame);
  connect(window_, &Window::EquipItemSignal, this, &Game::EquipItem);

  connect(fight_window_, &FightWindow::ButtonPressedSignal, this, &Game::GetInputBattleSim);

}

/**
 * @brief Game::LoadGame
 *
 * Opens the json read file if it exists, and loads the game with the data
 *
 * @return
 */
bool Game::LoadGame(){
  // Have the option to save in two different formats:
  // JSON, or unreadable binary
  QFile loadFile(save_format_ == Json
          ? QStringLiteral("save.json")
          : QStringLiteral("save.dat"));

      if (!loadFile.open(QIODevice::ReadOnly)) {
          qWarning("Couldn't open save file.");
          return false;
      }

      QByteArray save_data = loadFile.readAll();

      QJsonDocument loadDoc(save_format_ == Json
          ? QJsonDocument::fromJson(save_data)
          : QJsonDocument::fromBinaryData(save_data));

      Read(loadDoc.object());

      // Visually updates after reading
      GameLoop();
      window_->UpdatePlayerStats(*player_);
      window_->UpdateItems(player_->GetEquipment());

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
  QFile saveFile(save_format_ == Json
         ? QStringLiteral("save.json")
         : QStringLiteral("save.dat"));

     if (!saveFile.open(QIODevice::WriteOnly)) {
         qWarning("Couldn't open save file.");
         return false;
     }

     QJsonObject game_object;
     Write(game_object);
     QJsonDocument saveDoc(game_object);
     saveFile.write(save_format_ == Json
         ? saveDoc.toJson()
         : saveDoc.toBinaryData());

     return true;
}

/*
 * Loads a previous game save from a json object
 *
 * @param &json The Json Object with the game save data
 * */
void Game::Read(const QJsonObject &json){
  if (!json.contains("board") || !json["board"].isObject() ||
      !json.contains("player") || !json["player"].isObject()){
      qWarning("Load failed: Game data is either missing or corrupted.");
      return;
  }
  board_->Read(json["board"].toObject());
  delete player_;
  player_ = new Entity(json["player"].toObject());
}

/*
 * Reads all data from a game into a json object
 *
 * @param &json The Json Object to write to
 * */
void Game::Write(QJsonObject &json) const{
  QJsonObject board_object;
  board_->Write(board_object);
  json["board"] = board_object;

  QJsonObject player_object;
  player_->Write(player_object);
  json["player"] = player_object;
}

/*
  Recieved the input from the player, and moves the game foward
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
  }else if(battle_state == BattleState::End){
     battle_sim_->DeactivateBattle();
     EndBattle();
  }
  fight_window_->UpdateFightWindow(battle_sim_);
}

/**
 * @brief Game::GameLoop
 *
 * Updating the board
 */
void Game::GameLoop() const{
  window_->UpdateBoard(board_->get_board());
  window_->AddLighting(board_->get_board(), board_->GetPlayer());
  player_->SetLevel(board_->GetLevel());
  window_->UpdateLevel(board_->GetLevel());
}

/**
 * @brief Game::StartBattle
 */

void Game::StartBattle(){

  // set difficulty of the battle
  int minimax_depth = 0;

  switch (difficulty) {
    case Difficulty::Easy:
      std::cout << "Easy" << std::endl;
      minimax_depth = 3;
      break;
    case Difficulty::Medium:
      std::cout << "Medium" << std::endl;
      minimax_depth = 6;
      break;
    case Difficulty::Hard:
      std::cout << "Hard" << std::endl;
      minimax_depth = 9;
      break;
    case Difficulty::Extreme:
      std::cout << "Extremes" << std::endl;
      minimax_depth = 12;
      break;
  }

  battle_sim_ = new BattleSim(player_, minimax_depth);
  battle_sim_->ActivateBattle();
  fight_window_->UpdateFightWindow(battle_sim_);
  window_->hide();
  fight_window_->show();
}

/**
 * @brief Game::StartBattle
 */
void Game::EndBattle(){
  window_->show();
  fight_window_->hide();
  window_->UpdatePlayerStats(*player_);

  item_to_equip_ = item_factory_.GenerateItem(board_->GetLevel());
  window_->EnableItemDropUI(item_to_equip_, player_->GetEquipment());
  playing_ = false;
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
