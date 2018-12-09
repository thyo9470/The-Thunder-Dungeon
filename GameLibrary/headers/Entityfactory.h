#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include "Entity.h"
#include "Item.h"
#include "Itemfactory.h"

/**
 * Makes generating default players and enemies a little nicer
 */
class EntityFactory
{
public:
  static Entity * GenerateEnemy(int level);
  Entity * GenerateEnemyWithEquipment(int level);
  static Entity * GeneratePlayer();

private:
  static void EquipDefaultItems(Entity &entity);
  ItemFactory item_factory_;
};

#endif // ENTITYFACTORY_H
