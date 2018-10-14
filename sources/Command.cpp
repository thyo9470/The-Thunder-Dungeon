#include "../headers/Command.h"

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
