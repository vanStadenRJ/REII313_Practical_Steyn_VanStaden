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
        this->viewPix = this->pixmap();
        this->isNot = false;
        break;

    case 2:     // 2 = High Input
        this->setPixmap(QPixmap(":/images/High_Icon.png"));
        this->cur = this->pixmap();
        this->viewPix = this->pixmap();
        this->isNot = false;
        break;

    case 3:     // 3 = AND Gate
        this->setPixmap(QPixmap(":/images/And_Icon.png"));
        this->cur = QCursor(QPixmap(":/images/And_Gate.png"));
        this->viewPix = QPixmap(":/images/And_Gate_View.png");
        this->isNot = false;
        break;

    case 4:     // 4 = NAND Gate
        this->setPixmap(QPixmap(":/images/Nandd_Icon.png"));
        this->cur = QCursor(QPixmap(":/images/Nand_Gate.png"));
        this->viewPix = QPixmap(":/images/And_Gate_View.png");
        this->isNot = true;
        break;

    case 5:     // 5 = OR Gate
        this->setPixmap(QPixmap(":/images/Or_Icon.png"));
        this->cur = QCursor(QPixmap(":/images/Or_Gate.png"));
        this->viewPix = QPixmap(":/images/Or_Gate_View.png");
        this->isNot = false;
        break;

    case 6:     // 6 = NOR Gate
        this->setPixmap(QPixmap(":/images/Nor_Icon.png"));
        this->cur = QCursor(QPixmap(":/images/Nor_Gate.png"));
        this->viewPix = QPixmap(":/images/Or_Gate_View.png");
        this->isNot = true;
        break;

    case 7:     // 7 = XOR Gate
        this->setPixmap(QPixmap(":/images/XOR_Icon.png"));
        this->cur = QCursor(QPixmap(":/images/XOR_Gate.png"));
        this->viewPix = QPixmap(":/images/XOR_Gate_View.png");
        this->isNot = false;
        break;

    case 8:     // 8 = XNOR Gate
        this->setPixmap(QPixmap(":/images/XNOR_Icon.png"));
        this->cur = QCursor(QPixmap(":/images/XNOR_Gate.png"));
        this->viewPix = QPixmap(":/images/XOR_Gate_View.png");
        this->isNot = true;
        break;

    case 9:     // 9 = NOT Gate
        this->setPixmap(QPixmap(":/images/NOT_Icon.png"));
        this->cur = QCursor(QPixmap(":/images/NOT_Gate.png"));
        this->viewPix = QPixmap(":/images/NOT_Gate_View.png");
        this->isNot = true;
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
        simulation->viewPix = this->viewPix;
        simulation->isNot = this->isNot;
        simulation->setCursor(cur);
    }
}
