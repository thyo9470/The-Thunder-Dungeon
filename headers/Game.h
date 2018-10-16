

#ifndef _GAME_H_
#define _GAME_H_

#include <QApplication>

#include "Board.h"
#include "headers/graphics.h"
#include "../headers/keypressed.h"

class Game : public QObject{

public:
  Game();

  // Creates a new game
  void StartGame();

  // Game loop used for input, update, render
  void GameLoop();

  // updates game state
  void update();

private:
  Graphics * window_;
  Board  *board_;
  bool playing_;
  KeyPressed* input_handler_;
    //Player *player_;

  // Filters events looking for keyboard input
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
