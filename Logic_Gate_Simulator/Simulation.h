#ifndef SIMULATION_H
#define SIMULATION_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include <QString>
#include <QObject>
#include <QPainter>
#include <QPaintEvent>

#include "Gate.h"

// Our main workspace will be Simulation which inherits from QGraphicsView
class Simulation: public QGraphicsView
{
    Q_OBJECT
public:
    //Member Functions
    Simulation();
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);

    //Member Attributes
    QGraphicsScene * scene;
    Gate * gate;
    Wire * wire;
    Wire * move_wire;

    bool isBuildMode;
    bool wireMode;
    bool canMove;

signals:
    void clicked();
    void un_Select();
};

#endif // SIMULATION_H
