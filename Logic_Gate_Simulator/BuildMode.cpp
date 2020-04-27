#include "BuildMode.h"
#include "Simulation.h"

extern Simulation * simulation;

BuildMode::BuildMode(QGraphicsItem *parent): QGraphicsPixmapItem (parent)
{
    this->setPixmap(QPixmap(":/images/And_Icon.png"));
}

void BuildMode::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(simulation->isBuildMode == false)
    {
        simulation->isBuildMode = true;
        cur = QCursor(QPixmap(":/images/And_Gate.png"));
        //simulation->set_Cursor(QString(":/images/And_Icon.png"));
        simulation->setCursor(cur);
    }
}
