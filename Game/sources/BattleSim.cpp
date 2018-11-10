
#include <QApplication>
#include <QJsonDocument>
#include <QDebug>

#include <headers/Entity.h>

#include "../headers/BattleSim.h"

BattleSim::BattleSim(Entity* player){
  player_ = player;

  // make enemy
  QJsonObject entity_data;
  int enemy_level =  player->GetLevel() + ( qrand() % 5 - 2 );
  enemy_level = (enemy_level<1)?1:enemy_level;
  entity_data["level"] = enemy_level;
  entity_data["max_health"] = enemy_level * 10;
  entity_data["max_magic"] = enemy_level * 10;
  entity_data["strength"] = 100;
  entity_data["speed"] = 100;
  entity_data["sprite_index"] = 3;

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
  // check if runnings

  std::vector<Skill> possible_skills= player_->GetSkills();
  if(skill_id == 4){
    UpdateLog("Tried running");
    EnemyTurn();
  }else if(skill_id >= possible_skills.size()){
    UpdateLog("You do not have a skill on this slot");
  }else{
    Skill cur_skill = possible_skills[skill_id];
    if(cur_skill.GetTarget() == Target::Self){
      UpdateLog("OUCH! You hurt yourself");
      player_->ApplySkill(cur_skill);
    }else{
      UpdateLog("You used " + cur_skill.GetName());
      enemy_->ApplySkill(cur_skill);
    }
    EnemyTurn();
  }
}

void BattleSim::EnemyTurn(){
  if(enemy_->GetHealth() > 0){
    std::vector<Skill> possible_skills= player_->GetSkills();
    int skill_choice = rand() % possible_skills.size();
    player_->ApplySkill(possible_skills[skill_choice]);
  }
}

void BattleSim::UpdateLog(std::string new_message){
  if(log_.size() > 4){
    log_.erase(log_.begin());
  }
  log_.push_back(new_message);
}
