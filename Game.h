

#ifndef _GAME_H_
#define _GAME_H_

#include "Board.h"

class Game{

public:
  Game();

  void StartGame();

  void GameLoop();

private:
  Board  *board_;
  bool playing_;
    //Player *player_;

  void InputHandler();

  void InstantiateBoard();
  void InstantiatePlayer();  

};


class Start_Menu{

public:
  Start_Menu();

  void Intro();
  void Splash();
  void WaitForStart();

};

#endif // GAME_H 
