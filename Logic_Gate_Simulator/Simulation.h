#ifndef SIMULATION_H
#define SIMULATION_H

#include <QGraphicsScene>
#include <QGraphicsView>

class Simulation: public QGraphicsView
{
public:
    Simulation();

    QGraphicsScene * scene;
};

#endif // SIMULATION_H
