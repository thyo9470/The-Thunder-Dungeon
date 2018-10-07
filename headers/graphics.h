#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QGraphicsView>

class Graphics : public QGraphicsView
{
public:
    Graphics(int window_x, int window_y);
    void UpdateBoard(QList<QList<QList<int>>> tileInfo);
private:
    QGraphicsScene *scene_;
    QPixmap sprite_sheet_;
    int sprite_size_ = 8;
    int sprite_sheet_size_ = 16;
    int tile_scale_ = 4;
};

#endif // GRAPHICS_H
