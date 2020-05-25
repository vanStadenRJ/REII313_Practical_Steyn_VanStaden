#ifndef OUTPUTCON_H
#define OUTPUTCON_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsEffect>
#include <QMouseEvent>
#include <QObject>
#include <QBrush>
#include <QDebug>

#include "Wire.h"

class OutputCon: public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    // Constructors
    OutputCon(QGraphicsItem * parent);

    // Public Methods
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
    void mousePressEvent(QGraphicsSceneMouseEvent * event);

    // Public Attributes
    QPointF wire_Pos;
    QPointF centerPoint;

    QGraphicsDropShadowEffect * effect;

    int parent_Gate;
    bool connected;
    bool test_src;
    bool test;    

public slots:
    void InputToOutput();
    //void clearNode();
    //void conNode();
};

#endif // OUTPUTCON_H
