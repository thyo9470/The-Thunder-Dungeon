#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QGraphicsView>

class Graphics : public QGraphicsView
{
public:
    Graphics(int window_x, int window_y);
private:
    QGraphicsScene *scene_;
};

#endif // GRAPHICS_H
