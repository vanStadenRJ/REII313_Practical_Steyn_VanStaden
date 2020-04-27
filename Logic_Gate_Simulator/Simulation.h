#ifndef SIMULATION_H
#define SIMULATION_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include <QString>

#include "Gate.h"

// Our main workspace will be Simulation which inherits from QGraphicsView
class Simulation: public QGraphicsView
{
public:
    //Member Functions
    Simulation();
    void mousePressEvent(QMouseEvent * event);

    //Member Attributes
    QGraphicsScene * scene;
    Gate * gate;

    bool isBuildMode;
};

#endif // SIMULATION_H
