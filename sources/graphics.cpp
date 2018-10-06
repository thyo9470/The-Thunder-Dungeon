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

    // Create and add a single tile to the scene
    QGraphicsPixmapItem * pixmap = new QGraphicsPixmapItem();
    pixmap->setPixmap(QPixmap(":/images/Background.png"));

    scene_->addItem(pixmap);
}
