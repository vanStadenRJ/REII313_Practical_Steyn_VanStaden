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
    bool Output;

    bool isBuildMode;
    bool wireMode;
    bool canMove;
    uint nr_Gates;
    int nr_Wires;
    uint src_Gate;
    uint dest_Gate;
    QList<Wire *> list_Wires;
    QList<Gate *> list_Gates;

signals:
    void clicked();
    void un_Select();
    void unWire();
    void Output_Show();
    void Input_Show();
    void clear_Node();
    void connected_Node(int);
};

#endif // SIMULATION_H
