#include "./headers/Item.h"

Item::Item(){
  item_name_ = "None";
  item_description_ = "";
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

  if(json.contains("item_level") && json["item_level"].toInt()){
      item_level_ = json["item_level"].toInt();
    }
  else{
      item_level_ = 1;
    }

  if(json.contains("equip_type") && json["equip_type"].toInt()){
      equip_type_ = static_cast<EquipType>(json["equip_type"].toInt());
    }
}
