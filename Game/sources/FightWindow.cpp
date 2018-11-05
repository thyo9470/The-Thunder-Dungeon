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

  connect(ui->skillButton_1, &QPushButton::pressed, this, &FightWindow::ButtonClickedSlot);
  connect(ui->skillButton_2, &QPushButton::pressed, this, &FightWindow::ButtonClickedSlot);
  connect(ui->skillButton_3, &QPushButton::pressed, this, &FightWindow::ButtonClickedSlot);
  connect(ui->skillButton_4, &QPushButton::pressed, this, &FightWindow::ButtonClickedSlot);
  connect(ui->runButton, &QPushButton::pressed, this, &FightWindow::ButtonClickedSlot);

}

FightWindow::~FightWindow(){
    delete ui;
}

void FightWindow::ButtonClickedSlot(){
  QObject *senderObj = sender(); // This will give Sender object
  int skill_index = senderObj->property("skill").value<int>();  //objectName();

  if(skill_index == 4){
    emit ButtonClickedSignal();
  }
}
