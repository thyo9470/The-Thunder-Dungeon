#ifndef BATTLESIM_H
#define BATTLESIM_H

#include <QApplication>
#include <vector>


#include <headers/Entity.h>
#include "headers/BattleAgent.h"

enum class BattleState {Active, End, Inactive};

class BattleSim : public QObject{
  Q_OBJECT

public:
  BattleSim(Entity* player, int minimax_depth = 3); // once player object created we will pass its reference
  ~BattleSim();
  std::vector<std::string> GetLog(){return log_;}
  Entity* GetPlayer(){return player_;}
  Entity* GetEnemy(){return enemy_;}
  BattleState GetState(){return state_;}

  // change battle state
  void ActivateBattle(){state_ = BattleState::Active;}
  void EndBattle(){state_ = BattleState::End;}
  void DeactivateBattle(){state_ = BattleState::Inactive;}

public slots:
  void PlayerTurn(int skill);

signals:
  void DropItemSignal();
  void GameOverSignal();

private:
  Entity* player_;
  Entity* enemy_;
  BattleAgent* agent_;
  std::vector<std::string> log_;
  BattleState state_;
  // How many moves ahead can the enemy look at (larger = harder enemies)
  int minimax_depth_;

  void EnemyTurn();
  void IsBattleOver();
  void UpdateLog(std::string new_message);

};

#endif // BATTLESIM_H
