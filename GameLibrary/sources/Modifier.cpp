#include "../headers/Modifier.h"

/**
 * @brief Modifier::GetModifiedStat
 * @param stat The base stat to change
 * @param min The minimum the stat can be (keep from going negative for example)
 * @param max The maximum the stat can be
 * @return The modified stat value
 */
float Modifier::GetModifiedStat(float stat, float min, float max){
  float new_stat;
  if(application_type_ == ModifierOperation::Additive){
      new_stat = stat + amount_;
    }
  else{
      new_stat = stat * amount_;
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
