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
    this->canClick = true;
    this->isSource = false;

    QObject::connect(simulation, SIGNAL(clicked()), this, SLOT(changeColor()));

//    QBrush brush;
//    brush.setColor(Qt::darkRed);
//    brush.setStyle(Qt::SolidPattern);
//    this->setBrush(brush);
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

void OutputCon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //wire = new Wire();
    //wire->source = simulation->mapFromGlobal(QCursor::pos());
//    this->source = simulation->mapFromGlobal(QCursor::pos());

//    if(canClick == false)
//    {

    //    }
}

void OutputCon::changeColor()
{
    QBrush brush;
    brush.setColor(Qt::red);
    brush.setStyle(Qt::SolidPattern);
    this->setBrush(brush);
}
