#include "../headers/KeyPress.h"

#include <QApplication>
#include <QKeyEvent>

#include <QTextStream>

KeyPress::KeyPress(QWidget *parent) :
    QWidget(parent)
{
    myLabel = new QLabel("LABEL");
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(myLabel);
    setLayout(mainLayout);

}

void KeyPress::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        myLabel->setText("You pressed ESC");
        QTextStream out(stdout);
        out << "test" << endl;
    }
}

void KeyPress::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        myLabel->setText("You released ESC");
    }
}
