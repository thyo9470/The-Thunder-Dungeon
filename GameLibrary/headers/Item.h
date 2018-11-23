#ifndef ITEM_H
#define ITEM_H

#include "iostream"
#include "Modifier.h"
#include "Skill.h"
#include <vector>

enum class EquipType{
  Weapon,
  Shield,
  Armor,
  Helmet
};

class Item
{
public:
  Item();
  Item(int item_level, std::string item_name, std::string item_description, std::vector<Modifier> modifiers, EquipType equip_type, Skill skill):
    item_level_(item_level), item_name_(item_name), item_description_(item_description), modifiers_(modifiers), equip_type_(equip_type), item_skill_(skill){}

  std::vector<Modifier> GetModifiers() { return modifiers_; }
  std::string GetName() {return item_name_;}
  std::string GetDescription() {return item_description_;}
  EquipType GetEquipType() { return equip_type_; }
  int GetLevel() { return item_level_; }
  Skill GetSkill() { return item_skill_; }

private:
  std::string item_name_;
  std::string item_description_;
  std::vector<Modifier> modifiers_;
  int item_level_;
  EquipType equip_type_;
  Skill item_skill_;
};

#endif // ITEM_H
