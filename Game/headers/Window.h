#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QJsonObject>

#include "./headers/Tile.h"
#include "./headers/Entity.h"
#include "./headers/Item.h"

namespace Ui {
class MainWindow;
}

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = nullptr, int window_x = 496, int window_y = 496);
    void UpdateBoard(std::vector< std::vector< std::vector<Tile*> > > tileInfo);
    void AddLighting(std::vector< std::vector< std::vector<Tile*> > > board, PlayerTile* player);
    void UpdatePlayerStats(Entity &entity);
    void UpdateLevel(int level);
    void UpdateItems(std::map<EquipType, Item> equipment);
    void ShowItemDropUI(Item item, std::map<EquipType, Item> equipment);
    ~Window();
    void keyPressEvent( QKeyEvent * event );
    bool GetStillChoosingItem();

private:

    Ui::MainWindow *ui;
    QGraphicsScene *scene_; // Objects get added to the scene

    QPixmap sprite_sheet_; // Loads all of the sprites

    //int sprite_size_ = 8; // The size of a sprite in pixels
    //int sprite_sheet_size_ = 16; // The width of the sprite sheet in number of sprites
    //int tile_scale_ = 2; // The scale factor to increase the size of the sprites rendered


    QPixmap dungeon_sheet_; // Loads all of thse sprites
    QPixmap player_sheet_; // loads sprite sheet for player
    QPixmap slime_sheet_; // loads enemy sheet (slime)
    int dungeon_sprite_size_ = 16; // the size in pixels of dungeon scenery sprites
    int dungeon_sheet_size_ = 20; // The width of the dungeon sprite sheet in number of sprites
    int dungeon_tile_scale_ = 1;

    QGraphicsPixmapItem* GetWallSprite(std::array<bool, 4> wall_sides);
    QGraphicsPixmapItem* GetDungeonSprite(Tile* tile);

    int lighting_distance_ = 20;

    QString ItemToHTML(Item item);

    bool paused_ = false;

signals:
    void KeyPressSignal(QKeyEvent* event);
    void SaveGameSignal();
    void QuitGameSignal();
    void EquipItemSignal(bool equip_item);
private slots:
    void on_save_button_clicked();
    void on_equipButton_clicked();
    void on_throwAwayButton_clicked();
    void on_resumeButton_clicked();
    void on_quitButton_clicked();
    void on_pauseButton_clicked();
};

#endif // MAINWINDOW_H
