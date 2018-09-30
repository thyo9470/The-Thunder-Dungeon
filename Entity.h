

#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <vector>
#include "Item.h"

class Modifier{
   
  private:
    int * source;
    float value;
   
}

class Stat{

  private:
    float base_stat_;
    std::vector<Modifiers> stat_modifiers_;

};

class Entity{

  protected:
    
    Stats *stats;    
    std::vetor<Item> equipment; 
    
};

class Player:public Entity{

  public:
    Player():
    Entity(){};

};

class Enemy:public Entity{

  public:
    Enemy():
    Entity(){};

    void Attack();


};


#endif // ENTITY_H
