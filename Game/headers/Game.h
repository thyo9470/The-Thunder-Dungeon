

#ifndef _GAME_H_
#define _GAME_H_

#include <QApplication>

#include "./headers/Board.h"
#include "FightWindow.h"
#include "Window.h"

class Game : public QObject{
  Q_OBJECT
public:
  // Choose which format to save our data in
  enum SaveFormat {
      Json, Binary
  };

  Game();

  void Read(const QJsonObject &json);
  void Write(QJsonObject &json) const;

  // Game loop used for input, update, render
  void GameLoop() const;

  // updates game state
  void update();

private:
  Window * window_;
  FightWindow * fight_window_;
  Board  *board_;
  bool playing_;
  SaveFormat save_format_ = SaveFormat::Binary;
    //Player *player_;

public slots:
  void GetInput(QKeyEvent* event);
  // For data persistence
  bool LoadGame();
  bool SaveGame() const;
  void StartBattle();
  void EndBattle();

};


class Start_Menu{

public:
  Start_Menu();

  void Intro();
  void Splash();
  void WaitForStart();

};

#endif // GAME_H 
