#ifndef SKILL_H
#define SKILL_H

#include "iostream"
#include "Modifier.h"
#include <vector>

/**
 * @brief The Target enum
 *
 * Determines whether to apply a skill on yourself or your enemy
 */
enum class Target {
  Self,
  Enemy,
  Player
};

/**
 * @brief The Skill class
 *
 * Functions as a ability or skill to be applied on an entity
 */
class Skill{
public:
  Skill(std::string skill_name,  std::string skill_description, std::vector<Modifier> modifiers, int magic_cost, Target target):
    skill_name_(skill_name), skill_description_(skill_description), modifiers_(modifiers), magic_cost_(magic_cost), target_(target){}

  std::vector<Modifier> GetModifiers() { return modifiers_; }
  Target GetTarget() { return target_; }
  std::string GetName() {return skill_name_;}
  std::string GetDescription() {return skill_description_;}
  int GetMagicCost() {return magic_cost_;}

private:
  std::string skill_name_;
  std::string skill_description_;
  std::vector<Modifier> modifiers_;
  int magic_cost_;
  Target target_;
};

#endif // SKILL_H
