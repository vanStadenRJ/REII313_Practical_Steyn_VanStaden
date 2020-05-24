#include "InputCon.h"
#include "Simulation.h"
extern Simulation * simulation;

InputCon::InputCon(QGraphicsItem *parent): QGraphicsEllipseItem (parent)
{
    posGate = 0;
    Logic = 0;
    setRect(0,0,10,10);

    //ALLOW RESPONDING TO HOVER EVENTS
    this->setAcceptHoverEvents(true);
    connected = false;
    Logic = 0;
    test = false;

    QObject::connect(simulation, SIGNAL(Input_Show()), this, SLOT(OutputToInput()));
    QObject::connect(simulation, SIGNAL(clear_Node()), this, SLOT(clearNode()));
    QObject::connect(simulation,SIGNAL(connected_Node(int)), this, SLOT(conNode(int)));
}

void InputCon::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if((connected == false && simulation->isBuildMode == false  && simulation->isMove == false) && !(simulation->move_wire == nullptr))
    //if(!(simulation->move_wire == nullptr))
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
            simulation->dest_NodeNr = this->posGate;
        }
        else
        {
            simulation->src_Gate = this->parent_Gate;
            simulation->src_NodeNr = this->posGate;
        }
        simulation->destNode = this->centerPoint;

        qDebug() << "Gate Nr: " << this->parent_Gate << "; Node Nr: " << this->posGate << " Logig: " << Logic;
    }
}

void InputCon::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if((connected == false && simulation->isBuildMode == false && simulation->isMove == false) && !(simulation->move_wire == nullptr))
    //if(!(simulation->move_wire == nullptr))
    {
        test = false;
        if(simulation->wireMode == false)
        {
            this->setBrush(Qt::NoBrush);
        }
        else
        {
            QBrush brush;
            brush.setColor(Qt::darkGreen);
            brush.setStyle(Qt::SolidPattern);
            this->setBrush(brush);
        }


        simulation->setCursor(Qt::ArrowCursor);
        simulation->wireMode = false;
        simulation->src_NodeNr = 0;
    }
}

void InputCon::OutputToInput()
{
    if(!(simulation->src_Gate == this->parent_Gate) && (this->connected == false))
    {
        QBrush brush;
        brush.setColor(Qt::darkGreen);
        brush.setStyle(Qt::SolidPattern);
        this->setBrush(brush);
    }
}

void InputCon::clearNode()
{
    if(this->connected == false)
    {
        this->setBrush(Qt::NoBrush);
    }
}

void InputCon::conNode(int k)
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
            qDebug() << k;
            this->Logic = k;
            test = false;
        }
    }
}
