#ifndef BATTLEAGENT_H
#define BATTLEAGENT_H

#include "Skill.h"
#include "Entity.h"

class BattleAgent{

public:
  // makes copy of player and enemy so we don't edit the real versions
  BattleAgent(Entity* player, Entity* enemy):player_(player), enemy_(enemy){}
  Skill GetBestMove(Entity* user);

private:
  Entity* player_;
  Entity* enemy_;

  double TestMove(Skill skill, Target target);
  double StateValue(Entity* player, Entity* enemy);

  // takes in a value and a function to apply to it for weighting
  double GetWeightedValue(double value, double (*f)(double)) {return ((*f)(value));}
};

#endif // BATTLEAGENT_H
