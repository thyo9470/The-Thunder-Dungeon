#include "./headers/Item.h"
#include <QJsonArray>
#include <QtDebug>

Item::Item(){
  item_name_ = "None";
  item_description_ = "";
  has_skill_ = false;
}

Item::Item(QJsonObject json){
  if(json.contains("item_name") && json["item_name"].isString()){
      item_name_ = json["item_name"].toString().toStdString();
    }
  else{
      item_name_ = "None";
    }

  if(json.contains("item_description") && json["item_description"].isString()){
      item_description_ = json["item_description"].toString().toStdString();
    }

  if(json.contains("item_icon") && json["item_icon"].isString()){
      item_icon_ = json["item_icon"].toString().toStdString();
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

  if(json.contains("modifiers") && json["modifers"].isArray()){
      QJsonArray modifiers = json["modifers"].toArray();
      for(int i = 0; i < modifiers.size(); i++){
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
Item::Item(int item_level, std::string item_name, std::string item_description, std::vector<Modifier> modifiers, EquipType equip_type, Skill skill, std::string item_icon):
  item_level_(item_level), item_name_(item_name), item_description_(item_description), modifiers_(modifiers), equip_type_(equip_type), item_skill_(skill), item_icon_(item_icon)
{
  has_skill_ = true;
}

/**
 * Saves the item in a QJsonObject
 * @return The QJsonObject
 */
QJsonObject Item::Write()
{
  QJsonObject data;
  data["item_name"] = QString::fromStdString(item_name_);
  data["item_description"] = QString::fromStdString(item_description_);
  data["item_icon"] = QString::fromStdString(item_icon_);
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
