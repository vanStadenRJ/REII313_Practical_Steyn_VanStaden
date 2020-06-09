#include "Simulation.h"
#include "OutputCon.h"
#include "Wire.h"
#include "Gate.h"

extern Simulation * simulation;

OutputCon::OutputCon(QGraphicsItem * parent): QGraphicsEllipseItem(parent)
{
    // Set z-value to ensure wire placed underneath node
    this->setZValue(2);

    // Set visual of node
    this->setRect(0,0,12,12);    
    QPen pen;
    pen.setWidth(2);
    this->setPen(pen);
    this->setBrush(QBrush(QColor(255,255,255)));

    //ALLOW RESPONDING TO HOVER EVENTS
    this->setAcceptHoverEvents(true);
}

void OutputCon::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if(simulation->isBuildMode == false && simulation->isMove == false && simulation->move_wire == nullptr)
    {
        //Change color
        this -> setRect(0,0,13,13);        
        this->setBrush(QBrush(QColor(0,0,0)));

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
        simulation->sourceNode = this->centerPoint;
    }
}

void OutputCon::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    this -> setRect(0,0,12,12);
    if(simulation->isBuildMode == false && simulation->isMove == false)
    {
        simulation->setCursor(Qt::ArrowCursor);
        simulation->wireMode = false;
    }
    this->setBrush(QBrush(QColor(255,255,255)));
}
