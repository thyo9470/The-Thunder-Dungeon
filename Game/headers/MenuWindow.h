#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QGraphicsScene>
#include <QMainWindow>
#include "headers/Board.h"

namespace Ui {
  class MenuWindow;
}

class MenuWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MenuWindow(QWidget *parent = nullptr);
  void UpdateWindow(bool saved_game);
  ~MenuWindow();

private slots:
  void on_playButton_clicked();
  void on_loadGameButton_clicked();

signals:
    void StartGameSignal();
    void LoadGameSignal();

private:
  Ui::MenuWindow *ui;
  QGraphicsScene *scene_; // Objects get added to the scene

  QPixmap background_image_;

};

#endif // MENUWINDOW_H
