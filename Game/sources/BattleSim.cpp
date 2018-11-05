
#include <QApplication>
#include <QJsonDocument>
#include <QDebug>

#include <headers/Entity.h>

#include "../headers/BattleSim.h"

BattleSim::BattleSim(Entity* player){
  player_ = player;

  // make player
  QJsonObject entity_data;
  entity_data["max_health"] = 100;
  entity_data["max_magic"] = 100;
  entity_data["strength"] = 100;
  entity_data["speed"] = 100;

  enemy_ = new Entity(entity_data);
}

BattleSim::~BattleSim(){

}

/*
  Takes the player turn given the skill number used
      1-4: normal skills
      5: run

  @param  (int skill) The skill being used
  */
void BattleSim::PlayerTurn(int skill_id){
  std::vector<Skill> possible_skills= player_->GetSkills();
  if(skill_id == 4){
    UpdateLog("RUN!!");
  }else if(skill_id >= possible_skills.size()){
    UpdateLog("You don't have that skill yet");
  }else{
    Skill cur_skill = possible_skills[skill_id];
    if(cur_skill.GetTarget() == Target::Self){
      UpdateLog("OUCH! You hurt yourself");
      player_->ApplySkill(cur_skill);
    }else{
      UpdateLog("YAY! you hurt the enemy!");
      enemy_->ApplySkill(cur_skill);
    }
  }
  EnemyTurn();
}

void BattleSim::EnemyTurn(){
  if(enemy_->GetHealth() > 0){
    std::vector<Skill> possible_skills= player_->GetSkills();
    player_->ApplySkill(possible_skills[0]);
  }
}

void BattleSim::UpdateLog(std::string new_message){
  if(log_.size() > 4){
    log_.erase(log_.begin());
  }
  log_.push_back(new_message);
}
