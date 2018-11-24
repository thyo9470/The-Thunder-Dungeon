#include "./headers/Player.h"

Player::Player(QJsonObject entity_stats):
  Entity(entity_stats)
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

  std::vector<Modifier> item_mods; // No mods

  Item start_weapon(1, "Short Sword", "Unlocks skill: " + strike_skill.GetName(), item_mods, EquipType::Weapon, strike_skill, "sword_1.png");
  Item start_armor(1, "Magic Armor", "Unlock skill: " + recover_skill.GetName(), item_mods, EquipType::Armor, recover_skill, "armor_1.png");
  Item start_amulet(1, "Vampiric Amulet", "Unlock skill: " + drain_skill.GetName(), item_mods, EquipType::Trinket, drain_skill, "trinket_1.png");

  EquipItem(start_weapon);
  EquipItem(start_armor);
  EquipItem(start_amulet);
}
