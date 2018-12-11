#ifndef WinWINDOW_H
#define WinUWINDOW_H

#include <QGraphicsScene>
#include <QMainWindow>
#include "headers/Board.h"

namespace Ui {
  class WinWindow;
}

class WinWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit WinWindow(QWidget *parent = nullptr);
  ~WinWindow();

public slots:
  void on_NewGameButton_clicked();

signals:
  void NewGameSignal();

private:
  Ui::WinWindow *ui;
  QGraphicsScene *scene_; // Objects get added to the scene

  QPixmap background_image_;

};

#endif // MENUWINDOW_H
