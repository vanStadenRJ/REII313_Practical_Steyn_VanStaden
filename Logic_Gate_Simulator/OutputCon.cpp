#include <QBrush>
#include <QPoint>
#include <QDebug>
#include <QList>

#include "OutputCon.h"
#include "Simulation.h"
#include "Wire.h"
#include "Gate.h"

extern Simulation * simulation;

OutputCon::OutputCon(QGraphicsItem * parent): QGraphicsEllipseItem(parent)
{
    setRect(0,0,10,10);
    //setParent(this);

    //ALLOW RESPONDING TO HOVER EVENTS
    this->setAcceptHoverEvents(true);

    QObject::connect(simulation, SIGNAL(clicked()), this, SLOT(changeColor()));
    //QObject::connect(simulation->gate, SIGNAL(delete()), this, SLOT())
    //QObject::connect(simulation->gate, SIGNAL(delete_Wire), this, SLOT(deleteWire()));
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
    if(!(simulation->move_wire == nullptr))
    {
        simulation->dest_Gate = this->parent_Gate;
    }
    else
    {
        simulation->src_Gate = this->parent_Gate;
    }
}

void OutputCon::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    this->setBrush(Qt::NoBrush);

    simulation->setCursor(Qt::ArrowCursor);
    simulation->wireMode = false;
}

//void OutputCon::deleteWire()
//{
//    QList<QGraphicsItem *> colliding = collidingItems();
//    for(int i = 0, n = colliding.size(); i < n; i++)
//    {
//        if(typeid(*(colliding[i])) == typeid(Wire))
//        {
//            simulation->scene->removeItem(colliding[i]);
//            delete colliding[i];
//        }
//    }
    //qDebug() << "deleteWire";
//}

void OutputCon::changeColor()
{
    QBrush brush;
    brush.setColor(Qt::darkGreen);
    brush.setStyle(Qt::SolidPattern);
    this->setBrush(brush);
}
