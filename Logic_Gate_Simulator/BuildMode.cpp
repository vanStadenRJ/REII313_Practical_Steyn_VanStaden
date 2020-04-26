#include "BuildMode.h"
#include "Simulation.h"

extern Simulation * simulation;

BuildMode::BuildMode(QGraphicsItem *parent): QGraphicsPixmapItem (parent)
{
    this->setPixmap(QPixmap(":/images/And_Icon.png"));
}

void BuildMode::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(simulation->build_mode == nullptr)
    {
        simulation->build_mode = new Gate();
        simulation->set_Cursor(QString(":/images/And_Icon.png"));
    }
}
