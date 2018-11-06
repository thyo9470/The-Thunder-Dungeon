#include "../headers/FightWindow.h"

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <iostream>
#include <ui_fightwindow.h>
#include <QDebug>

FightWindow::FightWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::FightWindow)
{
  ui->setupUi(this);

  // Initialize the scene, which will hold all the objects to render
  scene_ = new QGraphicsScene();
  ui->graphicsView->setScene(scene_);

  // Keep scrollbars from appearing
  ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  // Hold all the images
  sprite_sheet_ = QPixmap(":/images/Sprites.png");

  connect(ui->skillButton_1, &QPushButton::pressed, this, &FightWindow::ButtonPressedSlot);
  connect(ui->skillButton_2, &QPushButton::pressed, this, &FightWindow::ButtonPressedSlot);
  connect(ui->skillButton_3, &QPushButton::pressed, this, &FightWindow::ButtonPressedSlot);
  connect(ui->skillButton_4, &QPushButton::pressed, this, &FightWindow::ButtonPressedSlot);
  connect(ui->runButton, &QPushButton::pressed, this, &FightWindow::ButtonPressedSlot);

}

FightWindow::~FightWindow(){
    delete ui;
}

void FightWindow::ButtonPressedSlot(){
  QObject *senderObj = sender(); // This will give Sender object
  int skill_id = senderObj->property("skill").value<int>();  //objectName();

  emit ButtonPressedSignal(skill_id);
}

void FightWindow::UpdateFightWindow(BattleSim* battle_sim){
  //update log
  std::vector<std::string> log = battle_sim->GetLog();
  std::string log_formatted = "";
  for(std::string message : log){
    log_formatted += "\n" + message;
  }
  ui->dialogLabel->setText(QString::fromStdString(log_formatted));

  //update player info
  Entity* player = battle_sim->GetPlayer();
  ui->playerHealthBar->setValue(player->GetHealthPercent());
  ui->playerMagicBar->setValue(player->GetMagicPercent());

  // update skill info
  std::vector<Skill> player_skills = player->GetSkills();
  std::vector<QPushButton*> button_skills = {ui->skillButton_1, ui->skillButton_2, ui->skillButton_3, ui->skillButton_4};
  for(unsigned int i = 0; i < player_skills.size(); i++){
    button_skills[i]->setText(QString::fromStdString(player_skills[i].GetName()));
    button_skills[i]->setToolTip(QString::fromStdString(player_skills[i].GetDescription()));
  }

  //update enemy info
  Entity* enemy = battle_sim->GetEnemy();
  ui->enemyHealthBar->setValue(enemy->GetHealthPercent());
  ui->enemyMagicBar->setValue(enemy->GetMagicPercent());
}
