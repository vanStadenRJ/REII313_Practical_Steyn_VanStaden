#include "Simulation.h"
#include "mainwindow.h"
#include "BuildMode.h"

extern Simulation * simulation;

BuildMode::BuildMode(int typeIcon)
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

    case 4:     // 4 = Nand Gate
        this->setPixmap(QPixmap(":/images/Nandd_Icon.png"));
        break;

    case 5:
        this->setPixmap(QPixmap(":/images/Or_Icon.png"));
        break;

    case 6:
        this->setPixmap(QPixmap(":/images/Nor_Icon.png"));
        break;

    case 7:
        this->setPixmap(QPixmap(":/images/XOR_Icon.png"));
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

        case 4:
            cur = QCursor(QPixmap(":/images/Nand_Gate.png"));
            simulation->typeIcon = 4;
            break;

        case 5:
            cur = QCursor(QPixmap(":/images/Or_Gate.png"));
            simulation->typeIcon = 5;
            break;

        case 6:
            cur = QCursor(QPixmap(":/images/Nor_Gate.png"));
            simulation->typeIcon = 6;
            break;

        case 7:
            cur = QCursor(QPixmap(":/images/XOR_Gate.png"));
            simulation->typeIcon = 7;
            break;
        }
        simulation->setCursor(cur);
    }
}
