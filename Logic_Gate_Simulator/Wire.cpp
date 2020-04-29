#include "Wire.h"

#include <QPen>

Wire::Wire(QGraphicsItem *parent)
{
    QPen pen;
    pen.setWidth(2);
    pen.setCapStyle(Qt::RoundCap);
    this->setPen(pen);
}

void Wire::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //Add Delete Function HERE!!
}
