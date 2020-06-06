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

    //ALLOW RESPONDING TO HOVER EVENTS
    this->setAcceptHoverEvents(true);
    connected = false;
    test = false;
    test_src = false;

    QBrush brush;
    brush.setColor(QColor(255,255,255));
    brush.setStyle(Qt::SolidPattern);
    this->setBrush(brush);
}

void OutputCon::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    //this->setToolTip(QString("Yeet"));
    if((connected == false && simulation->isBuildMode == false && simulation->isMove == false) && (simulation->move_wire == nullptr))
    {
        //Change color
        this -> setRect(0,0,13,13);

        QBrush brush;
        brush.setColor(Qt::black);
        brush.setStyle(Qt::SolidPattern);
        this->setBrush(brush);

        test = true;
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
    this->setToolTip(QString(""));
    this -> setRect(0,0,12,12);
    if(connected == false && simulation->isBuildMode == false && simulation->isMove == false)
    {
        if(test_src == false)
        {
            test = false;
            //this->setBrush(Qt::NoBrush);
            QBrush brush;
            brush.setColor(QColor(255,255,255));
            brush.setStyle(Qt::SolidPattern);
            this->setBrush(brush);
        }
        simulation->setCursor(Qt::ArrowCursor);
        simulation->wireMode = false;
    }
    QBrush brush;
    brush.setColor(QColor(255,255,255));
    brush.setStyle(Qt::SolidPattern);
    this->setBrush(brush);
}

void OutputCon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    test = true;
    test_src = true;
    wire_Pos = simulation->mapFromGlobal(QCursor::pos());;
}
