#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity
{
public:
  Player(QJsonObject entity_stats);
};

#endif // PLAYER_H
