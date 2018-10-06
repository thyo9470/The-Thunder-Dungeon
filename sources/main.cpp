#include <QApplication>
#include "headers/graphics.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Create the widget responsible for all of our graphics and show it
    Graphics * graphics = new Graphics(800, 640);
    graphics->show();

    return a.exec();
}
