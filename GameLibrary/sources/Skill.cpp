#include "headers/Skill.h"
#include <QJsonArray>

Skill::Skill(QJsonObject data){
  if(data.contains("skill_name") && data["skill_name"].isString()){
      skill_name_ = data["skill_name"].toString().toStdString();
    }
  else{
      qWarning("Json skill initialization contains no skill_name parameter.");
    }

  if(data.contains("skill_description") && data["skill_description"].isString()){
      skill_description_ = data["skill_description"].toString().toStdString();
    }
  else{
      qWarning("Json skill initialization contains no description parameter.");
    }

  if(data.contains("modifiers") && data["modifiers"].isArray()){
      QJsonArray modifiers = data["modifiers"].toArray();
      for(int i = 0; i < modifiers.size(); i++){
          modifiers_.push_back(Modifier(modifiers[i].toObject()));
        }
    }
  else{
      qWarning("Json skill initialization contains no modifiers parameter.");
    }

  if(data.contains("target")){
      target_ = static_cast<Target>(data["target"].toInt());
    }
  else{
      qWarning("Json skill initialization contains no target parameter.");
    }

  if(data.contains("magic_cost")){
      magic_cost_ = data["magic_cost"].toInt();
    }
  else{
      qWarning("Json skill initialization contains no magic_cost parameter.");
    }
}

QJsonObject Skill::Write()
{
  QJsonObject data;
  data["skill_name"] = QString::fromStdString(skill_name_);
  data["skill_description"] = QString::fromStdString(skill_description_);
  QJsonArray modifers;
  for(Modifier mod : modifiers_){
      modifers.append(mod.Write());
    }

  data["modifiers"] = modifers;
  data["target"] = static_cast<int>(target_);
  data["magic_cost"] = magic_cost_;
  return data;
}
