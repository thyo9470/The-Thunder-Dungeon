
#ifndef _COMMAND_H_
#define _COMMAND_H_

#include "Tile.h"

class Command{

public:
  virtual void execute(EntityTile* tile) = 0; 
};

class UpCommand : public Command{

public:
  virtual void execute(EntityTile* tile);  

};

class DownCommand : public Command{

public:
  virtual void execute(EntityTile* tile);

};

class RightCommand : public Command{

public:
  virtual void execute(EntityTile* tile);

};

class LeftCommand : public Command{

public:
  virtual void execute(EntityTile* tile);

};

#endif // COMMAND_H
