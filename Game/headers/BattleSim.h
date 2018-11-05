#ifndef BATTLESIM_H
#define BATTLESIM_H

#include <QApplication>

class BattleSim : public QObject{
  Q_OBJECT

  BattleSim(); // once player object created we will pass its reference
  ~BattleSim();

private slots:
  void PlayerTurn(int skill);

private:
  //Entity player_;
  //Entity enemy_;

  void EnemyTurn();

};

#endif // BATTLESIM_H
