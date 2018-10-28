#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QKeyEvent>

#include "./headers/Tile.h"

namespace Ui {
class MainWindow;
}

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = nullptr, int window_x = 800, int window_y = 640);
    void UpdateBoard(std::vector< std::vector< std::vector<Tile*> > > tileInfo);
    ~Window();
    void keyPressEvent( QKeyEvent * event );

private:

    Ui::MainWindow *ui;
    QGraphicsScene *scene_; // Objects get added to the scene

    QPixmap sprite_sheet_; // Loads all of the sprites

    int sprite_size_ = 8; // The size of a sprite in pixels
    int sprite_sheet_size_ = 16; // The width of the sprite sheet in number of sprites
    int tile_scale_ = 2; // The scale factor to increase the size of the sprites rendered

signals:
    void KeyPressSignal(QKeyEvent* event);
};

#endif // MAINWINDOW_H
