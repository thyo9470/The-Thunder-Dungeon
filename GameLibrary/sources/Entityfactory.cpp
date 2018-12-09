#include "headers/Entityfactory.h"
#include <cmath>
/**
 * Generates an enemy based on level
 * @param level
 * @return The enemy reference
 */
Entity * EntityFactory::GenerateEnemy(int level)
{
  // make enemy
  QJsonObject entity_data;
  int enemy_level =  level + ( qrand() % 5 - 2 );
  //int enemy_level = 10;
  enemy_level = (enemy_level<1)?1:enemy_level;
  entity_data["level"] = enemy_level;
  entity_data["max_health"] = floor(log(enemy_level+1)/log(1.017)); // FIX FLOATING NUMBERS
  entity_data["max_magic"] = floor(log(enemy_level+1)/log(1.017)); // FIX FLOATING NUMBERS
  entity_data["strength"] = 100;
  entity_data["speed"] = 100;
  entity_data["sprite_index"] = 3;

  Entity * enemy = new Entity(entity_data);

  EquipDefaultItems(*enemy);

  return enemy;
}

/**
 * Generates an enemy based on level with equipment based on the level
 * @param level
 * @return The enemy reference
 */
Entity *EntityFactory::GenerateEnemyWithEquipment(int level)
{
  Entity * enemy = GenerateEnemy(level);
  int equipment_attempts = 4;
  for(int i = 0; i < equipment_attempts; i++){
      enemy->EquipItem(item_factory_.GenerateItem(level));
    }
  return enemy;
}

/**
 * Generates a player with the default stats
 * @return The player reference
 */
Entity *EntityFactory::GeneratePlayer()
{
  // make player
  QJsonObject entity_data;
  entity_data["max_health"] = 100;
  entity_data["max_magic"] = 100;
  entity_data["strength"] = 100;
  entity_data["speed"] = 100;
  entity_data["sprite_index"] = 2;

  Entity * player = new Entity(entity_data);

  EquipDefaultItems(*player);

  return player;
}

/**
 * Equips the default items to an entity
 * @param entity
 */
void EntityFactory::EquipDefaultItems(Entity &entity)
{
  std::vector<Modifier> strike_mods;
  int strike_cost = 7;
  Modifier damage_mod(ModifierType::Health, ModifierOperation::Additive, -10);
  strike_mods.push_back(damage_mod);

  std::vector<Modifier> guard_mods;
  int recover_cost = 0;
  Modifier recover_mod(ModifierType::Magic, ModifierOperation::Additive, 10);
  Modifier health_mod(ModifierType::Health, ModifierOperation::Additive, 3);
  guard_mods.push_back(recover_mod);
  guard_mods.push_back(health_mod);

  Skill strike_skill("Strike", "Basic Attack: \n10 damage", strike_mods, strike_cost, Target::Enemy);
  Skill guard_skill("Guard", "Regain 10 magic and 3 health", guard_mods, recover_cost, Target::Self);

  std::vector<Modifier> no_mods;
  std::vector<Modifier> armor_mod;
  armor_mod.push_back(Modifier(ModifierType::MaxHealth, ModifierOperation::Additive, 10));

  std::vector<Modifier> ring_mod;
  ring_mod.push_back(Modifier(ModifierType::MaxMagic, ModifierOperation::Additive, 10));

  Item start_weapon(1, "Short Sword", "A light short sword.", no_mods, EquipType::Weapon, strike_skill, ":/images/items/Weapon_06.png");
  Item start_special(1, "Buckler", "A light, small shield.", no_mods, EquipType::Special, guard_skill, ":/images/items/Shield_01.png");
  Item start_amulet(1, "Metal Ring", "A slightly magical ring.", ring_mod, EquipType::Trinket, ":/images/items/Accessory_01.png");
  Item start_armor(1, "Beginner's Armor", "Provides some protection.", armor_mod, EquipType::Armor, ":/images/items/Armor_03.png");

  entity.EquipItem(start_weapon);
  entity.EquipItem(start_special);
  entity.EquipItem(start_amulet);
  entity.EquipItem(start_armor);
}
