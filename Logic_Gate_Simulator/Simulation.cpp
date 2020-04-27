#include "Simulation.h"
#include "BuildMode.h"
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
    this->setMouseTracking(true);

    BuildMode * ic = new BuildMode();
    scene->addItem(ic);
}

void Simulation::mousePressEvent(QMouseEvent *event)
{
    if(isBuildMode)
    {
        if(event->button() == Qt::LeftButton)
        {
            qDebug() << "yeet|;";
            gate = new Gate();
            scene->addItem(gate);
            gate->setPos(event->pos());
            //gate = nullptr;
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
    else {
        QGraphicsView::mousePressEvent(event);
    }
}
