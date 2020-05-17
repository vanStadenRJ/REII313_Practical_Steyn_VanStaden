#include "BuildMode.h"
#include "Simulation.h"
#include "mainwindow.h"

extern Simulation * simulation;
//MainWindow * mw;

BuildMode::BuildMode(uint typeIcon)
{
    // All gates share same Icon class
    this->Icon = typeIcon;
    switch(Icon)
    {
    case 1:     // 1 = and gate
        this->setPixmap(QPixmap(":/images/And_Icon.png"));
        break;

    case 2:     // 2 = High Input
        this->setPixmap(QPixmap(":/images/High_Icon.png"));
        break;

    case 3:     // 3 = Low Input
        this->setPixmap(QPixmap(":/images/Low_Icon.png"));
        break;
    }

}

void BuildMode::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // If clicked, buildmode entered to be placed on QGraphicsView    
    if(simulation->isBuildMode == false)
    {
        simulation->isBuildMode = true;        
        switch(Icon)
        {
        case 1:     // 1 = and gate
            cur = QCursor(QPixmap(":/images/And_Gate.png"));
            simulation->typeIcon = 1;
            break;

        case 2:     // 2 = High Input
            cur = QCursor(QPixmap(":/images/High_Icon.png"));
            simulation->typeIcon = 2;
            break;

        case 3:
            cur = QCursor(QPixmap(":/images/Low_Icon.png"));
            simulation->typeIcon = 3;
            break;
        }
        simulation->setCursor(cur);
    }
}
