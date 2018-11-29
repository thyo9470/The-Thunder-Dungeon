#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include "Entity.h"

/**
 * Makes generating default players and enemies a little nicer
 */
class EntityFactory
{
public:
  static Entity * GenerateEnemy(int level);
  static Entity * GeneratePlayer();

private:
  static void EquipDefaultItems(Entity &entity);
};

#endif // ENTITYFACTORY_H
