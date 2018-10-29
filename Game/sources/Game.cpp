#include<iostream>
#include<thread>
#include<chrono>


#include <QApplication>
#include <QKeyEvent>
#include <QPushButton>
#include <QJsonDocument>

#include "../headers/Game.h"
#include "./headers/Board.h"

#include <QTextStream>

Game::Game()
{
  int x_rooms = 5;
  int y_rooms = 5;

  window_ = new Window(nullptr, ( x_rooms * 6 + 1 ) * 4 * 8, ( y_rooms * 6 + 1 ) * 4 * 8);

  playing_ = true;

  board_ = new Board(3, x_rooms, y_rooms);

  window_->show();

  connect(window_, &Window::KeyPressSignal, this, &Game::GetInput);
  connect(window_, &Window::SaveGameSignal, this, &Game::SaveGame);
  connect(window_, &Window::LoadGameSignal, this, &Game::LoadGame);
}

bool Game::LoadGame()
{
  // Have the option to save in two different formats:
  // JSON, or unreadable binary
  QFile loadFile(save_format_ == Json
          ? QStringLiteral("save.json")
          : QStringLiteral("save.dat"));

      if (!loadFile.open(QIODevice::ReadOnly)) {
          qWarning("Couldn't open save file.");
          return false;
      }

      QByteArray saveData = loadFile.readAll();

      QJsonDocument loadDoc(save_format_ == Json
          ? QJsonDocument::fromJson(saveData)
          : QJsonDocument::fromBinaryData(saveData));

      Read(loadDoc.object());

      QTextStream(stdout) << "Loaded save using "
                          << (save_format_ != Json ? "binary " : "") << "JSON...\n";
      return true;
}

bool Game::SaveGame() const
{
  QFile saveFile(save_format_ == Json
         ? QStringLiteral("save.json")
         : QStringLiteral("save.dat"));

     if (!saveFile.open(QIODevice::WriteOnly)) {
         qWarning("Couldn't open save file.");
         return false;
     }

     QJsonObject gameObject;
     Write(gameObject);
     QJsonDocument saveDoc(gameObject);
     saveFile.write(save_format_ == Json
         ? saveDoc.toJson()
         : saveDoc.toBinaryData());

     return true;
}

void Game::Read(const QJsonObject &json)
{
  if (json.contains("board") && json["board"].isObject()){
      board_->Read(json["board"].toObject());
  }
}

void Game::Write(QJsonObject &json) const
{
  QJsonObject boardObject;
  board_->Write(boardObject);
  json["board"] = boardObject;
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

/*
    The game loop is what handles getting user input and updating the board
*/
void Game::GameLoop(){
  window_->UpdateBoard(board_->get_board());
}
