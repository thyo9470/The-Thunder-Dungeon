#include<iostream>
#include<thread>
#include<chrono>

#include "../headers/Game.h"
#include "../headers/Board.h"

Game::Game(){
  
  playing_ = true;
  
  std::string test;

  board_ = new Board(2, 16, 8);
  board_->GenerateDungeon();
   
}

// use threadding for coninuous user input
void Game::InputHandler(){
  while(playing_){
	  std::string input;
	  std::cin>>input;
	  if(input == "up"){
	    board_->MovePlayer(ActionType::Up);
	  }
	  if(input == "right"){
	    board_->MovePlayer(ActionType::Right);
	  }
	  if(input == "down"){
	    board_->MovePlayer(ActionType::Down);
	  }
	  if(input == "left"){
	    board_->MovePlayer(ActionType::Left);
	  }

  }
}

/*
    The game loop is what handles getting user input and updating the board
*/
void Game::GameLoop(){
  std::thread ih_thread(&Game::InputHandler, this); 
 
  while(playing_){
    board_->PrintBoard();

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

}
