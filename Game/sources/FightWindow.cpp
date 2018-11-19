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
  player_sheet_ = QPixmap(":/images/Player.png");
  slime_sheet_ = QPixmap(":/images/Slime.png");

  //load backgroundr
  QLabel* background = new QLabel();
  background->setGeometry(10, 10, 781, 421);
  //background->setPixmap(QPixmap(":/images/Crypte.png"));
  background->setPixmap(QPixmap(":/images/souterrain.png"));
  background->setScaledContents(true);
  scene_->addWidget(background);

  // hide exit button
  ui->exitButton->setVisible(false);
  ui->exitButton->setEnabled(false);

  //set player and enemy position
  player_position_x_ = 100;
  //player_position_y_ = 6.0*scene_->height()/10.0;
  player_position_y_ = 5.0*scene_->height()/10.0;

  //enemy_position_x_ = scene_->width()-170;
  enemy_position_x_ = scene_->width()-230;
  //enemy_position_y_ = 6.0*scene_->height()/10.0;
  enemy_position_y_ = 5.3*scene_->height()/10.0;

  // connect pressed button
  connect(ui->skillButton_1, &QPushButton::pressed, this, &FightWindow::ButtonPressedSlot);
  connect(ui->skillButton_2, &QPushButton::pressed, this, &FightWindow::ButtonPressedSlot);
  connect(ui->skillButton_3, &QPushButton::pressed, this, &FightWindow::ButtonPressedSlot);
  connect(ui->skillButton_4, &QPushButton::pressed, this, &FightWindow::ButtonPressedSlot);
  connect(ui->runButton, &QPushButton::pressed, this, &FightWindow::ButtonPressedSlot);
  connect(ui->exitButton, &QPushButton::pressed, this, &FightWindow::ButtonPressedSlot);

}

FightWindow::~FightWindow(){
    delete ui;
}

void FightWindow::ButtonPressedSlot(){
  QObject *senderObj = sender(); // This will give Sender object
  int skill_id = senderObj->property("skill").value<int>();  //objectName();

  emit ButtonPressedSignal(skill_id);
}

/**
 * @brief FightWindow::UpdateFightWindow
 *
 * Updates the fight window GUI
 *
 * @param battle_sim - The current state of the battle_sim
 */

void FightWindow::UpdateFightWindow(BattleSim* battle_sim){
  // if it's the end of a battle show exit button otherwise hide it
  if(battle_sim->GetState() == BattleState::End){
    ui->exitButton->setVisible(true);
    ui->exitButton->setEnabled(true);
    }else if(battle_sim->GetState() == BattleState::Active){
    ui->exitButton->setVisible(false);
    ui->exitButton->setEnabled(false);
    }

  //update log
  std::vector<std::string> log = battle_sim->GetLog();
  std::string log_formatted = "";
  for(std::string message : log){
    log_formatted += "\n" + message;
  }
  ui->dialogLabel->setText(QString::fromStdString(log_formatted));

  //updatee player info
  Entity* player = battle_sim->GetPlayer();
  ui->playerHealthBar->setMaximum(player->GetMaxHealth());
  ui->playerHealthBar->setValue(player->GetHealth());
  ui->playerMagicBar->setMaximum(player->GetMaxMagic());
  ui->playerMagicBar->setValue(player->GetMagic());

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
  //pixmap_player->setPixmap(sprite_sheet_.copy(player->get_sprite_index() * sprite_size_, row * sprite_size_, sprite_size_, sprite_size_));
  pixmap_player->setPixmap(player_sheet_.copy(0, 0, dungeon_sprite_size_, dungeon_sprite_size_));
  pixmap_player->setPos( player_position_x_ , player_position_y_);
  pixmap_player->setScale(pixmap_player->scale() * tile_scale_);
  scene_->addItem(pixmap_player);

  //update enemy info
  Entity* enemy = battle_sim->GetEnemy();
  ui->enemyHealthBar->setMaximum(enemy->GetMaxHealth());
  ui->enemyHealthBar->setValue(enemy->GetHealth());
  ui->enemyMagicBar->setMaximum(enemy->GetMaxMagic());
  ui->enemyMagicBar->setValue(enemy->GetMagic());

  // Create and add the tile to the scene
  QGraphicsPixmapItem * pixmap_enemy = new QGraphicsPixmapItem();
  //pixmap_enemy->setPixmap(sprite_sheet_.copy(enemy->get_sprite_index() * sprite_size_, row * sprite_size_, sprite_size_, sprite_size_));
  pixmap_enemy->setPixmap(slime_sheet_.copy(0, 0, dungeon_sprite_size_, dungeon_sprite_size_));
  pixmap_enemy->setPos( enemy_position_x_ , enemy_position_y_);
  pixmap_enemy->setScale(pixmap_enemy->scale() * tile_scale_);
  scene_->addItem(pixmap_enemy);
}
