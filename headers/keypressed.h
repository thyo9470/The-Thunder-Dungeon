#ifndef KEYPRESSED_H
#define KEYPRESSED_H

#include <QObject>

class KeyPressed : public QObject
{
    Q_OBJECT
public:
  KeyPressed();

protected:
    //bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif // KEYPRESSED_H
