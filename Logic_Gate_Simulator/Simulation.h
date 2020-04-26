#ifndef SIMULATION_H
#define SIMULATION_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>

// Our main workspace will be Simulation which inherits from QGraphicsView
class Simulation: public QGraphicsView
{
public:
    //Member Functions
    Simulation();    

    //Member Attributes
    QGraphicsScene * scene;
};

#endif // SIMULATION_H
