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
  Consumable
};

class Item
{
public:
  Item();
  Item(QJsonObject item_data);
  Item(int item_level, QString item_name, QString item_description, std::vector<Modifier> modifiers, EquipType equip_type, Skill skill, QString item_icon);
  Item(int item_level, QString item_name, QString item_description, std::vector<Modifier> modifiers, EquipType equip_type, QString item_icon);
  std::vector<Modifier> get_modifiers() { return modifiers_; }
  QString get_name() {return item_name_;}
  QString get_description() {return item_description_;}
  EquipType get_equip_type() { return equip_type_; }
  int get_level() { return item_level_; }
  Skill get_skill() { return item_skill_; }
  bool get_has_skill() { return has_skill_; }
  QString get_icon() { return item_icon_; }
  QJsonObject Write() const;

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
