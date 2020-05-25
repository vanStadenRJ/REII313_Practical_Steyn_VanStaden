#include "Simulation.h"
#include "OutputCon.h"
#include "Wire.h"

#include <QMainWindow>
#include <QCursor>
#include <QDebug>
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

    for(int i = 1; i <= 4; i++)
    {
        andIcon = new BuildMode(i);
        scene->addItem(andIcon);
        andIcon->setPos((i-1)*100,0);
    }

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
            for(int j = 0; j < list_Gates.size(); j++)
            {
                list_Gates.at(j)->setCenterPos();
            }
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
        return;
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
        return;
    }


    if(wireMode)
    {
        if(move_wire == nullptr)
        {
            qDebug() << "Wire";
            move_wire = new Wire();
            move_wire->source = this->sourceNode;
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
                wire->dest = this->destNode;
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

                QLineF line;
                line.setPoints(wire->source, wire->dest);
                wire->setLine(line);
                scene->addItem(wire);
                list_Wires << wire;
                qDebug() << "Amount of wires: " << list_Wires.size();
                nr_Wires++;
                emit connected_Node(wire->Logic_Wire, wire->src_Gate);
                this->setCursor(Qt::ArrowCursor);            
                this->updateWireLogic();

                emit clear_Node(false, 0, 0);
            }
            else
            {
                emit clear_Node(false, 0, 0);
            }
            canMove = false;
            scene->removeItem(move_wire);
            move_wire = nullptr;
            delete move_wire;           
            wireMode = false;
        }
        return;
    }
    else
    {
        QGraphicsView::mousePressEvent(event);
        if (!(move_wire == nullptr))
        {
            canMove = false;
            scene->removeItem(move_wire);
            move_wire = nullptr;
            emit clear_Node(false, 0, 0);

            delete move_wire;
            wireMode = false;
        }
    }
}

void Simulation::mouseMoveEvent(QMouseEvent *event)
{
    if(canMove == true)
    {        
        move_wire->dest = this->mapFromGlobal(QCursor::pos());
        QLineF line;
        line.setPoints(move_wire->source, move_wire->dest);
        move_wire->setLine(line);
        scene->update();
    }

    // Enable default QGraphicsView mousePressEvent()
    QGraphicsView::mousePressEvent(event);
}

void Simulation::updateWireLogic()
{
    // Update gate logic on current logic of inputs
    emit changeGateLogic();

    // Update logic of each wire
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

    // Update Logic of all Inputs
    emit changeInputLogic();

    // Update Logic of all gates
    emit changeGateLogic();

    // Only change color logic of wire if there are wires
    if(!(this->list_Wires.size() == 0))
    {
        emit changeWireColor();
    }
}
