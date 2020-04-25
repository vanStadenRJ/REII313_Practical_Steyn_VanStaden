#include "Simulation.h"

Simulation::Simulation()
{
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,1000,800);
    this->setScene(scene);
}
