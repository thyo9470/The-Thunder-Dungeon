#include "../headers/Modifier.h"

/**
 * Initialize a modifier from its appropriate json object
 * @param data
 */
Modifier::Modifier(QJsonObject data)
{
  if(data.contains("type") &&
     data.contains("application_type") &&
     data.contains("amount") && data["amount"].isDouble()){
      Modifier(
          static_cast<ModifierType>(data["type"].toInt()),
          static_cast<ModifierOperation>(data["application_type"].toInt()),
          data["amount"].toDouble()
          );
    }
  else{
      qWarning("Json modifier initialization is missing one or more parameters.");
    }
}

/**
 * @brief Modifier::GetModifiedStat
 * @param stat The base stat to change
 * @param min The minimum the stat can be (keep from going negative for example)
 * @param max The maximum the stat can be
 * @param reverse If true, will do the opposite effect of the modifier
 * @return The modified stat value
 */
float Modifier::GetModifiedStat(float stat, float min, float max, bool reverse){
  float new_stat;
  if(application_type_ == ModifierOperation::Additive){
      new_stat = reverse ? stat - amount_ : stat + amount_;
    }
  else{
      new_stat = reverse? stat / amount_ : stat * amount_;
    }

  // Check Bounds
  if(new_stat > max){
      return max;
    }
  else if(new_stat < min){
      return min;
    }

  return new_stat;
}

/**
 * Saves the modifier in a QJsonObject
 * @return The QJsonObject
 */
QJsonObject Modifier::Write()
{
  QJsonObject data;
  data["type"] = static_cast<int>(type_);
  data["application_type"] = static_cast<int>(application_type_);
  data["amount"] = static_cast<double>(amount_);
  return data;
}
