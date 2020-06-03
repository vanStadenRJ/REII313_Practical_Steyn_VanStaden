#include "Wire.h"
#include "Simulation.h"

#include <QDebug>
#include <QPen>

extern Simulation * simulation;

Wire::Wire()
{
    // Set ZValue to 0 to enable wire to be under the input nodes
    setZValue(0);

    QPen pen;
    pen.setWidth(5);
    pen.setCapStyle(Qt::RoundCap);
    pen.setColor(Qt::magenta);
    this->setPen(pen);

    effect = nullptr;

    // Connect Signals and Slots
    QObject::connect(simulation, SIGNAL(unWire()), this, SLOT(deleteEffect()));
    QObject::connect(simulation, SIGNAL(changeWireColor()), this, SLOT(colorLogic()));

    // Item can respond to keypress event
    this->setFlag(QGraphicsItem::ItemIsFocusable);
}

void Wire::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPainterPath outline;

    outline.moveTo(line().p1());
    outline.lineTo(line().p2());

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    QPen pen1;
    pen1.setColor(QColor(0,0,0));
    pen1.setWidth(4 + pen().width());
    pen1.setCapStyle(Qt::RoundCap);
    painter->strokePath(outline, pen1);
    painter->setPen(pen());
    pen().setCapStyle(Qt::RoundCap);
    painter->drawLine(line());
    painter->restore();
}

void Wire::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug() << "Wire: " << this->Logic_Wire;
    this->setFocus();
    if(effect == nullptr)
    {
        effect = new QGraphicsDropShadowEffect();
        if(event->button() == Qt::LeftButton)
        {
            effect->setEnabled(true);
            effect->setColor(Qt::lightGray);
            effect->setOffset(8);
        }        
    }
    else
    {
        effect->setEnabled(true);
    }
    this->setFocus();
    this->setGraphicsEffect(effect);
}

void Wire::keyPressEvent(QKeyEvent *event)
{
    if(effect->isEnabled() && event->key() == Qt::Key_Delete)
    {
        simulation->nr_Wires = simulation->nr_Wires - 1;
        bool bFound = false;
        int i = 0;

        while(bFound == false)
        {
            //int n = simulation->list_Gates.at(i)->list_Inputs.size();
            if(simulation->list_Gates.at(i)->gate_Nr == this->dest_Gate)
            {
                for(int j = 0; j < simulation->list_Gates.at(i)->list_Inputs.size(); j++)
                {
                    if(simulation->list_Gates.at(i)->list_Inputs.at(j)->posGate == this->dest_NodeNr)
                    {
                        bFound = true;
                        simulation->list_Gates.at(i)->list_Inputs.at(j)->connected = false;
                        QBrush brush;

                        //emit simulation->clear_Node();
                        simulation->list_Gates.at(i)->list_Inputs.at(j)->setBrush(brush);
                        simulation->list_Gates.at(i)->list_Inputs.at(j)->Logic = 0;
                        //delete this;
                        //return;
                    }
                }
            }
            i++;
        }

        // Upon Delete of Wire, Remove Wire from list of wires
        for(int v = 0; v < simulation->list_Wires.size(); v++)
        {
            if(simulation->list_Wires.at(v)->source == this->source && simulation->list_Wires.at(v)->dest == this->dest)
            {
                simulation->list_Wires.takeAt(v);
                //qDebug() << "Amount of wires: " << simulation->list_Wires.size();
                break;
            }
        }

        simulation->updateWireLogic();

        delete this;
        return;
    }
}

void Wire::deleteEffect()
{
    if (!(effect == nullptr))
    {
        effect->setEnabled(false);
        //this->clearFocus();
    }
}

void Wire::colorLogic()
{
    if(this->Logic_Wire == 1)
    {
        QPen pen;
        pen.setColor(QColor(0,75,200));
        pen.setWidth(5);
        pen.setCapStyle(Qt::RoundCap);
        this->setPen(pen);
    }
    else
    {
        QPen pen;
        pen.setColor(QColor(255,255,255));
        pen.setWidth(5);
        pen.setCapStyle(Qt::RoundCap);
        this->setPen(pen);
    }
}
