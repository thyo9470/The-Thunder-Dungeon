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
  ui->backgroundView->setScene(scene_);

  // Keep scrollbars from appearing
  ui->backgroundView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->backgroundView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  // Hold all the images
  sprite_sheet_ = QPixmap(":/images/Sprites.png");

  //load backgroundr
  QLabel* background = new QLabel();
  background->setGeometry(10, 10, 781, 421);
  background->setPixmap(QPixmap(":/images/Crypte.png"));
  background->setScaledContents(true);
  scene_->addWidget(background);

  //set player and enemy position
  player_position_x_ = 100;
  player_position_y_ = 6.0*scene_->height()/10.0;

  enemy_position_x_ = scene_->width()-170;
  enemy_position_y_ = 6.0*scene_->height()/10.0;

  // connect pressed button
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

  //updatee player info
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

  int row = 0;
  // Create and add the tile to the scene
  QGraphicsPixmapItem * pixmap_player = new QGraphicsPixmapItem();
  pixmap_player->setPixmap(sprite_sheet_.copy(player->get_sprite_index() * sprite_size_, row * sprite_size_, sprite_size_, sprite_size_));
  pixmap_player->setPos( player_position_x_ , player_position_y_);
  pixmap_player->setScale(pixmap_player->scale() * tile_scale_);
  scene_->addItem(pixmap_player);

  //update enemy info
  Entity* enemy = battle_sim->GetEnemy();
  ui->enemyHealthBar->setValue(enemy->GetHealthPercent());
  ui->enemyMagicBar->setValue(enemy->GetMagicPercent());

  // Create and add the tile to the scene
  QGraphicsPixmapItem * pixmap_enemy = new QGraphicsPixmapItem();
  pixmap_enemy->setPixmap(sprite_sheet_.copy(enemy->get_sprite_index() * sprite_size_, row * sprite_size_, sprite_size_, sprite_size_));
  pixmap_enemy->setPos( enemy_position_x_ , enemy_position_y_);
  pixmap_enemy->setScale(pixmap_enemy->scale() * tile_scale_);
  scene_->addItem(pixmap_enemy);
}
