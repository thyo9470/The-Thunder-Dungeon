
#include <QApplication>
#include <QJsonDocument>

#include "../headers/BattleSim.h"


BattleSim::BattleSim(){
  //enemy_ = CreateEnemy
}

BattleSim::~BattleSim(){

}

/*
  Takes the player turn given the skill number used
      1-4: normal skills
      5: run

  @param  (int skill) The skill being used
  */
void BattleSim::PlayerTurn(int skill){
  //player->useskill(skill)
  EnemyTurn();
}

void BattleSim::EnemyTurn(){

}
