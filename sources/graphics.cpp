#include "headers/graphics.h"

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

Graphics::Graphics(int window_x, int window_y)
{
    // Initialize the scene, which will hold all the objects to render
    scene_ = new QGraphicsScene();
    setScene(scene_);

    // Keep scrollbars from appearing
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Keep the scene from resizing
    setFixedSize(window_x, window_y);
    scene_->setSceneRect(0, 0, window_x, window_y);

    // Hold all the images
    sprite_sheet_ = QPixmap(":/images/Tiles.png");
}

// When called, re-renders the board. NOTE: currently doesn't delete the memory created
void Graphics::UpdateBoard(QList<QList<QList<int> > > tileInfo)
{
    for(int i = 0; i < tileInfo.size(); i++){
        for(int y = 0; y < tileInfo[i].size(); y++){
            for(int x = 0; x < tileInfo[i][y].size(); x++){
                int tile = tileInfo[i][y][x];
                int tile_pos_x = tile % sprite_sheet_size_;
                int tile_pos_y = tile - tile_pos_x;
                // Create and add the tile to the scene
                QGraphicsPixmapItem * pixmap = new QGraphicsPixmapItem();
                pixmap->setPixmap(sprite_sheet_.copy(tile_pos_x * sprite_size_, tile_pos_y * sprite_size_, sprite_size_, sprite_size_));
                pixmap->setPos(x * sprite_size_ * tile_scale_, y * sprite_size_ * tile_scale_);
                pixmap->setScale(pixmap->scale() * tile_scale_);
                scene_->addItem(pixmap);
            }
        }
    }
}
