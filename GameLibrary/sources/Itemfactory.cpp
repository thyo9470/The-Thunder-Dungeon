#include "headers/Itemfactory.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <vector>
#include <QtMath>

ItemFactory::ItemFactory()
{
  InitializeItemDatabase();
  InitializeAffixes();
}

/**
 * Generates a weapon
 *
 * @param level
 * @return an Item to be equipped
 */
Item ItemFactory::GenerateItem(int level)
{
  // Choose a random item based on level
  QJsonObject item_data = items_by_level_.at(level).at(qrand() % items_by_level_.at(level).size());

  // Generate item prefixes
  if((qrand() % 100)/100.0 < prefix_chance_){
      QJsonObject prefix = item_prefixes_[qrand() % item_prefixes_.size()];

      ApplyAffixToItem(prefix["modifiers"].toArray(), item_data);

      item_data["item_name"] = prefix["name"].toString() + " " + item_data["item_name"].toString();
    }

  // Generate item suffixes
  if((qrand() % 100)/100.0 < suffix_chance_){
      QJsonObject suffix = item_suffixes_[qrand() % item_suffixes_.size()];

      ApplyAffixToItem(suffix["modifiers"].toArray(), item_data);

      item_data["item_name"] = item_data["item_name"].toString() + " " + suffix["name"].toString();
    }

  return Item(item_data);
}

/**
 * Load a bunch of default items by their level so the prodecural item generator can use them
 */
void ItemFactory::InitializeItemDatabase()
{
  // Loads the file
  QFile loadFile(QStringLiteral(":/itemData/itemData.json"));
  if (!loadFile.open(QIODevice::ReadOnly)) {
      qWarning("Couldn't open itemData.json file. Aborting loading items.");
      return;
  }
  QByteArray save_data = loadFile.readAll();
  QJsonDocument loadDoc(QJsonDocument::fromJson(save_data));

  if(!loadDoc.object().contains("items") || !loadDoc.object()["items"].isArray()){
      qWarning("The itemData.json is missing the 'items' array. Aborting loading items.");
      return;
    }

  // Populate the item database
  QJsonArray items = loadDoc.object()["items"].toArray();
  for(int i = 0; i < items.count(); i++){
      if(!items[i].isObject()){
          qWarning("The itemData.json file is corrupted. Aborting loading items.");
          return;
        }

     QJsonObject item = items[i].toObject();

     if(!item.contains("equip_type") || !item.contains("item_level") || !item.contains("item_icon") || !item.contains("skill") || !item.contains("item_name")){
         qWarning("Item " + QString::number(i).toLocal8Bit() + " is missing an essential property as an item. Aborting loading items.");
         return;
       }

     // Add to the items_by_level_ map to be used in item generation
     items_by_level_[item["item_level"].toInt()].push_back(item);
    }
}

/**
 * Populates the prefixes and suffixes array from the file affixes.json
 */
void ItemFactory::InitializeAffixes()
{
  // Loads the file
  QFile loadFile(QStringLiteral(":/itemData/affixes.json"));
  if (!loadFile.open(QIODevice::ReadOnly)) {
      qWarning("Couldn't open affixes.json file. Aborting loading items.");
      return;
  }
  QByteArray save_data = loadFile.readAll();
  QJsonDocument loadDoc(QJsonDocument::fromJson(save_data));

  if(!loadDoc.object().contains("suffixes") || !loadDoc.object()["suffixes"].isArray() ||
     !loadDoc.object().contains("prefixes") || !loadDoc.object()["prefixes"].isArray()){
      qWarning("The affixes.json is missing 'suffixes' or 'prefixes' array. Aborting loading items.");
      return;
    }

  // Adds all of the suffixes and prefixes to their respective arrays
  for(QString affix : std::vector<QString>{"suffixes", "prefixes"}){
      QJsonArray affixes = loadDoc.object()[affix].toArray();
      for(int i = 0; i < affixes.count(); i++){
          if(!affixes[i].isObject()){
              qWarning("The affixes.json file is corrupted. Aborting loading items.");
              return;
            }

         QJsonObject affix_obj = affixes[i].toObject();

         if(!affix_obj.contains("modifiers") || !affix_obj.contains("name")){
             qWarning("Affix " + QString::number(i).toLocal8Bit() + " is missing a required attribute. Aborting loading items.");
             return;
           }

         affix == "suffixes" ? item_suffixes_.push_back(affix_obj) : item_prefixes_.push_back(affix_obj);
        }
    }
}

/**
 * Scales the modifier by level, and adds it to the item's modifier list.
 * @param affixes
 * @param item_data
 */
void ItemFactory::ApplyAffixToItem(QJsonArray affixes, QJsonObject &item_data)
{
  for(int i = 0; i < affixes.size(); i++){
      QJsonObject affix = affixes[i].toObject();

      // If the application type is additive, multiply by the level
      if(affix["application_type"].toInt() == static_cast<int>(ModifierOperation::Additive)){
                affix["amount"] = affix["amount"].toDouble() * item_data["item_level"].toInt();
        }

      // If the application is multiplicative, raise the amount by the level
      else{
          affix["amount"] = qPow(affix["amount"].toDouble(), item_data["item_level"].toInt());
        }

      item_data["modifiers"] = item_data["modifiers"].toArray() + affix;
    }
}
