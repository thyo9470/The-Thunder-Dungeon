
#include <QApplication>
#include <QJsonDocument>
#include <cmath>
#include <headers/Entity.h>

#include "../headers/BattleSim.h"
#include "headers/Item.h"
#include "headers/Entityfactory.h"
#include "headers/Itemfactory.h"

BattleSim::BattleSim(Entity* player, int minimax_depth){
  minimax_depth_ = minimax_depth;

  player_ = player;

  EntityFactory entity_factory;
  enemy_ = entity_factory.GenerateEnemyWithEquipment(player->GetLevel());

  agent_ = new BattleAgent(player_, enemy_);

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
    int flip =  rand() % 2 + 1;
    if(flip == 1){
      EndBattle();
      UpdateLog("You got away!");
    }else{
      UpdateLog("Tried running");
      EnemyTurn();
    }
  }else if(skill_id >= possible_skills.size()){
    UpdateLog("You do not have a skill on this slot");
  }else{
    Skill cur_skill = possible_skills[skill_id];
    if(player_->GetMagic() < cur_skill.get_magic_cost()){
      UpdateLog("You do not have enough magic!");
      return;
    }
    if(cur_skill.get_target() == Target::Self){
      player_->ApplySkill(cur_skill);
    }else{
      enemy_->ApplySkill(cur_skill);
    }
    UpdateLog("You used " + cur_skill.get_name().toStdString());
    player_->UseSkill(cur_skill);
    agent_->AddSkill(cur_skill);
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

    Skill cur_skill = agent_->GetEnemyMove(minimax_depth_);

    if(enemy_->GetMagic() >= cur_skill.get_magic_cost()){

        if(cur_skill.get_target() == Target::Self){
          enemy_->ApplySkill(cur_skill);
          enemy_->UseSkill(cur_skill);
        }else{
          player_->ApplySkill(cur_skill);
          enemy_->UseSkill(cur_skill);
        }
        UpdateLog("The enemy used " + cur_skill.get_name().toStdString());
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
    emit GameOverSignal();
    state_ = BattleState::End;
  }else if(enemy_->GetHealth() == 0){
    UpdateLog("You Win!!");
    emit DropItemSignal();
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
