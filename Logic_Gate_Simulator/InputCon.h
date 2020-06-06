#ifndef INPUTCON_H
#define INPUTCON_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QMouseEvent>
#include <QObject>

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
    QPointF centerPoint;                        // Coordinate of center point of node to make wiring visually appealing
    int parent_Gate;                            // Gate Number of parent gate
    int posGate;                                // Position of node when gate created
    int conGate;                                // Gate that is connected to this node
    int Logic;                                  // Logic of output node
    bool connected;                             // Is node connected
    bool test;                                  // If false, node is not connected, clear node

public slots:
    void OutputToInput();                       // Called when node not connected to show notable connections
    void conNode(int k, int h);                 // Called to give node the logic of wire connected
    void clearNode(bool gate, int g, int h);    // Cleared when wire not connected
    void getWireLogic();                        // Get logic of wire connected to node
};

#endif // INPUTCON_H
