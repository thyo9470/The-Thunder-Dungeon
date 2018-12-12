

#ifndef _GAME_H_
#define _GAME_H_

#include <QApplication>
#include <QMediaPlayer>

#include "headers/Entity.h"
#include "headers/Board.h"
#include "BattleSim.h"
#include "FightWindow.h"
#include "Window.h"
#include "WinWindow.h"
#include "MenuWindow.h"
#include "headers/Itemfactory.h"

enum class Difficulty {Easy, Medium, Hard, Extreme};

class Game : public QObject{
  Q_OBJECT
public:
  Game();
  ~Game();

  void Read(const QJsonObject &json);
  void Write(QJsonObject &json) const;

  // Game loop used for input, update, render
  void GameLoop() const;

  // updates game state
  void update();

private:
  Window * window_;
  FightWindow * fight_window_;
  MenuWindow * menu_window_;
  WinWindow * win_window_;
  Board  *board_;
  BattleSim *battle_sim_;
  Difficulty difficulty;
  ItemFactory item_factory_;
  bool playing_;
  Item item_to_equip_;
  Entity *player_;
  QMediaPlayer * fx_player_;

  int end_level = 6;

  void WinGame() const;

public slots:
  void GetInputBoard(QKeyEvent* event);
  void GetInputBattleSim(int skill_id);
  void NewWindows();
  void StartGame();
  void NewGame();
  // For data persistence
  bool LoadGame();
  bool SaveGame() const;
  void StartBattle();
  void EndBattle();
  void EquipItem(bool equip_skill);
  void QuitGame();
  void DropRandomItem();
  void EnemyDropItem();
  void GoToBoard();
  void GameOver();
};


class Start_Menu{

public:
  Start_Menu();

  void Intro();
  void Splash();
  void WaitForStart();

};

#endif // GAME_H 
