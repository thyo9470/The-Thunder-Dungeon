#ifndef ENTITY_H
#define ENTITY_H

#include <QJsonObject>
#include <vector>
#include "Skill.h"
#include "Modifier.h"

/**
 * @brief The Entity class
 *
 * Class that holds the stats for either the player or the enemy
 */
class Entity
{
public:
  Entity(QJsonObject entity_stats);
  int GetLevel() {return level_;}
  float GetHealth() { return health_; }
  float GetMaxHealth() {return max_health_; }
  int GetHealthPercent() {return (health_/max_health_) * 100;}
  float GetMagic(){ return magic_; }
  float GetMaxMagic() {return max_magic_; }
  int GetMagicPercent() {return (magic_/max_magic_) * 100; }
  float GetSpeed(){ return speed_; }
  float GetStrength() { return strength_; }
  std::vector<Skill> GetSkills() { return skills_; }
  int get_sprite_index() {return sprite_index_;}
  void ApplySkill(Skill skill);
  void SetLevel(int level) {level_ = level;}

  void Write(QJsonObject &json) const;

private:
  int level_;
  float max_health_;
  float max_magic_;
  float health_;
  float magic_;
  float strength_;
  float speed_;
  float max_stat_value_ = 1000; // The maximum number a stat can be
  float min_stat_value_ = 0;
  std::vector <Skill> skills_;
  void ApplyModifier(Modifier mod);
  int sprite_index_;

};

#endif // ENTITY_H
