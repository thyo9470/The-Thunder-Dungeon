#ifndef MENUWINDOW_H
#define MENUWINDOW_H

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
};

#endif // MENUWINDOW_H
