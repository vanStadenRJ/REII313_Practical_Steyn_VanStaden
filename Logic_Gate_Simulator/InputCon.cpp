#include "InputCon.h"
#include "Simulation.h"

#include <QDebug>

extern Simulation * simulation;

InputCon::InputCon(QGraphicsItem *parent): QGraphicsEllipseItem (parent)
{
    posGate = 0;
    setRect(0,0,10,10);

    //ALLOW RESPONDING TO HOVER EVENTS
    this->setAcceptHoverEvents(true);
    connected = false;
    test = false;

    QObject::connect(simulation, SIGNAL(Input_Show()), this, SLOT(OutputToInput()));
    QObject::connect(simulation, SIGNAL(clear_Node()), this, SLOT(clearNode()));
    QObject::connect(simulation,SIGNAL(connected_Node()), this, SLOT(conNode()));
}

void InputCon::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if(connected == false)
    {
        //Change color
        QBrush brush;
        brush.setColor(Qt::black);
        brush.setStyle(Qt::SolidPattern);
        this->setBrush(brush);
        test = true;

        simulation->setCursor(Qt::CrossCursor);
        simulation->wireMode = true;
        simulation->Output = false;
        if(!(simulation->move_wire == nullptr))
        {
            simulation->dest_Gate = this->parent_Gate;
        }
        else
        {
            simulation->src_Gate = this->parent_Gate;
        }
    }
}

void InputCon::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if(connected == false)
    {
        test = false;
        this->setBrush(Qt::NoBrush);

        simulation->setCursor(Qt::ArrowCursor);
        simulation->wireMode = false;
    }
}

void InputCon::OutputToInput()
{
    if(!(simulation->src_Gate == this->parent_Gate))
    {
        QBrush brush;
        brush.setColor(Qt::darkGreen);
        brush.setStyle(Qt::SolidPattern);
        this->setBrush(brush);
    }
}

void InputCon::clearNode()
{
    QBrush brush;
    brush.setColor(Qt::red);
    brush.setStyle(Qt::SolidPattern);
    this->setBrush(brush);
}

void InputCon::conNode()
{
    if(simulation->dest_Gate == this->parent_Gate || simulation->src_Gate == this->parent_Gate)
    {
        if(test == true)
        {
            this->connected = true;
            QBrush brush;
            brush.setColor(Qt::black);
            brush.setStyle(Qt::SolidPattern);
            this->setBrush(brush);
        }
    }
}