
#include <vector>
#include <iostream>
#include <cmath>

#include "../headers/BattleAgent.h"

/**
 * @brief BattleAgent::AddSkill
 *
 * Save the moveset of the opponent for better predictions fo what move to use
 *
 * @param new_skill
 */

void BattleAgent::AddSkill(Skill new_skill){
  for(Skill& skill : player_skills){
    if(skill.get_name() == new_skill.get_name()){
      return;
    }
  }
  player_skills.push_back(new_skill);
}

/**
 * @brief BattleAgent::GetEnemyMove
 *
 * Gets the most optimal move for the enemy
 *
 * @param depth - How far ahead should the enemy be able to see.
 *              - A larger depth means a harder to beat monster
 * @return The optimal skill to use
 */

Skill BattleAgent::GetEnemyMove(int depth){

  // get skills enemy can use
  std::vector<Skill> enemy_skills = enemy_->GetSkills();

  // setup minimax search
  std::vector<double> skill_score;

  double beta = inf;

  // get score of each move
  for(Skill& skill : enemy_skills){
    Entity temp_player = Entity(*player_);
    Entity temp_enemy = Entity(*enemy_);

    UseEnemyMove(temp_player, temp_enemy, skill);

    double cur_score = PlayerMove(temp_player, temp_enemy, depth, inf, beta);

    skill_score.push_back(cur_score);

    if(cur_score < beta){
      beta = cur_score;
    }
  }


  for(unsigned long i = 0; i < skill_score.size(); i++){
    std::cout << enemy_skills[i].get_name().toStdString() << "'s Score: " << skill_score[i] << " || ";
  }
  std::cout << std::endl;

  // Get the min skill score
  double min_score = *min_element(std::begin(skill_score), std::end(skill_score));

  // break tie randomly
  std::vector<unsigned long> best_moves_index;

  for(unsigned long i = 0; i < skill_score.size(); i++){
    if(skill_score[i] == min_score){
      best_moves_index.push_back(i);
    }
  }

  unsigned long skill_index = best_moves_index[ qrand() % best_moves_index.size() ];

  return enemy_skills[skill_index];
}

/**
 * @brief BattleAgent::EnemyMove (min node in minimax)
 *
 * Get's the best score the enemy can get at this state (the more negative the better)
 *
 * @param player - The player to test on
 * @param enemy - The enemy to test on
 * @param depth - The current depth in minimax
 * @param alpha - The best state value seen so far for the player
 * @param beta - The best state value seen so far for the enemy
 * @return The best score the enemy can get at the current state
 */

double BattleAgent::EnemyMove(Entity player, Entity enemy, int depth, double alpha, double beta){

  // check terminal state
  if(depth <= 0 || enemy.GetHealth() <= 0 || player.GetHealth() <= 0){
    return StateValue(player, enemy);
  }
  depth--;

  // values for this node of minimax
  std::vector<double> skill_score;

  // get score for each skill the enemy can use
  for(Skill& skill : enemy.GetSkills()){

      // test this skill on the current state
      Entity temp_player = Entity(player);
      Entity temp_enemy = Entity(enemy);

      UseEnemyMove(temp_player, temp_enemy, skill);

      // get score after using the skill
      double new_score = PlayerMove(temp_player, temp_enemy, depth, alpha, beta);

      skill_score.push_back(new_score);

      if(beta > new_score){
        beta = new_score;
      }

      if(alpha >= beta){
        break;
      }

  }

  // return the lowest value that can be obtained at this node
  double min_score = *min_element(std::begin(skill_score), std::end(skill_score));
  return min_score;

}

/**
 * @brief BattleAgent::PlayerMove
 *
 * Get's the best score the player can get at this state (the more posititve the better)
 *
 * @param player - The player to test on
 * @param enemy - The enemy to test on
 * @param depth - The current depth in minimax
 * @param alpha - The best state value seen so far for the player
 * @param beta - The best state value seen so far for the enemy
 * @return The best score the player can get at the current state
 */

double BattleAgent::PlayerMove(Entity player, Entity enemy, int depth, double alpha, double beta){

  // check terminal state
  if(depth <= 0 || player_skills.size() == 0 || player.GetHealth() <= 0 || enemy.GetHealth() <= 0){
    return StateValue(player, enemy);
  }
  depth--;

  // values for this node of minimax
  std::vector<double> skill_score;

  // get score for each skill the enemy can use
  for(Skill& skill : player_skills){

      // test this skill on the current state
      Entity temp_player = Entity(player);
      Entity temp_enemy = Entity(enemy);

      UsePlayerMove(temp_player, temp_enemy, skill);

      // get score after using the skill

      double new_score = EnemyMove(temp_player, temp_enemy, depth, alpha, beta);

      skill_score.push_back(new_score);

      if(alpha < new_score){
        alpha = new_score;
      }

      if(alpha >= beta){
        break;
      }

  }

  // return the largest value that can be obtained at this node
  double max_score = *max_element(std::begin(skill_score), std::end(skill_score));
  return max_score;
}

/**
 * @brief BattleAgent::UseEnemyMove
 *
 * Given the reference to a player, enemy, and skill
 * the skill is applied as if the enemy were using it
 *
 * @param player - The player you want the skill applied to (if applicable)
 * @param enemy - The enemy you want to use the skill and apply it to (if applicable)
 * @param skill - The skill which is being used
 */

void BattleAgent::UseEnemyMove(Entity& player, Entity& enemy, Skill& skill){

  Target target = skill.get_target();

  // apply skill on proper target
  enemy.UseSkill(skill);
  if(target == Target::Self){
    enemy.ApplySkill(skill);
  }else{
    player.ApplySkill(skill);
  }

}

/**
 * @brief BattleAgent::UsePlayerMove
 *
 * Given the reference to a player, enemy, and skill
 * the skill is applied as if the player were using it
 *
 * @param player - The player you want to use the skill apply it to (if applicable)
 * @param enemy - The enemy you want the skill applied to (if applicable)
 * @param skill - The skill which is being used
 */

void BattleAgent::UsePlayerMove(Entity& player, Entity& enemy, Skill& skill){

  Target target = skill.get_target();

  // apply skill on proper target
  player.UseSkill(skill);
  if(target == Target::Self){
    player.ApplySkill(skill);
  }else{
    enemy.ApplySkill(skill);
  }

}

/**
 * @brief BattleAgent::StateValue
 *
 * Gets the current state value.
 *  -  higher score means a better state for the player
 *  -  lower score means a better state for the enemy
 *
 * @param player - A reference to the current player state
 * @param enemy - A referencec to the current enemy state
 * @return The state score
 */

double BattleAgent::StateValue(Entity& player, Entity& enemy){

  // get player's score (+)

  double player_score = player.GetHealthPercent();
                      + player.GetMagicPercent();

  // get enemy's score (-)

  double enemy_score = enemy.GetHealthPercent();
                     + enemy.GetMagicPercent();

  if(enemy.GetMagic() < 0){
    enemy_score -= 100;
  }

  if(enemy.GetHealth() <= 0){
    enemy_score -= 1000;
  }

  if(player.GetHealth() <= 0){
    player_score -= 1000;
  }


  return player_score - enemy_score;
}



