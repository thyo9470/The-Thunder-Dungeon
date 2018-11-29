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
  int strike_cost = 10;
  Modifier damage_mod(ModifierType::Health, ModifierOperation::Additive, -10);
  strike_mods.push_back(damage_mod);

  std::vector<Modifier> drain_mods;
  int drain_cost = -5;
  Modifier magic_mod(ModifierType::Magic, ModifierOperation::Additive, -10);
  drain_mods.push_back(magic_mod);

  std::vector<Modifier> recover_mods;
  int recover_cost = 0;
  Modifier recover_mod(ModifierType::Magic, ModifierOperation::Additive, 20);
  recover_mods.push_back(recover_mod);

  Skill strike_skill("Strike", "Basic Attack: \n10 damage", strike_mods, strike_cost, Target::Enemy);
  Skill drain_skill("Drain", "Enemy loses \n10 magic", drain_mods, drain_cost, Target::Enemy);
  Skill recover_skill("Recover", "Regain 10 magic", recover_mods, recover_cost, Target::Self);

  std::vector<Modifier> no_mods;
  std::vector<Modifier> add_magic;
  Modifier max_magic_mod(ModifierType::MaxMagic, ModifierOperation::Additive, 10);
  add_magic.push_back(max_magic_mod);

  Item start_weapon(1, "Short Sword", "A light short sword.", no_mods, EquipType::Weapon, strike_skill, ":/images/items/sword_1.png");
  Item start_special(1, "Mage's Tome", "A book of power", add_magic, EquipType::Special, recover_skill, ":/images/items/book_0.png");
  Item start_amulet(1, "Vampiric Amulet", "An amulet that drinks blood.", no_mods, EquipType::Trinket, drain_skill, ":/images/items/trinket_1.png");
  Item start_armor(1, "Headband", "An absolutely useless headband.", no_mods, EquipType::Armor, ":/images/items/headband_0.png");

  entity.EquipItem(start_weapon);
  entity.EquipItem(start_special);
  entity.EquipItem(start_amulet);
  entity.EquipItem(start_armor);
}
