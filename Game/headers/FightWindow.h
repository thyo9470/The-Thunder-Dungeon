#ifndef FIGHTWINDOW_H
#define FIGHTWINDOW_H

#include "BattleSim.h"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QKeyEvent>

namespace Ui {
class FightWindow;
}

class FightWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FightWindow(QWidget *parent = nullptr);
    ~FightWindow();

    Ui::FightWindow * get_ui(){return ui;}

    void UpdateFightWindow(BattleSim* battle_sim);

private:

    Ui::FightWindow *ui;
    QGraphicsScene *scene_; // Objects get added to the scene

    QPixmap sprite_sheet_; // Loads all of the sprites

    int sprite_size_ = 8; // The size of a sprite in pixels
    int sprite_sheet_size_ = 16; // The width of the sprite sheet in number of sprites
    int tile_scale_ = 10; // The scale factor to increase the size of the sprites rendered

    double player_position_x_;
    double player_position_y_;
    double enemy_position_x_;
    double enemy_position_y_;

private slots:
    void ButtonPressedSlot();


signals:
    void ButtonPressedSignal(int skill_id);

};

#endif // FIGHTWINDOW_H
