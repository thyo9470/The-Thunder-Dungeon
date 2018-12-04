#ifndef ITEMIMAGE_H
#define ITEMIMAGE_H

#include <QLabel>

/**
 * Class specifically designed to make the item tooltip pop up faster
 */
class ItemImage : public QLabel
{
  Q_OBJECT

public:
  explicit ItemImage(QWidget * parent = 0);
protected:
  void mouseMoveEvent(QMouseEvent * event);
};

#endif // ITEMIMAGE_H
