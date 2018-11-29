#ifndef MODIFER_H
#define MODIFER_H

#include <QJsonObject>

/**
 * @brief The ModifierType enum
 *
 * Represents which stat in the entity class to modify
 */
enum class ModifierType{
  Health,
  MaxHealth,
  Magic,
  MaxMagic,
  Strength,
  Speed,
  Damage
};

/**
 * @brief The ModifierApplication enum
 *
 * Whether to apply the modifier as a percentage (stat * amount_)
 * or as an addition (stat + amount_)
 */
enum class ModifierOperation{
  Multiplicative,
  Additive,
};

/**
 * @brief The Modifier class
 *
 * Modifies a stat based on certain requirements
 */
class Modifier{
public:
  Modifier(ModifierType type, ModifierOperation application, float effect):
    type_(type), application_type_(application), amount_(effect){}
  Modifier(QJsonObject data);

  float GetModifiedStat(float stat, float min, float max, bool reverse);
  ModifierType GetType() { return type_; }
  QJsonObject Write();
  QString ToString();

private:
  ModifierType type_;
  ModifierOperation application_type_;
  float amount_;
  QString OperationToString();
};

#endif // MODIFER_H
