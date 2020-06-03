#ifndef SIMULATION_H
#define SIMULATION_H

#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QJsonDocument>
#include <QGraphicsView>
#include <QJsonObject>
#include <QMouseEvent>
#include <QJsonArray>
#include <QString>
#include <QObject>

#include "Gate.h"
#include "BuildMode.h"
#include "ButtonPanel.h"

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
    ButtonPanel * panel;
    bool Output;

    bool isBuildMode;
    bool isMove;
    bool insidePanel;
    int moveGate;
    bool wireMode;
    bool canMove;
    int nr_Gates;
    int nr_Wires;
    int src_Gate;
    int dest_Gate;
    QList<Wire *> list_Wires;
    QList<Gate *> list_Gates;

    BuildMode * andIcon;
    QList<BuildMode *> list_Icons;
    int typeIcon;

    int src_NodeNr;
    int dest_NodeNr;

    QPointF sourceNode;
    QPointF destNode;

    QPixmap viewPix;
    bool isNot;
    QGraphicsTextItem * gateDesc;

    QJsonArray toJson();

    void updateMWLogic(int x, int y);

private:
    void initGates(int nrIn, int x, int y);

signals:
    void clicked();
    void un_Select();
    void unWire();
    void Output_Show();
    void Input_Show();
    void clear_Node(bool, int, int);
    void connected_Node(int, int);
    void changeInputLogic();
    void changeGateLogic();
    void changeWireColor();
};

#endif // SIMULATION_H
