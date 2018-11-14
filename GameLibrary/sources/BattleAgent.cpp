
#include <vector>
#include <iostream>
#include <stdexcept>
#include <cmath>

#include "../headers/BattleAgent.h"

Skill BattleAgent::GetBestMove(Entity* user){

  std::vector<Skill> skills = user->GetSkills();
  std::vector<double> skill_values;

  for(Skill& skill : skills){
    // get the target of the skill
    Target target;

    if(user->IsPlayer()){
        if(skill.GetTarget() == Target::Self){
          target = Target::Player;
        }else{
          target = Target::Enemy;
        }
      }else{
        if(skill.GetTarget() == Target::Self){
          target = Target::Enemy;
        }else{
          target = Target::Player;
        }
      }

    skill_values.push_back( TestMove(skill, target) );
  }

  for(double d : skill_values){
      std::cout << d << "  ";
  }
  std::cout << std::endl;

  int skill_index = (std::min_element( skill_values.begin(), skill_values.end() ) - skill_values.begin());

  return skills[skill_index];
}

/**
 * @brief BattleAgent::TestMove
 *
 * Tests how good using a specific skill is
 *
 * @param skill - the skill you are testing
 * @param target - is the skill directed toward the enemy or player
 * @return - How good using the given skill is (higher is better for player, lower is better for enemy)
 */

double BattleAgent::TestMove(Skill skill, Target target){
  if(target == Target::Self){
    throw std::invalid_argument( "Test move's target cannot be self" );
  }

  Entity* temp_player = new Entity(*player_);
  Entity* temp_enemy = new Entity(*enemy_);

  std::cout << skill.GetName() <<std::endl;

  if(target == Target::Player){
      temp_enemy->UseSkill(skill);
      temp_player->ApplySkill(skill);
    }else{
      temp_enemy->UseSkill(skill);
      temp_enemy->ApplySkill(skill);
    }

  std::cout << player_->GetHealth() << std::endl;

  double state_value = StateValue(temp_player, temp_enemy);
  return state_value;
}


/**
 * @brief BattleSim::StateValue
 *
 * Given the state of a player and enemy what is it's value
 *    - Higher = better for player
 *    - Lower  = better for enemy
 *
 * @param player - The player object
 * @param enemy - The enemy object
 * @return - The state value for the given player and enemy states
 */

double BattleAgent::StateValue(Entity* player, Entity* enemy){


  double player_value = GetWeightedValue(player->GetHealth(), [](double x){return x * 1.5;})
       + player->GetMaxHealth()
       + player->GetMagic()
       + player->GetMaxMagic();

  double enemy_value = enemy->GetHealth()
       + enemy->GetMaxHealth()
       + enemy->GetMagic()
       + enemy->GetMaxMagic();

  double other = 0;
  // if this move will make them miss their turn
  if(enemy->GetMagic() < 0){
    other += 1000;
  }
  // if this move will make a player lose the batte=le
  if(player->GetHealth() <= 0){
    other -= 1000;
  }
  if(enemy->GetHealth() <= 0){
    other += 1000;
  }

  //std::cout << "player: " << player_value;
  //std::cout << "enemy: " << enemy_value;

  return player_value - enemy_value + other;
}

