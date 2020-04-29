#include "Simulation.h"
#include "BuildMode.h"
#include "OutputCon.h"
#include "Wire.h"

//#include "Gate.h"
#include <QDebug>
#include <QCursor>

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

    if(isBuildMode)
    {
        if(event->button() == Qt::LeftButton)
        {
            qDebug() << "yeet|;";
            gate = new Gate();
            scene->addItem(gate);
            gate->setPos(event->pos());
            isBuildMode = false;
            QCursor def = QCursor();
            def.setShape(Qt::ArrowCursor);
            this->setCursor(def);

            //scene->removeItem(gate);
            //delete(gate);
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
            scene->addItem(move_wire);
            canMove = true;
            emit clicked();
        }
        else
        {
            if(event->button() == Qt::LeftButton)
            {
                wire = new Wire();
                wire->source = move_wire->source;
                wire->dest = move_wire->dest;
                QLineF line;
                line.setPoints(move_wire->source, move_wire->dest);
                wire->setLine(line);
                scene->addItem(wire);
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

            //scene->removeItem(move_wire);
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
    else {
        QGraphicsView::mouseMoveEvent(event);
    }

}
