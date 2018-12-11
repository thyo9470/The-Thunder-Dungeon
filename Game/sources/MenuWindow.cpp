#include "headers/MenuWindow.h"
#include "ui_menuwindow.h"

MenuWindow::MenuWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MenuWindow)
{
  ui->setupUi(this);

  // Initialize the scene, which will hold all the objects to render
  scene_ = new QGraphicsScene();
  ui->backgroundView->setScene(scene_);

  // Keep scrollbars from appearing
  ui->backgroundView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->backgroundView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  background_image_ = QPixmap(":/images/HippoGooseEyes.png");

  //load backgroundr
  QLabel* background = new QLabel();
  background->setGeometry(10, 10, 801, 590);
  background->setPixmap(background_image_);
  background->setScaledContents(true);
  scene_->addWidget(background);

  /*ui->playButton->autoFillBackground();
  ui->playButton->setStyleSheet("border-image:url(:images/Button.png)");

  ui->loadGameButton->autoFillBackground();
  ui->loadGameButton->setStyleSheet("border-image:url(:images/Button.png)");*/

}

/**
 * Updates the window's load game button based on whether there is a exists game to load
 * @param saved_game
 */
void MenuWindow::UpdateWindow(bool saved_game)
{
  if(saved_game){
      ui->loadGameButton->setEnabled(true);
    }
  else{
      ui->loadGameButton->setEnabled(false);
    }
}

MenuWindow::~MenuWindow()
{
  delete ui;
  delete scene_;
}

void MenuWindow::on_playButton_clicked()
{
  emit StartGameSignal();
}

void MenuWindow::on_loadGameButton_clicked()
{
  emit LoadGameSignal();
}
