
#include "./headers/WinWindow.h"
#include "ui_winwindow.h"

#include <QDebug>



WinWindow::WinWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::WinWindow)
{
  ui->setupUi(this);

  connect(ui->newGame, &QPushButton::pressed, this, &WinWindow::on_NewGameButton_clicked);

  // Initialize the scene, which will hold all the objects to render
  scene_ = new QGraphicsScene();
  ui->backgroundView->setScene(scene_);

  // Keep scrollbars from appearing
  ui->backgroundView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->backgroundView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  background_image_ = QPixmap(":/images/HippoGooseHead.png");

  //load backgroundr
  QLabel* background = new QLabel();
  background->setGeometry(10, 10, 801, 631);
  background->setPixmap(background_image_);
  background->setScaledContents(true);
  scene_->addWidget(background);

}

WinWindow::~WinWindow(){
  delete ui;
  delete scene_;
}

/**
 * @brief WinWindow::on_NewGameButton_clicked
 *
 * triggers the new game signal when pressing the new game button
 *
 */

void WinWindow::on_NewGameButton_clicked()
{
  emit NewGameSignal();
}
