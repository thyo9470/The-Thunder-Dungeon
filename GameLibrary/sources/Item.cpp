#include "./headers/Item.h"
#include <QJsonArray>

Item::Item(){
  item_name_ = "None";
  item_description_ = "";
  has_skill_ = false;
}

Item::Item(QJsonObject json){
  if(json.contains("item_name") && json["item_name"].isString()){
      item_name_ = json["item_name"].toString();
    }
  else{
      item_name_ = "None";
    }

  if(json.contains("item_description") && json["item_description"].isString()){
      item_description_ = json["item_description"].toString();
    }

  if(json.contains("item_icon") && json["item_icon"].isString()){
      item_icon_ = json["item_icon"].toString();
    }
  else{
      item_icon_ = "Slime.png"; // The default texture
    }

  if(json.contains("item_level")){
      item_level_ = json["item_level"].toInt();
    }
  else{
      item_level_ = 1;
    }

  if(json.contains("equip_type")){
      equip_type_ = static_cast<EquipType>(json["equip_type"].toInt());
    }
  else{
      qWarning("Json item initialization contains no equip_type parameter.");
    }

  if(json.contains("modifiers") && json["modifiers"].isArray()){
      QJsonArray modifiers = json["modifiers"].toArray();
      for(int i = 0; i < modifiers.size(); i++){
          if(!modifiers[i].isObject()){
              qWarning("Modifier is not an object");
            }
          modifiers_.push_back(Modifier(modifiers[i].toObject()));
        }
    }

  if(json.contains("skill") && json["skill"].isObject()){
      item_skill_ = Skill(json["skill"].toObject());
      has_skill_ = true;
    }
  else{
      has_skill_ = false;
    }
}

/**
 * The Lazy initialization of the item: ideally the item factory will prodecdurally generate items
 * @param item_level
 * @param item_name
 * @param item_description
 * @param modifiers
 * @param equip_type
 * @param skill
 * @param item_icon
 */
Item::Item(int item_level, QString item_name, QString item_description, std::vector<Modifier> modifiers, EquipType equip_type, Skill skill, QString item_icon):
  item_level_(item_level), item_name_(item_name), item_description_(item_description), modifiers_(modifiers), equip_type_(equip_type), item_skill_(skill), item_icon_(item_icon)
{
  has_skill_ = true;
}

/**
 * Constructs and item without a skill
 * @param item_level
 * @param item_name
 * @param item_description
 * @param modifiers
 * @param equip_type
 * @param item_icon
 */
Item::Item(int item_level, QString item_name, QString item_description, std::vector<Modifier> modifiers, EquipType equip_type, QString item_icon):
item_level_(item_level), item_name_(item_name), item_description_(item_description), modifiers_(modifiers), equip_type_(equip_type), item_icon_(item_icon)
{
  has_skill_ = false;
}

/**
 * Saves the item in a QJsonObject
 * @return The QJsonObject
 */
QJsonObject Item::Write()
{
  QJsonObject data;
  data["item_name"] = item_name_;
  data["item_description"] = item_description_;
  data["item_icon"] = item_icon_;
  data["item_level"] = item_level_;
  data["equip_type"] = static_cast<int>(equip_type_);
  QJsonArray modifers;
  for(Modifier mod : modifiers_){
      modifers.append(mod.Write());
    }
  data["modifiers"] = modifers;
  if(has_skill_){
    data["skill"] = item_skill_.Write();
    }
  return data;
}
