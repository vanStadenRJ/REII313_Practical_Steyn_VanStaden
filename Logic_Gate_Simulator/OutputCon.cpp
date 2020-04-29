#include <QBrush>
#include <QPoint>
#include <QDebug>

#include "OutputCon.h"
#include "Simulation.h"

extern Simulation * simulation;

OutputCon::OutputCon()
{
    setRect(0,0,10,10);

    //ALLOW RESPONDING TO HOVER EVENTS
    this->setAcceptHoverEvents(true);

    QObject::connect(simulation, SIGNAL(clicked()), this, SLOT(changeColor()));
}

void OutputCon::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    //Change color
    QBrush brush;
    brush.setColor(Qt::black);
    brush.setStyle(Qt::SolidPattern);
    this->setBrush(brush);

    simulation->setCursor(Qt::CrossCursor);
    simulation->wireMode = true;
}

void OutputCon::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    this->setBrush(Qt::NoBrush);

    simulation->setCursor(Qt::ArrowCursor);
    simulation->wireMode = false;
}

void OutputCon::changeColor()
{
    QBrush brush;
    brush.setColor(Qt::darkGreen);
    brush.setStyle(Qt::SolidPattern);
    this->setBrush(brush);
}
