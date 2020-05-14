#include "Simulation.h"
#include "BuildMode.h"
#include "OutputCon.h"
#include "Wire.h"

//#include "Gate.h"
#include <QDebug>
#include <QCursor>
#include <QList>

Simulation::Simulation()
{
    //Set scene and show on view
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,1000,800);
    this->setScene(scene);
    this->setFixedSize(1000,800);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // set cursor
    isBuildMode = false;
    wireMode = false;
    move_wire = nullptr;
    this->setMouseTracking(true);

    BuildMode * ic = new BuildMode();
    scene->addItem(ic);

    canMove = false;
    nr_Gates = 0;
    nr_Wires = 0;

    Output = true;
}

void Simulation::mousePressEvent(QMouseEvent *event)
{
//    if(isBuildMode || wireMode)
//    {
//        if(isBuildMode)
//        {
//            if(event->button() == Qt::LeftButton)
//            {
//                qDebug() << "yeet|;";
//                gate = new Gate();
//                scene->addItem(gate);
//                gate->setPos(event->pos());
//                gate->Output();
//                isBuildMode = false;
//                QCursor def = QCursor();
//                def.setShape(Qt::ArrowCursor);
//                this->setCursor(def);
//            }
//            else if (event->button() == Qt::RightButton)
//            {
//                QCursor def = QCursor();
//                def.setShape(Qt::ArrowCursor);
//                this->setCursor(def);
//                isBuildMode = false;
//            }
//        }
//        else if(wireMode)
//        {
//            if(move_wire == nullptr)
//            {
//                qDebug() << "Wire";
//                move_wire = new Wire();
//                move_wire->source = this->mapFromGlobal(QCursor::pos());
//                scene->addItem(move_wire);
//                canMove = true;
//                emit clicked();
//            }
//            else
//            {
//                if(event->button() == Qt::LeftButton)
//                {
//                    wire = new Wire();
//                    wire->source = move_wire->source;
//                    wire->dest = move_wire->dest;
//                    QLineF line;
//                    line.setPoints(move_wire->source, move_wire->dest);
//                    wire->setLine(line);
//                    scene->addItem(wire);
//                }
//                canMove = false;
//                scene->removeItem(move_wire);
//                move_wire = nullptr;
//                delete move_wire;
//                wireMode = false;
//            }
//        }
//    }
//    else
//    {
//        QGraphicsView::mousePressEvent(event);
//        if (!(move_wire == nullptr))
//        {
//            canMove = false;
//            scene->removeItem(move_wire);
//            move_wire = nullptr;

//            //scene->removeItem(move_wire);
//            delete move_wire;
//            wireMode = false;
//        }
//    }

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
            gate = new Gate(this->nr_Gates);
            scene->addItem(gate);            
            gate->setPos(event->pos());
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

    if(wireMode)
    {
        if(move_wire == nullptr)
        {
            qDebug() << "Wire";
            move_wire = new Wire();
            move_wire->source = this->mapFromGlobal(QCursor::pos());
            qDebug() << move_wire->source;
//            for(int g = 0; g < list_Gates.size(); g++)
//            {
//                for(int h = 0; h < list_Gates.at(g)->list_Outputs.size(); h++)
//                {
//                    if(list_Gates.at(g)->list_Outputs.at(g)->)
//                }
//            }



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
                nr_Wires++;
                emit connected_Node(wire->Logic_Wire);
                this->setCursor(Qt::ArrowCursor);
                for(int g = 0; g < list_Gates.size(); g++)
                {
                    list_Gates.at(g)->updateLogic();
                }
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
