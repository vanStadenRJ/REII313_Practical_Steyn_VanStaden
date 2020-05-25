#include "ButtonPanel.h"
#include "Simulation.h"

extern Simulation * simulation;

ButtonPanel::ButtonPanel()
{
//    this->setRect(5,5,250,864);
//    this->update();
    this->setZValue(0);
}

void ButtonPanel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QColor(Qt::lightGray));

    QPen pen;
    pen.setWidth(3);
    painter->setPen(pen);
    painter->drawRoundedRect(7, 7, 300, 860, 5, 5);
}

//void ButtonPanel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
//{

//}
