#ifndef WIRE_H
#define WIRE_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QGraphicsEffect>
#include <QKeyEvent>
#include <QObject>
#include <QPointF>
#include <QPen>

class Wire: public QObject, public QGraphicsLineItem
{
    Q_OBJECT
public:
    // Constructors
    Wire();

    // Public Methods
    void paint(QPainter *painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void keyPressEvent(QKeyEvent * event);

    // Public Attributes
    QGraphicsDropShadowEffect * effect;             // QGraphicsEffect linked to wire being pressed
    QPointF source;                                 // Source coordinate of wire
    QPointF dest;                                   // Dest coordinate of wire
    int src_Gate;                                   // Gate Number of source gate
    int dest_Gate;                                  // Gate Number of destination gate
    int src_NodeNr;                                 // Node number of node on source gate
    int dest_NodeNr;                                // Node number of node on dest gate
    int Logic_Wire;                                 // Logic of wire

public slots:
    void deleteEffect();                            // Delete Effect of wire
    void colorLogic();                              // Update color that represents the logic of wire
};

#endif // WIRE_H
