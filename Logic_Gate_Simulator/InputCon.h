#ifndef INPUTCON_H
#define INPUTCON_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QMouseEvent>
#include <QObject>
#include <QDebug>

class InputCon: public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    // Constructors
    InputCon(QGraphicsItem * parent);

    // Public Methods
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);

    // Public Attributes
    QPointF centerPoint;
    int parent_Gate;                        // Gate Number of parent gate
    bool connected;                         // Is node connected
    uint posGate;                            // Position of node when gate created
    int Logic;                              // Logic of node
    bool test;

public slots:
    void OutputToInput();                   // Called when node not connected to show notable connections
    void conNode(int k);                    // Called to give node the logic of wire connected
    void clearNode();                       // Cleared when wire not connected
};

#endif // INPUTCON_H
