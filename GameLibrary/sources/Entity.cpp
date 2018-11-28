#include "../headers/Entity.h"
#include <QJsonArray>
#include <QDebug>

/**
 * Initialize and entity using a json object to initialize all of its parameters
 * We don't need a read functioin because we can create a new entity from the same json
 * @param json The json object to read data from and initialize the stats
 */
Entity::Entity(QJsonObject json)
{
  if(json.contains("max_health") && json["max_health"].isDouble()){
      max_health_ = json["max_health"].toDouble();
    }
  if(json.contains("max_magic") && json["max_magic"].isDouble()){
      max_magic_ = json["max_magic"].toDouble();
    }
  if(json.contains("health") && json["health"].isDouble()){
      health_ = json["health"].toDouble();
    }
  else{
      health_ = max_health_;
    }
  if(json.contains("magic") && json["magic"].isDouble()){
      magic_ = json["magic"].toDouble();
    }
  else{
      magic_ = max_magic_;
    }
  if(json.contains("speed") && json["speed"].isDouble()){
      speed_ = json["speed"].toDouble();
    }
  if(json.contains("level") && json["level"].toInt()){
      level_ = json["level"].toInt();
    }
  else{
      level_ = 1;
    }
  if(json.contains("sprite_index") && json["sprite_index"].toInt()){
      sprite_index_ = json["sprite_index"].toInt();
   }else{
     sprite_index_ = 4; // default is a set of stairs
   }
  if(json.contains("equipment") && json["equipment"].isArray()){
      QJsonArray equipment = json["equipment"].toArray();
      for(int i = 0; i < equipment.size(); i++){
          EquipItem(Item(equipment[i].toObject()));
        }
    }
}

void Entity::UseSkill(Skill skill){
  magic_ -= skill.GetMagicCost();
}

/**
 * @brief Entity::ApplySkill
 * @param skill The skill to apply to the entity
 */
void Entity::ApplySkill(Skill skill)
{
  for(Modifier mod : skill.GetModifiers()){
      ApplyModifier(mod);
    }
}


/**
 * Saves the atomic attributes of an entity
 * We are not saving the skills because we are going to attempt to use a database to save and load the skills
 * and save a skill using just its id
 *
 * @param json
 */
void Entity::Write(QJsonObject &json)
{
  json["level"] = level_;
  json["max_health"] = max_health_;
  json["max_magic"] = max_magic_;
  json["health"] = health_;
  json["magic"] = magic_;
  json["speed"] = speed_;

  QJsonArray equipment;
  std::map<EquipType, Item>::iterator it;
  for(it = equipment_.begin(); it != equipment_.end(); ++it){
    equipment.append(it->second.Write());
    }

  json["equipment"] = equipment;
}

/**
 * Equips an item to its equip slot, and updates the players stats
 * it removes the previous if there is any
 *
 * @param item
 */
void Entity::EquipItem(Item item)
{
  std::map<EquipType, Item>::iterator it = equipment_.find(item.GetEquipType());

  // If there was an item already equipped
  if(it != equipment_.end()){

      // Remove the equipped item's modifiers
      for(Modifier mod : it->second.GetModifiers()){
          ApplyModifier(mod, true);
        }
      it->second = item;
    }
  else{
      equipment_[item.GetEquipType()] = item;
    }

  // Apply the item's modifiers
  for(Modifier mod : item.GetModifiers()){
      ApplyModifier(mod);
    }

  UpdateSkills();
}

/**
 * @brief Entity::UpdateSkills
 *
 * Remakes the skills_ array from the equipped items
 */
void Entity::UpdateSkills()
{
  skills_.clear();

  std::map<EquipType, Item>::iterator it;

  for(it = equipment_.begin(); it != equipment_.end(); ++it){
      if(it->second.HasSkill()){
          skills_.push_back(it->second.GetSkill());
        }
    }
}

/**
 * @brief Entity::ApplyModifier
 * @param mod The modifier to apply to the entity
 *
 */
void Entity::ApplyModifier(Modifier mod, bool reverse)
{
  switch(mod.GetType()){
    case ModifierType::Health:
      health_ = mod.GetModifiedStat(health_, min_stat_value_, max_health_, reverse);
      break;
    case ModifierType::Magic:
      magic_ = mod.GetModifiedStat(magic_, min_stat_value_, max_magic_, reverse);
      break;
    case ModifierType::Speed:
      speed_ = mod.GetModifiedStat(speed_, min_stat_value_, max_stat_value_, reverse);
      break;
    case ModifierType::Strength:
      strength_ = mod.GetModifiedStat(strength_, min_stat_value_, max_stat_value_, reverse);
      break;
    case ModifierType::MaxHealth:
      max_health_ = mod.GetModifiedStat(max_health_, min_stat_value_, max_stat_value_, reverse);
      if(health_ > max_health_){
          health_ = max_health_;
        }
      break;
    case ModifierType::MaxMagic:
      max_magic_ = mod.GetModifiedStat(max_magic_, min_stat_value_, max_stat_value_, reverse);
      if(magic_ > max_magic_){
          magic_ = max_magic_;
        }
      break;
     case ModifierType::Damage:
      health_ = mod.GetModifiedStat(health_, min_stat_value_, max_health_, reverse);
      break;
    }

}
