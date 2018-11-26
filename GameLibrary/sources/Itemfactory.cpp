#include "headers/Itemfactory.h"

ItemFactory::ItemFactory()
{
  item_adjectives_ = std::vector<QString>{ "Epic", "Magical", "Mystical", "Royal", "Demonic", "Rare", "Mysterious" };
  weapon_nouns_ = std::vector<QString>{ "Sword", "Axe", "Staff" };
}

/**
 * Generates a weapon
 *
 * @param level
 * @return an Item to be equipped
 */
Item ItemFactory::GenerateWeapon(int level)
{
  QJsonObject item_data;
  QString weapon_type = weapon_nouns_[qrand() % weapon_nouns_.size()];
  item_data["item_name"] = item_adjectives_[qrand() % item_adjectives_.size()] + " " + weapon_type;
  item_data["equip_type"] = static_cast<int>(EquipType::Weapon);

  if(weapon_type == "Sword"){
      item_data["item_icon"] = ":/images/items/sword_" + QString::number(qrand() % sword_resource_count_);
    }
  else if(weapon_type == "Axe"){
      item_data["item_icon"] = ":/images/items/axe_" + QString::number(qrand() % axe_resource_count);
    }
  else if(weapon_type == "Staff"){
      item_data["item_icon"] = ":/images/items/staff_" + QString::number(qrand() % staff_resource_count);
    }

  item_data["item_level"] = level;

  return Item(item_data);
}
