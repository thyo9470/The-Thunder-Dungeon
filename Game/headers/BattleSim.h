#ifndef BATTLESIM_H
#define BATTLESIM_H

#include <QApplication>
#include <vector>

#include <headers/Entity.h>

class BattleSim : public QObject{
  Q_OBJECT

public:
  BattleSim(Entity* player); // once player object created we will pass its reference
  ~BattleSim();
  std::vector<std::string> GetLog(){return log_;}
  Entity* GetPlayer(){return player_;}
  Entity* GetEnemy(){return enemy_;}

public slots:
  void PlayerTurn(int skill);

private:
  Entity* player_;
  Entity* enemy_;
  std::vector<std::string> log_;

  void EnemyTurn();
  void UpdateLog(std::string new_message);

};

#endif // BATTLESIM_H
