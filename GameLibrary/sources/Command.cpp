#include "../headers/Command.h"

/*
    Command clases used to exeute a given class's method
    These are the commands used in the command design pattern
*/
void UpCommand::execute(EntityTile* tile){
  tile->SetPosition(tile->get_position() + Position(0,-1)); 
}

void RightCommand::execute(EntityTile* tile){
  tile->SetPosition(tile->get_position() + Position(1,0)); 
}

void DownCommand::execute(EntityTile* tile){
  tile->SetPosition(tile->get_position() + Position(0,1)); 
}

void LeftCommand::execute(EntityTile* tile){
  tile->SetPosition(tile->get_position() + Position(-1,0)); 
}

void DFSSearchCommand::execute(EnemyTile* tile, std::vector< std::vector< std::vector<Tile*> > > &board){
  tile->DFSMove(board);
}

void FollowCommnad::execute(EnemyTile* tile, std::vector< std::vector< std::vector<Tile*> > > &board){
  //tile->Follow(board);
}
