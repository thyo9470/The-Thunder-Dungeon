

#ifndef _GAME_H_
#define _GAME_H_

class Game{

  Game();

  void StartGame();

  private:
    Board  *board_;
    Player *player_;

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
