#ifndef GATE_H
#define GATE_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>

#include "Simulation.h"

extern Simulation * simulation;

class Gate: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Gate(QGraphicsItem * parent = 0);
    QGraphicsRectItem *rect;
    QGraphicsEllipseItem *circle;

private:


public slots:

};

#endif // GATE_H
