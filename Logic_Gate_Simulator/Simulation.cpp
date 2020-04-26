#include "Simulation.h"
#include "BuildMode.h"
//#include "Gate.h"

Simulation::Simulation()
{
    //Set scene and show on view
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,1000,800);
    this->setScene(scene);
    this->setFixedSize(1000,800);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

//    Gate * gate = new Gate();
//    gate->setPos(500,400);
//    scene->addItem(gate);

    //scene->addItem(gate->rect);

    // set cursor
    cursor = nullptr;
    build_mode = nullptr;
    this->setMouseTracking(true);

    BuildMode * ic = new BuildMode();
    scene->addItem(ic);
}

void Simulation::set_Cursor(QString filename)
{
    if(!(cursor == nullptr))
    {
        scene->removeItem(cursor);
        delete cursor;
    }
    cursor = new QGraphicsPixmapItem();
    cursor->setPixmap(QPixmap(filename));
    scene->addItem(cursor);
}

void Simulation::mouseMoveEvent(QMouseEvent *event)
{
    if (!(cursor==nullptr))
    {
        cursor->setPos(event->pos());
    }
}

void Simulation::mousePressEvent(QMouseEvent *event)
{
    if(build_mode)
    {
        scene->addItem(build_mode);
        build_mode->setPos(event->pos());
        delete cursor;
        this->scene->removeItem(cursor);
        cursor = nullptr;
        build_mode = nullptr;
    }
    else {
        QGraphicsView::mousePressEvent(event);
    }
}
