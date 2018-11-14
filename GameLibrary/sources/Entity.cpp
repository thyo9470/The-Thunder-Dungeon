#include "../headers/Entity.h"

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
  if(json.contains("IsPlayer") && json["IsPlayer"].toBool()){
    IsPlayer_ = json["IsPlayer"].toBool();
  }else{
    IsPlayer_ = false;
  }

  std::vector<Modifier> strike_mods;
  int strike_cost = 10;
  Modifier damage_mod(ModifierType::Health, ModifierOperation::Additive, -10);
  strike_mods.push_back(damage_mod);

  std::vector<Modifier> drain_mods;
  int drain_cost = 10;
  Modifier magic_mod(ModifierType::Magic, ModifierOperation::Additive, -10);
  drain_mods.push_back(magic_mod);

  std::vector<Modifier> recover_mods;
  int recover_cost = 0;
  Modifier recover_mod(ModifierType::Magic, ModifierOperation::Additive, 10);
  recover_mods.push_back(recover_mod);

  Skill strike_skill("Strike", "Basic Attack: \n10 damage", strike_mods, strike_cost, Target::Enemy);
  Skill drain_skill("Drain", "Enemy loses \n10 magic", drain_mods, drain_cost, Target::Enemy);
  Skill recover_skill("Recover", "Regain 10 magic", recover_mods, recover_cost, Target::Self);

  skills_.push_back(strike_skill);
  skills_.push_back(drain_skill);
  skills_.push_back(recover_skill);
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
void Entity::Write(QJsonObject &json) const
{
  json["level"] = level_;
  json["max_health"] = max_health_;
  json["max_magic"] = max_magic_;
  json["health"] = health_;
  json["magic"] = magic_;
  json["speed"] = speed_;
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
     case ModifierType::Damage:
      health_ = mod.GetModifiedStat(health_, min_stat_value_, max_health_);
      break;
    }

}
