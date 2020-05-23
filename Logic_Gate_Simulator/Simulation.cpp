#include "Simulation.h"
#include "OutputCon.h"
#include "Wire.h"

#include <QMainWindow>
#include <QDebug>
#include <QCursor>
#include <QList>

Simulation::Simulation(QWidget * parent)
{
    //Set scene and show on view
    this->setSceneRect(0,0,1000,800);
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,1000,800);
    this->setScene(scene);
    this->setFixedSize(1000,800);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // set cursor
    isBuildMode = false;
    isMove = false;
    wireMode = false;
    move_wire = nullptr;
    this->setMouseTracking(true);

    andIcon = new BuildMode(1);
    scene->addItem(andIcon);
    andIcon->setPos(0,0);

    highIcon = new BuildMode(2);
    scene->addItem(highIcon);
    highIcon->setPos(100,0);

    lowIcon = new BuildMode(3);
    scene->addItem(lowIcon);
    lowIcon->setPos(200,0);

    canMove = false;
    nr_Gates = 0;
    nr_Wires = 0;

    Output = true;
}

void Simulation::mousePressEvent(QMouseEvent *event)
{
    if(!(gate == nullptr))
    {
        emit un_Select();
    }

    if(!(wire == nullptr))
    {
        emit unWire();
    }

    if(isBuildMode)
    {
        if(event->button() == Qt::LeftButton)
        {
            this->nr_Gates = this->nr_Gates + 1;
            gate = new Gate(this->nr_Gates, this->typeIcon);
            scene->addItem(gate);
            gate->setPos(event->x()-gate->pixmap().width()/2, event->y() -
                         gate->pixmap().height()/2);
            gate->pos_Gate = gate->pos();
            list_Gates << gate;
            isBuildMode = false;

            QCursor def = QCursor();
            def.setShape(Qt::ArrowCursor);
            this->setCursor(def);
        }
        else if (event->button() == Qt::RightButton)
        {
            QCursor def = QCursor();
            def.setShape(Qt::ArrowCursor);
            this->setCursor(def);
            isBuildMode = false;            
        }
    }
    else
    {
        QGraphicsView::mousePressEvent(event);
    }

    if(isMove)
    {
        for(int i = 0; i < list_Gates.size(); i++)
        {
            if(list_Gates.at(i)->gate_Nr == this->moveGate)
            {
                list_Gates.at(i)->setPos(event->x()-list_Gates.at(i)->pixmap()
                                         .width()/2, event->y() - list_Gates.at(i)
                                         ->pixmap().height()/2);
                QPointF dif;
                dif = list_Gates.at(i)->pos() - list_Gates.at(i)->pos_Gate;
                list_Gates.at(i)->pos_Gate = list_Gates.at(i)->pos();
                QLineF line;
                for(int j = 0; j < list_Wires.size(); j++)
                {
                    if(list_Wires.at(j)->src_Gate == this->moveGate)
                    {
                        list_Wires.at(j)->source = list_Wires.at(j)->source + dif;
                        line.setPoints(list_Wires.at(j)->source, list_Wires.at(j)->dest);
                        list_Wires.at(j)->setLine(line);
                    }
                    else
                    {
                        if(list_Wires.at(j)->dest_Gate == this->moveGate)
                        {
                            list_Wires.at(j)->dest = list_Wires.at(j)->dest + dif;
                            line.setPoints(list_Wires.at(j)->source, list_Wires.at(j)->dest);
                            list_Wires.at(j)->setLine(line);
                        }
                    }
                }
                this->setCursor(Qt::ArrowCursor);
                isMove = false;
            }
        }

    }


    if(wireMode)
    {
        if(move_wire == nullptr)
        {
            qDebug() << "Wire";
            move_wire = new Wire();
            move_wire->source = this->mapFromGlobal(QCursor::pos());
            qDebug() << move_wire->source;

            scene->addItem(move_wire);
            canMove = true;

            if(this->Output == true)
            {
                emit Input_Show();
            }
            else
            {
                emit Output_Show();
            }
            emit clicked();
        }
        else
        {
            if(event->button() == Qt::LeftButton)
            {
                QGraphicsView::mousePressEvent(event);
                wire = new Wire();
                wire->source = move_wire->source;
                wire->dest = move_wire->dest;
                wire->src_Gate = this->src_Gate;
                wire->dest_Gate = this->dest_Gate;
                wire->src_NodeNr = this->src_NodeNr;
                wire->dest_NodeNr = this->dest_NodeNr;

                for(int g = 0; g < list_Gates.size(); g++)
                {
                    if(list_Gates.at(g)->gate_Nr == wire->src_Gate)
                    {
                        wire->Logic_Wire = list_Gates.at(g)->LogicalOutput;
                        qDebug() << "Gate " << list_Gates.at(g)->gate_Nr << " found!";
                        break;
                    }
                }
                //emit connected_Node();
                QLineF line;
                line.setPoints(move_wire->source, move_wire->dest);
                wire->setLine(line);
                scene->addItem(wire);
                list_Wires << wire;
                qDebug() << "Amount of wires: " << list_Wires.size();
                nr_Wires++;
                emit connected_Node(wire->Logic_Wire);
                this->setCursor(Qt::ArrowCursor);            
                this->updateWireLogic();
            }
            else
            {
                emit clear_Node();
            }
            canMove = false;
            scene->removeItem(move_wire);
            move_wire = nullptr;
            delete move_wire;
            wireMode = false;
        }
    }
    else
    {
        QGraphicsView::mousePressEvent(event);
        if (!(move_wire == nullptr))
        {
            canMove = false;
            scene->removeItem(move_wire);
            move_wire = nullptr;
            emit clear_Node();

            delete move_wire;
            wireMode = false;
        }
    }
}

void Simulation::mouseMoveEvent(QMouseEvent *event)
{
    if(canMove == true)
    {
        QGraphicsView::mousePressEvent(event);
        move_wire->dest = this->mapFromGlobal(QCursor::pos());
        QLineF line;
        line.setPoints(move_wire->source, move_wire->dest);
        move_wire->setLine(line);
        scene->update();
    }
    else {
        QGraphicsView::mouseMoveEvent(event);
    }
}

void Simulation::updateWireLogic()
{
    for(int v = 0; v < list_Gates.size(); v++)
    {
        list_Gates.at(v)->updateLogic();
    }

    for(int v = 0; v < list_Wires.size(); v++)
    {
        for(int b = 0; b < list_Gates.size(); b++)
        {
            if(list_Gates.at(b)->gate_Nr == list_Wires.at(v)->src_Gate)
            {
                list_Wires.at(v)->Logic_Wire = list_Gates.at(b)->LogicalOutput;
            }
        }
    }

    for(int v = 0; v < list_Gates.size(); v++)
    {
        for(int b = 0; b < list_Gates.at(v)->list_Inputs.size(); b++)
        {
            for(int c = 0; c < list_Wires.size(); c++)
            {
                if(list_Wires.at(c)->dest_NodeNr == list_Gates.at(v)->list_Inputs.at(b)->posGate)
                {
                    list_Gates.at(v)->list_Inputs.at(b)->Logic = list_Wires.at(c)->Logic_Wire;
                }
            }
        }
        list_Gates.at(v)->updateLogic();
    }
}
