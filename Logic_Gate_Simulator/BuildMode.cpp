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
    case 1:     // 1 = Low Input
        this->setPixmap(QPixmap(":/images/Low_Icon.png"));
        this->cur = this->pixmap();
        break;

    case 2:     // 2 = High Input
        this->setPixmap(QPixmap(":/images/High_Icon.png"));
        this->cur = this->pixmap();
        break;

    case 3:     // 3 = AND Gate
        this->setPixmap(QPixmap(":/images/And_Icon.png"));
        this->cur = QCursor(QPixmap(":/images/And_Gate.png"));
        break;

    case 4:     // 4 = NAND Gate
        this->setPixmap(QPixmap(":/images/Nandd_Icon.png"));
        this->cur = QCursor(QPixmap(":/images/Nand_Gate.png"));
        break;

    case 5:     // 5 = OR Gate
        this->setPixmap(QPixmap(":/images/Or_Icon.png"));
        this->cur = QCursor(QPixmap(":/images/Or_Gate.png"));
        break;

    case 6:     // 6 = NOR Gate
        this->setPixmap(QPixmap(":/images/Nor_Icon.png"));
        this->cur = QCursor(QPixmap(":/images/Nor_Gate.png"));
        break;

    case 7:     // 7 = XOR Gate
        this->setPixmap(QPixmap(":/images/XOR_Icon.png"));
        this->cur = QCursor(QPixmap(":/images/XOR_Gate.png"));
        break;

    case 8:     // 8 = XNOR Gate
        this->setPixmap(QPixmap(":/images/XNOR_Icon.png"));
        this->cur = QCursor(QPixmap(":/images/XNOR_Gate.png"));
        break;

    case 9:     // 9 = NOT Gate
        this->setPixmap(QPixmap(":/images/NOT_Icon.png"));
        this->cur = QCursor(QPixmap(":/images/NOT_Gate.png"));
        break;
    }
}

void BuildMode::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // If clicked, buildmode entered to be placed on QGraphicsView    
    if(simulation->isBuildMode == false)
    {
        simulation->isBuildMode = true;
        simulation->typeIcon = this->Icon;
        simulation->setCursor(cur);
    }
}
