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
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // Public Attributes
    QPointF centerPoint;
    int parent_Gate;                        // Gate Number of parent gate
    bool connected;                         // Is node connected
    int posGate;                            // Position of node when gate created
    int conGate;
    int Logic;                              // Logic of node
    bool test;

public slots:
    void OutputToInput();                   // Called when node not connected to show notable connections
    void conNode(int k, int h);                    // Called to give node the logic of wire connected
    void clearNode(bool gate, int g, int h);                       // Cleared when wire not connected
    void getWireLogic();
};

#endif // INPUTCON_H
