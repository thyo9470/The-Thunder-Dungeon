
#include <QApplication>
#include <QJsonDocument>
#include <QDebug>

#include <headers/Entity.h>

#include "../headers/BattleSim.h"
#include "headers/BattleAgent.h"

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
    if(player_->GetMagic() < cur_skill.GetMagicCost()){
      UpdateLog("You do not have enough magic!");
      return;
    }
    if(cur_skill.GetTarget() == Target::Self){
      player_->ApplySkill(cur_skill);
    }else{
      enemy_->ApplySkill(cur_skill);
    }
    UpdateLog("You used " + cur_skill.GetName());
    player_->UseSkill(cur_skill);
    EnemyTurn();
  }
}

/**
 * @brief BattleSim::EnemyTurn
 *
 * Takes the enemies turn in battle sim
 */
void BattleSim::EnemyTurn(){
  if(enemy_->GetHealth() > 0){
    std::vector<Skill> possible_skills= player_->GetSkills();
    std::vector<double> skill_values = std::vector<double>();

    BattleAgent enemy_agent(player_, enemy_);

    Skill cur_skill = enemy_agent.GetBestMove(enemy_);

    if(enemy_->GetMagic() >= cur_skill.GetMagicCost()){

        if(cur_skill.GetTarget() == Target::Self){
          enemy_->ApplySkill(cur_skill);
          enemy_->UseSkill(cur_skill);
        }else{
          player_->ApplySkill(cur_skill);
          enemy_->UseSkill(cur_skill);
        }
        UpdateLog("The enemy used " + cur_skill.GetName());
      }else{
        UpdateLog("The enemy tried but didn't have enough magic");
      }



  }
  IsBattleOver();
}

/**
 * @brief BattleSim::IsBattleOver
 *
 * Updates the state of the battle if it is the end
 *
 */

void BattleSim::IsBattleOver(){
  if(player_->GetHealth() == 0){
    UpdateLog("You Lost!!");
    state_ = BattleState::End;
  }else if(enemy_->GetHealth() == 0){
    UpdateLog("You Win!!");
    state_ = BattleState::End;
  }
}

/**
 * @brief BattleSim::UpdateLog
 *
 * Adds a message to the battle sim log found to the right of the player's actions
 *
 * @param new_message - message you want displayed in battle log
 */

void BattleSim::UpdateLog(std::string new_message){
  if(log_.size() > 4){
    log_.erase(log_.begin());
  }
  log_.push_back(new_message);
}
