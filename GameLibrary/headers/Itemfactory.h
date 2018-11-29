#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include "Item.h"
#include <iostream>
#include <vector>
#include <map>

/**
 * Prodecurally generates items (not completed)
 */
class ItemFactory
{
public:
  ItemFactory();
  Item GenerateItem(int level);

private:
  std::vector<QJsonObject> item_suffixes_;
  std::vector<QJsonObject> item_prefixes_;
  float prefix_chance_ = 0.5;
  float suffix_chance_ = 0.25;
  std::map<int, std::vector<QJsonObject>> items_by_level_;
  int sword_resource_count_ = 9;
  int axe_resource_count = 8;
  int staff_resource_count = 6;
  void InitializeItemDatabase();
  void InitializeAffixes();
  void ApplyAffixToItem(QJsonArray affixes, QJsonObject &item_data);
};

#endif // ITEMFACTORY_H
