#include<iostream>
#include<thread>
#include<chrono>


#include <QApplication>
#include <QKeyEvent>
#include <QPushButton>
#include <QJsonDocument>
#include <QDebug>

#include "../headers/Game.h"
#include "./headers/Board.h"

#include <QTextStream>

Game::Game()
{

  int rooms_wide = 5;
  int rooms_tall = 5;

  window_ = new Window();
  fight_window_ = new FightWindow();

  playing_ = true;

  board_ = new Board(4, rooms_wide, rooms_tall);
  connect(board_, &Board::StartBattle, this, &Game::StartBattle);
  connect(fight_window_, &FightWindow::ButtonClickedSignal, this, &Game::EndBattle);

  window_->show();

  connect(window_, &Window::KeyPressSignal, this, &Game::GetInput);
  connect(window_, &Window::SaveGameSignal, this, &Game::SaveGame);
  connect(window_, &Window::LoadGameSignal, this, &Game::LoadGame);
}

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

      QTextStream(stdout) << "Loaded save using "
                          << (save_format_ != Json ? "binary " : "") << "JSON...\n";
      return true;
}

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
  if (json.contains("board") && json["board"].isObject()){
      board_->Read(json["board"].toObject());
      GameLoop();
  }
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
}

/*
  Recieved the input from the player, and moves the game foward
*/
void Game::GetInput(QKeyEvent* event){
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
 * @brief Game::GameLoop
 *
 * Updating the board
 */

void Game::GameLoop() const{
  window_->UpdateBoard(board_->get_board());
}

/**
 * @brief Game::StartBattle
 */

void Game::StartBattle(){
  qDebug() << "Start Battel";
  window_->hide();
  fight_window_->show();
}

/**
 * @brief Game::StartBattle
 */

void Game::EndBattle(){
  qDebug() << "Start Battel";
  window_->show();
  fight_window_->hide();
}
