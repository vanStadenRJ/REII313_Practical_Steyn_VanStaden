#include "Simulation.h"
#include "OutputCon.h"
#include "Wire.h"
#include "Gate.h"

extern Simulation * simulation;

OutputCon::OutputCon(QGraphicsItem * parent): QGraphicsEllipseItem(parent)
{
    setRect(0,0,10,10);

    //ALLOW RESPONDING TO HOVER EVENTS
    this->setAcceptHoverEvents(true);
    connected = false;
    test = false;
    test_src = false;

    QObject::connect(simulation, SIGNAL(Output_Show()), this, SLOT(InputToOutput()));
    QObject::connect(simulation, SIGNAL(clear_Node()), this, SLOT(clearNode()));
    QObject::connect(simulation,SIGNAL(connected_Node(int)), this, SLOT(conNode()));
}

void OutputCon::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    //if(connected == false && simulation->isBuildMode == false && simulation->isMove == false)
    if(simulation->move_wire == nullptr)
    {
        //Change color
        this -> setRect(0,0,12,12);

        QBrush brush;
        brush.setColor(Qt::black);
        brush.setStyle(Qt::SolidPattern);
        this->setBrush(brush);

        test = true;
        simulation->setCursor(Qt::CrossCursor);
        simulation->wireMode = true;
        simulation->Output = true;
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

void OutputCon::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    this -> setRect(0,0,10,10);
    //if(connected == false && simulation->isBuildMode == false && simulation->isMove == false)
    if(simulation->move_wire == nullptr)
    {
        if(test_src == false)
        {
            test = false;
            this->setBrush(Qt::NoBrush);
        }
        simulation->setCursor(Qt::ArrowCursor);
        simulation->wireMode = false;
    }
}

void OutputCon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    test = true;
    test_src = true;
    wire_Pos = simulation->mapFromGlobal(QCursor::pos());;
}

void OutputCon::InputToOutput()
{
    if(!(simulation->src_Gate == this->parent_Gate))
    {
        QBrush brush;
        brush.setColor(Qt::darkGreen);
        brush.setStyle(Qt::SolidPattern);
        this->setBrush(brush);
    }
}

void OutputCon::clearNode()
{
    QBrush brush;
    brush.setColor(Qt::red);
    brush.setStyle(Qt::SolidPattern);
    this->setBrush(brush);
}

void OutputCon::conNode()
{
    if(simulation->dest_Gate == this->parent_Gate || simulation->src_Gate == this->parent_Gate)
    {
        if(test == true)
        {
            //this->connected = true;
            QBrush brush;
            brush.setColor(Qt::black);
            brush.setStyle(Qt::SolidPattern);
            this->setBrush(brush);
        }
    }
}
