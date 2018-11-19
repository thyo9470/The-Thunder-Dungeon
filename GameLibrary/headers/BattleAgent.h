#ifndef BATTLEAGENT_H
#define BATTLEAGENT_H

#include <limits>

#include "Skill.h"
#include "Entity.h"

class BattleAgent{

public:
  // makes copy of player and enemy so we don't edit the real versions
  BattleAgent(Entity* player, Entity* enemy):player_(player), enemy_(enemy){}
  Skill GetBestMove();
  void AddSkill(Skill skill);

  //new functions
  Skill GetEnemyMove(int depth);
  Skill GetPlayerMove(int depth);

private:
  static constexpr double inf = std::numeric_limits<double>::infinity();

  Entity* player_;
  Entity* enemy_;
  std::vector<Skill> player_skills;

  double EnemyMove(Entity player, Entity enemy, int depth, double alpha = -inf, double beta = inf);
  double PlayerMove(Entity player, Entity enemy, int depth, double alpha = -inf, double beta = inf);

  void UseEnemyMove(Entity& player, Entity& enemy, Skill& skill);
  void UsePlayerMove(Entity& player, Entity& enemy, Skill& skill);

  double StateValue(Entity& player, Entity& enemy);

  // takes in a value and a function to apply to it for weighting
  double GetWeightedValue(double value, double (*f)(double)) {return ((*f)(value));}
};

#endif // BATTLEAGENT_H
