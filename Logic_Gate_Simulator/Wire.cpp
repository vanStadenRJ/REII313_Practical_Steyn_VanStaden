#include "Wire.h"
#include "Simulation.h"

#include <QPen>
#include <QDebug>

extern Simulation * simulation;

Wire::Wire()
{
    QPen pen;
    pen.setWidth(5);
    pen.setCapStyle(Qt::RoundCap);
    this->setPen(pen);

    effect = nullptr;
    QObject::connect(simulation, SIGNAL(unWire()), this, SLOT(deleteEffect()));
    this->setFlag(QGraphicsItem::ItemIsFocusable);
}

void Wire::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setFocus();
    if(effect == nullptr)
    {
        effect = new QGraphicsDropShadowEffect();
        if(event->button() == Qt::LeftButton)
        {
            effect->setEnabled(true);
            effect->setColor(Qt::lightGray);
            effect->setOffset(8);
            this->setGraphicsEffect(effect);
            this->setFocus();

            QPen pen;
            pen.setWidth(6);
            pen.setCapStyle(Qt::RoundCap);
            this->setPen(pen);
        }        
        qDebug() << this->src_Gate << "(" << src_NodeNr << ")"
                 << "->" << this->dest_Gate << "(" << dest_NodeNr << ")"
                 <<" logic: " << this->Logic_Wire;
    }
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

        //simulation->updateWireLogic();
        // Upon Delete of Wire, Remove Wire from list of wires
        for(int v = 0; v < simulation->list_Wires.size(); v++)
        {
            if(simulation->list_Wires.at(v)->source == this->source && simulation->list_Wires.at(v)->dest == this->dest)
            {
                simulation->list_Wires.takeAt(v);
                qDebug() << "Amount of wires: " << simulation->list_Wires.size();
                break;
            }
        }

//        for(int v = 0; v < simulation->list_Gates.size(); v++)
//        {
//            simulation->list_Gates.at(v)->updateLogic();
//        }

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
        this->setGraphicsEffect(effect);
        effect = nullptr;
        this->clearFocus();

        QPen pen;
        pen.setWidth(5);
        pen.setCapStyle(Qt::RoundCap);
        this->setPen(pen);
    }
}
