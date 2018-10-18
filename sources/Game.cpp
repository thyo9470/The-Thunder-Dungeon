#include<iostream>
#include<thread>
#include<chrono>


#include <QApplication>
#include <QKeyEvent>
#include <QPushButton>

#include "../headers/Game.h"
#include "../headers/Board.h"

#include <QTextStream>

Game::Game(){

  int x_rooms = 5;
  int y_rooms = 5;

  window_ = new Window(nullptr, ( x_rooms * 6 + 1 ) * 4 * 8, ( y_rooms * 6 + 1 ) * 4 * 8);

  playing_ = true;

  board_ = new Board(2, x_rooms, y_rooms);
  board_->GenerateDungeon();
   
  window_->show();

  connect(window_, &Window::KeyPressSignal, this, &Game::GetInput);

}

/*

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
  }
  window_->UpdateBoard(board_->get_board());
}

/*
    The game loop is what handles getting user input and updating the board
*/
void Game::GameLoop(){
  window_->UpdateBoard(board_->get_board());
}
