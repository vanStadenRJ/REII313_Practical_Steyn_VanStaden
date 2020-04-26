#include "Simulation.h"
#include "Gate.h"

Simulation::Simulation()
{
    //Set scene and show on view
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,1000,800);
    this->setScene(scene);
    this->setFixedSize(1000,800);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QGraphicsRectItem * rect = new QGraphicsRectItem();
    rect->setRect(0,0,100,100);
    scene->addItem(rect);

    Gate * gate = new Gate();
    gate->setPos(500,400);
    scene->addItem(gate);

    scene->addItem(gate->rect);


}
