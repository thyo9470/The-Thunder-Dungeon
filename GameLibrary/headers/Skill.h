#ifndef SKILL_H
#define SKILL_H

#include "iostream"
#include "Modifier.h"
#include <vector>
#include <QJsonObject>

/**
 * @brief The Target enum
 *
 * Determines whether to apply a skill on yourself or your enemy
 */
enum class Target {
  Self,
  Enemy
};

/**
 * @brief The Skill class
 *
 * Functions as a ability or skill to be applied on an entity
 */
class Skill{
public:
  Skill(){} // Default constructor because items and skills require default constructors when using maps (in entity)
  Skill(QJsonObject data);
  Skill(QString skill_name,  QString skill_description, std::vector<Modifier> modifiers, int magic_cost, Target target):
    skill_name_(skill_name), skill_description_(skill_description), modifiers_(modifiers), magic_cost_(magic_cost), target_(target){}

  std::vector<Modifier> GetModifiers() { return modifiers_; }
  Target GetTarget() { return target_; }
  QString GetName() {return skill_name_;}
  QString GetDescription() {return skill_description_;}
  int GetMagicCost() {return magic_cost_;}
  QJsonObject Write() const;

private:
  QString skill_name_;
  QString skill_description_;
  std::vector<Modifier> modifiers_;
  int magic_cost_;
  Target target_;
};

#endif // SKILL_H
