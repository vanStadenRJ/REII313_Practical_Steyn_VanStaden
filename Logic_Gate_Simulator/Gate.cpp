#include "Gate.h"

Gate::Gate(QGraphicsItem *parent)
{
    this->setPixmap(QPixmap(":/images/And_Gate.png"));
    //rect = new QGraphicsRectItem(this);
    //rect->setRect(x()+50, y()+50, 50, 50);

    // set draw output branch
    rect = new QGraphicsRectItem(this);
    rect->setRect(x(), y(), 20, 5);
    rect->setPos(pixmap().width()-5, pixmap().height()/2);
    circle = new QGraphicsEllipseItem(this);
    circle->setRect(x(), y(), 10, 10);
    circle->setPos(pixmap().width()-5 + rect->rect().width(), pixmap().height()/2 - rect->rect().height()/2);

}
