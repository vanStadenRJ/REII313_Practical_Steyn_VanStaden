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

    // Public Attributes
    QPointF centerPoint;
    int parent_Gate;
};

#endif // OUTPUTCON_H
