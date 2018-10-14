#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

namespace Ui {
class MainWindow;
}

class Graphics : public QMainWindow
{
    Q_OBJECT

public:
    explicit Graphics(QWidget *parent = nullptr, int window_x = 800, int window_y = 640);
    void UpdateBoard(QList<QList<QList<int>>> tileInfo);
    ~Graphics();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene_; // Objects get added to the scene

    QPixmap sprite_sheet_; // Loads all of the sprites

    int sprite_size_ = 8; // The size of a sprite in pixels
    int sprite_sheet_size_ = 16; // The width of the sprite sheet in number of sprites
    int tile_scale_ = 4; // The scale factor to increase the size of the sprites rendered
};

#endif // MAINWINDOW_H
