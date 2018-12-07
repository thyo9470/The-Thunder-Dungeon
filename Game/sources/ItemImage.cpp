#include "headers/ItemImage.h"

#include <QToolTip>
#include <QMouseEvent>

ItemImage::ItemImage(QWidget *parent)
  :QLabel (parent)
{
  this->setMouseTracking(true);
}

/**
 * Shows the tooltip whenever the mouse moves across the item
 * @param event
 */
void ItemImage::mouseMoveEvent(QMouseEvent *event)
{
  QToolTip::showText(event->globalPos(), toolTip());
}
