#ifndef SKILL_H
#define SKILL_H

#include "iostream"
#include "Modifer.h"
#include <vector>

/**
 * @brief The Skill class
 *
 * Functions as a ability or skill to be applied on an entity
 */
class Skill{
public:
  Skill(std::string skill_name,  std::string skill_description, std::vector<Modifier> modifiers):
    skill_name_(skill_name), skill_description_(skill_description), modifiers_(modifiers){}

  std::vector<Modifier> GetModifiers() { return modifiers_; }

private:
  std::string skill_name_;
  std::string skill_description_;
  std::vector<Modifier> modifiers_;
};

#endif // SKILL_H
