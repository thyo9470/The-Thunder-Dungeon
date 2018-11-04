#include "../headers/Entity.h"

/**
 * @brief Entity::Entity
 * @param json The json object to read data from and initialize the stats
 */
Entity::Entity(QJsonObject json)
{
  if(json.contains("max_health") && json["max_health"].toInt()){
      max_health_ = json["max_health"].toInt();
      health_ = json["max_health"].toInt();
    }
  if(json.contains("max_magic") && json["max_magic"].toInt()){
      max_magic_ = json["max_magic"].toInt();
      magic_ = json["max_magic"].toInt();
    }
  if(json.contains("strength") && json["strength"].toInt()){
      strength_ = json["strength"].toInt();
    }
  if(json.contains("speed") && json["speed"].toInt()){
      speed_ = json["speed"].toInt();
    }
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
 * @brief Entity::ApplyModifier
 * @param mod The modifier to apply to the entity
 *
 */
void Entity::ApplyModifier(Modifier mod)
{
  switch(mod.GetType()){
    case ModifierType::Health:
      health_ = mod.GetModifiedStat(health_, min_stat_value_, max_health_);
      break;
    case ModifierType::Magic:
      magic_ = mod.GetModifiedStat(magic_, min_stat_value_, max_magic_);
      break;
    case ModifierType::Speed:
      speed_ = mod.GetModifiedStat(speed_, min_stat_value_, max_stat_value_);
      break;
    case ModifierType::Strength:
      strength_ = mod.GetModifiedStat(strength_, min_stat_value_, max_stat_value_);
      break;
    case ModifierType::MaxHealth:
      max_health_ = mod.GetModifiedStat(max_health_, min_stat_value_, max_stat_value_);
      break;
    case ModifierType::MaxMagic:
      max_magic_ = mod.GetModifiedStat(max_magic_, min_stat_value_, max_stat_value_);
      break;
    }

}
