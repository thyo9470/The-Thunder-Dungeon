#ifndef ITEM_H
#define ITEM_H

#include "iostream"
#include "Modifier.h"
#include "Skill.h"
#include <QJsonObject>
#include <vector>

enum class EquipType{
  Weapon,
  Armor,
  Trinket,
  Special,
};

class Item
{
public:
  Item();
  Item(QJsonObject item_data);
  Item(int item_level, QString item_name, QString item_description, std::vector<Modifier> modifiers, EquipType equip_type, Skill skill, QString item_icon);
  Item(int item_level, QString item_name, QString item_description, std::vector<Modifier> modifiers, EquipType equip_type, QString item_icon);
  std::vector<Modifier> GetModifiers() { return modifiers_; }
  QString GetName() {return item_name_;}
  QString GetDescription() {return item_description_;}
  EquipType GetEquipType() { return equip_type_; }
  int GetLevel() { return item_level_; }
  Skill GetSkill() { return item_skill_; }
  bool HasSkill() { return has_skill_; }
  QString GetIcon() { return item_icon_; }
  QJsonObject Write();

private:
  QString item_name_;
  QString item_description_;
  std::vector<Modifier> modifiers_;
  int item_level_;
  EquipType equip_type_;
  Skill item_skill_;
  bool has_skill_;
  QString item_icon_;
};

#endif // ITEM_H
