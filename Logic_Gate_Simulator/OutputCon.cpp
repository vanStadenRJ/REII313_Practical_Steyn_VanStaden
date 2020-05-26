#include "Simulation.h"
#include "OutputCon.h"
#include "Wire.h"
#include "Gate.h"

extern Simulation * simulation;

OutputCon::OutputCon(QGraphicsItem * parent): QGraphicsEllipseItem(parent)
{
    this->setRect(0,0,12,12);
    this->setZValue(2);
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

    QObject::connect(simulation, SIGNAL(Output_Show()), this, SLOT(InputToOutput()));
    //QObject::connect(simulation, SIGNAL(clear_Node()), this, SLOT(clearNode()));
    //QObject::connect(simulation,SIGNAL(connected_Node(int)), this, SLOT(conNode()));
}

void OutputCon::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{    
    if((connected == false && simulation->isBuildMode == false && simulation->isMove == false) && (simulation->move_wire == nullptr))
    //if(simulation->move_wire == nullptr)
    {
        //Change color
        this -> setRect(0,0,13,13);
        //this->setPen(QPen)
        //this->paint();

        QBrush brush;
        brush.setColor(Qt::black);
        brush.setStyle(Qt::SolidPattern);
        this->setBrush(brush);

        effect = new QGraphicsDropShadowEffect();
        effect->setEnabled(true);
        effect->setColor(Qt::lightGray);
        effect->setOffset(6);
        this->setGraphicsEffect(effect);

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
        simulation->sourceNode = this->centerPoint;
    }
}

void OutputCon::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
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

    effect->setEnabled(false);
}

void OutputCon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    test = true;
    test_src = true;
    wire_Pos = simulation->mapFromGlobal(QCursor::pos());;
}

//void OutputCon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
//{
//    painter->setBrush(QColor(255,255,255));

//    QPen pen;
//    pen.setWidth(2);
//    painter->setPen(pen);
//    painter->drawEllipse(0,0,12,12);
//}

void OutputCon::InputToOutput()
{
    if(!(simulation->src_Gate == this->parent_Gate))
    {
        if(this->connected == false)
        {
            QBrush brush;
            brush.setColor(Qt::darkGreen);
            brush.setStyle(Qt::SolidPattern);
            this->setBrush(brush);
        }
    }
}

//void OutputCon::clearNode()
//{
//    //
//}

//void OutputCon::conNode()
//{
//    if(simulation->dest_Gate == this->parent_Gate || simulation->src_Gate == this->parent_Gate)
//    {
//        if(test == true)
//        {
//            //this->connected = true;
//            QBrush brush;
//            brush.setColor(Qt::black);
//            brush.setStyle(Qt::SolidPattern);
//            this->setBrush(brush);
//        }
//    }
//}
