#include <QApplication>
#include "headers/graphics.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Create the widget responsible for all of our graphics and show it
    Graphics * graphics = new Graphics(800, 640);
    graphics->show();

    QList<QList<int>> floor;

    for(int i = 0; i < 16; i++){
        QList<int> row;
        floor.append(row);
        for(int j = 0; j < 16; j++){
            floor[i].append(5);
        }
    }

    QList<QList<QList<int>>> board;
    board.append(floor);
    graphics->UpdateBoard(board);

    return a.exec();
}
