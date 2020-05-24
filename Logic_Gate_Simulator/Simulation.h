#ifndef SIMULATION_H
#define SIMULATION_H

#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QString>
#include <QObject>

#include "Gate.h"
#include "BuildMode.h"

// Our main workspace will be Simulation which inherits from QGraphicsView
class Simulation: public QGraphicsView
{
    Q_OBJECT
public:
    // Constructors
    Simulation(QWidget * parent);

    //Public Methods
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void updateWireLogic();

    //Public Attributes
    QGraphicsScene * scene;
    Gate * gate;
    Wire * wire;
    Wire * move_wire;
    bool Output;

    bool isBuildMode;
    bool isMove;
    uint moveGate;
    bool wireMode;
    bool canMove;
    uint nr_Gates;
    int nr_Wires;
    uint src_Gate;
    uint dest_Gate;
    QList<Wire *> list_Wires;
    QList<Gate *> list_Gates;

    BuildMode * andIcon;
    BuildMode * highIcon;
    BuildMode * lowIcon;
    uint typeIcon;

    uint src_NodeNr;
    uint dest_NodeNr;

    QPointF sourceNode;
    QPointF destNode;

private:


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
