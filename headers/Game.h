

#ifndef _GAME_H_
#define _GAME_H_

#include <QApplication>

#include "Board.h"
#include "headers/Window.h"

class Game : public QObject{
  Q_OBJECT
public:
  Game();

  // Creates a new game
  void StartGame();

  // Game loop used for input, update, render
  void GameLoop();

  // updates game state
  void update();

private:
  Window * window_;
  Board  *board_;
  bool playing_;
    //Player *player_;

public slots:
  void GetInput(QKeyEvent* event);

};


class Start_Menu{

public:
  Start_Menu();

  void Intro();
  void Splash();
  void WaitForStart();

};

#endif // GAME_H 
