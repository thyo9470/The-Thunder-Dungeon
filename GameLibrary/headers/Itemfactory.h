#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include "Item.h"
#include <iostream>
#include <vector>

class ItemFactory
{
public:
  ItemFactory();
  Item GenerateItem(int level);

private:
  std::vector<std::string> item_adjectives_;
  std::vector<std::string> item_nouns_;
};

#endif // ITEMFACTORY_H
