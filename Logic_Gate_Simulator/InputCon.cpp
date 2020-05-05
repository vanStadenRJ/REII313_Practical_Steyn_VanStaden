#include "InputCon.h"
#include "Simulation.h"

#include <QDebug>

extern Simulation * simulation;

InputCon::InputCon(QGraphicsItem *parent): QGraphicsEllipseItem (parent)
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
    if(!(simulation->move_wire == nullptr))
    {
        simulation->dest_Gate = this->parent_Gate;
    }
    else
    {
        simulation->src_Gate = this->parent_Gate;
    }
}

void InputCon::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    this->setBrush(Qt::NoBrush);

    simulation->setCursor(Qt::ArrowCursor);
    simulation->wireMode = false;
}
