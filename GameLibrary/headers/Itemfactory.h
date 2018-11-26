#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include "Item.h"
#include <iostream>
#include <vector>

/**
 * Prodecurally generates items (not completed)
 */
class ItemFactory
{
public:
  ItemFactory();
  Item GenerateWeapon(int level);

private:
  std::vector<QString> item_adjectives_;
  std::vector<QString> weapon_nouns_;
  int sword_resource_count_ = 9;
  int axe_resource_count = 8;
  int staff_resource_count = 6;
};

#endif // ITEMFACTORY_H
