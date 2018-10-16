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

  window_ = new Graphics(nullptr, ( x_rooms * 6 + 1 ) * 4 * 8, ( y_rooms * 6 + 1 ) * 4 * 8);

  playing_ = true;

  board_ = new Board(2, x_rooms, y_rooms);
  board_->GenerateDungeon();
   
  window_->show();
}

bool Game::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        qDebug("Ate key press %d", keyEvent->key());
        if(keyEvent->key() == Qt::Key_Up){
          qDebug("Up");
          board_->MovePlayer(ActionType::Up);
        }else if(keyEvent->key() == Qt::Key_Right){
          qDebug("Right");
          board_->MovePlayer(ActionType::Right);
        }else if(keyEvent->key() == Qt::Key_Down){
          qDebug("Down");
          board_->MovePlayer(ActionType::Down);
        }else if(keyEvent->key() == Qt::Key_Left){
          qDebug("Left");
          board_->MovePlayer(ActionType::Left);
        }
        window_->UpdateBoard(board_->get_board());
        return true;
    } else {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}

/*
    The game loop is what handles getting user input and updating the board
*/
void Game::GameLoop(){
  window_->UpdateBoard(board_->get_board());

 /*
  while(playing_){
    board_->PrintBoard();

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }*/

}
