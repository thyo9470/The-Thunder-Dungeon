

#ifndef _GAME_H_
#define _GAME_H_

#include <QApplication>

#include "headers/Entity.h"
#include "headers/Board.h"
#include "BattleSim.h"
#include "FightWindow.h"
#include "Window.h"
#include "headers/Itemfactory.h"

enum class Difficulty {Easy, Medium, Hard, Extreme};

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

  BattleSim *battle_sim_;
  Difficulty difficulty;
  ItemFactory item_factory_;

  bool playing_;
  SaveFormat save_format_ = SaveFormat::Json;
  Entity *player_;

public slots:
  void GetInputBoard(QKeyEvent* event);
  void GetInputBattleSim(int skill_id);
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
