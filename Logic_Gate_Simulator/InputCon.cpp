#include "InputCon.h"
#include "Simulation.h"
extern Simulation * simulation;

InputCon::InputCon(QGraphicsItem *parent): QGraphicsEllipseItem (parent)
{
    posGate = 0;
    Logic = 0;
    setRect(0,0,12,12);
    QBrush brush;
    brush.setColor(QColor(255,255,255));
    brush.setStyle(Qt::SolidPattern);
    this->setBrush(brush);

    //ALLOW RESPONDING TO HOVER EVENTS
    this->setAcceptHoverEvents(true);
    connected = false;
    Logic = 0;
    test = false;

    QObject::connect(simulation, SIGNAL(Input_Show()), this, SLOT(OutputToInput()));
    QObject::connect(simulation, SIGNAL(clear_Node(bool, int, int)), this, SLOT(clearNode(bool, int, int)));
    QObject::connect(simulation,SIGNAL(connected_Node(int, int)), this, SLOT(conNode(int, int)));
    QObject::connect(simulation, SIGNAL(changeInputLogic()), this, SLOT(getWireLogic()));
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
    else
    {
        qDebug() << "Gate Nr: " << this->parent_Gate << "; Node Nr: " << this->posGate << " Logig: " << Logic << " Con Gate: " << conGate;
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
            this->setBrush(QColor(255,255,255));
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

void InputCon::clearNode(bool gate, int g, int h)
{
    if(gate == true)
    {
        if(g == conGate && h == posGate)
        {
            this->setBrush(QColor(255,255,255));
            this->Logic = 0;
            this->connected = false;
        }
    }
    else
    {
        if(this->connected == false)
        {
            this->setBrush(QColor(255,255,255));
            this->Logic = 0;
            this->connected = false;
        }
    }
}

void InputCon::getWireLogic()
{
    if(this->connected == true)
    {
        for(int i = 0; i < simulation->list_Wires.size(); i++)
        {
            if(simulation->list_Wires.at(i)->dest_NodeNr == this->posGate && this->parent_Gate == simulation->list_Wires.at(i)->dest_Gate)
            {
                this->Logic = simulation->list_Wires.at(i)->Logic_Wire;
                return;
            }
        }
    }
    else
    {
        Logic = 0;
        return;
    }
}

void InputCon::conNode(int k, int h)
{
    if(simulation->dest_Gate == this->parent_Gate || simulation->src_Gate == this->parent_Gate)
    {
        if(test == true)
        {
            this->connected = true;
            QBrush brush;
            brush.setColor(Qt::white);
            brush.setStyle(Qt::SolidPattern);
            this->setBrush(brush);
            qDebug() << k;
            this->Logic = k;
            this->conGate = h;
            test = false;
        }
    }
}
