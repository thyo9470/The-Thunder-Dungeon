
#ifndef _COMMAND_H_
#define _COMMAND_H_

#include "Tile.h"

/*
    Command classes used in command design pattern
*/
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

class DFSSearchCommand : public Command{

public:
  virtual void execute(EnemyTile* tile, std::vector< std::vector< std::vector<Tile*> > > &board);
};

class FollowCommnad : public Command{

public:
  virtual void execute(EnemyTile* tile, std::vector< std::vector< std::vector<Tile*> > > &board);

};

#endif // COMMAND_H
