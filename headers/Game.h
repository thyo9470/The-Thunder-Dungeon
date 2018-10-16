

#ifndef _GAME_H_
#define _GAME_H_

#include <QApplication>

#include "Board.h"
#include "headers/graphics.h"
#include "../headers/keypressed.h"

class Game : public QObject{

public:
  Game();

  void StartGame();

  void GameLoop();

  void update();

private:
  Graphics * window_;
  Board  *board_;
  bool playing_;
  KeyPressed* input_handler_;
    //Player *player_;

  bool eventFilter(QObject *obj, QEvent *event) override;

};


class Start_Menu{

public:
  Start_Menu();

  void Intro();
  void Splash();
  void WaitForStart();

};

#endif // GAME_H 
