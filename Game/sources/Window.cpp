#include "headers/Window.h"
#include "ui_mainwindow.h"

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <iostream>

#include "./headers/Tile.h"



Window::Window(QWidget *parent, int window_x, int window_y) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize the scene, which will hold all the objects to render
    scene_ = new QGraphicsScene();
    ui->graphicsView->setScene(scene_);

    // Keep scrollbars from appearing
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Keep the scene from resizing
    ui->graphicsView->setFixedSize(window_x, window_y);
    scene_->setSceneRect(0, 0, window_x, window_y);

    // Hold all the images
    sprite_sheet_ = QPixmap(":/images/Sprites.png");

}

Window::~Window()
{
    delete ui;
}

void Window::keyPressEvent(QKeyEvent *event)
{
    emit KeyPressSignal(event);
}

/**
 * When called, re-renders the board. NOTE: currently doesn't delete the memory created
 *
 * @param tileInfo A 3 dimensional qlist representing the board's tiles to render
 */
void Window::UpdateBoard(std::vector< std::vector< std::vector<Tile*> > > tile_info)
{
  scene_->clear();
  for(int y = 0; y < tile_info[0].size(); y++){
      for(int x = 0; x < tile_info[0][y].size(); x++){
          int tile = static_cast<int>( tile_info[0][y][x]->get_type() );
          for(unsigned int l = 0; l < tile_info.size(); l++){
              Tile cur_sq = (*tile_info[l][y][x]);
              if((cur_sq == TileType::Empty) == false){
                tile = static_cast<int>( tile_info[l][y][x]->get_type() );
              }
            }
          int tile_pos_x = tile % sprite_sheet_size_;
          int tile_pos_y = 0;//tile % sprite_sheet_size_;

          // Create and add the tile to the scene
          QGraphicsPixmapItem * pixmap = new QGraphicsPixmapItem();
          pixmap->setPixmap(sprite_sheet_.copy(tile_pos_x * sprite_size_, tile_pos_y * sprite_size_, sprite_size_, sprite_size_));
          pixmap->setPos(x * sprite_size_ * tile_scale_, y * sprite_size_ * tile_scale_);
          pixmap->setScale(pixmap->scale() * tile_scale_);
          scene_->addItem(pixmap);
      }
  }
}

void Window::on_save_button_clicked()
{
    emit SaveGameSignal();
}

void Window::on_load_button_clicked()
{
    emit LoadGameSignal();
}
