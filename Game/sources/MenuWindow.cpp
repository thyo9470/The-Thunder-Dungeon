#include "headers/MenuWindow.h"
#include "ui_menuwindow.h"

MenuWindow::MenuWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MenuWindow)
{
  ui->setupUi(this);
  ui->playButton->autoFillBackground();
  ui->playButton->setStyleSheet("border-image:url(:images/Button.png)");
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
}

void MenuWindow::on_playButton_clicked()
{
  emit StartGameSignal();
}

void MenuWindow::on_loadGameButton_clicked()
{
  emit LoadGameSignal();
}
