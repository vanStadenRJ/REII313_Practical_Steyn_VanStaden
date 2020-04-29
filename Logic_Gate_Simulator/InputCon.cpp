#include "InputCon.h"
#include "Simulation.h"

extern Simulation * simulation;

InputCon::InputCon(QGraphicsItem *parent)
{
    setRect(0,0,10,10);

    //ALLOW RESPONDING TO HOVER EVENTS
    this->setAcceptHoverEvents(true);
}

void InputCon::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    //Change color
    QBrush brush;
    brush.setColor(Qt::black);
    brush.setStyle(Qt::SolidPattern);
    this->setBrush(brush);

    simulation->setCursor(Qt::CrossCursor);
    simulation->wireMode = true;
}

void InputCon::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    this->setBrush(Qt::NoBrush);

    simulation->setCursor(Qt::ArrowCursor);
    simulation->wireMode = false;
}
