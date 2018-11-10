#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QKeyEvent>

#include "./headers/Tile.h"
#include "./headers/Entity.h"

namespace Ui {
class MainWindow;
}

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = nullptr, int window_x = 496, int window_y = 496);
    void UpdateBoard(std::vector< std::vector< std::vector<Tile*> > > tileInfo);
    void UpdatePlayerStats(Entity &entity);
    void UpdateLevel(int level);
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
    void SaveGameSignal();
    void LoadGameSignal();
private slots:
    void on_save_button_clicked();
    void on_load_button_clicked();
};

#endif // MAINWINDOW_H
