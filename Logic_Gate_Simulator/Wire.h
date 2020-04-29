#ifndef WIRE_H
#define WIRE_H

#include <QGraphicsLineItem>
#include <QObject>
#include <QPointF>
#include <QGraphicsSceneMouseEvent>

class Wire: public QObject, public QGraphicsLineItem
{
public:
    Wire();

    QPointF source;
    QPointF dest;

    void mousePressEvent(QGraphicsSceneMouseEvent * event);

    bool draw;
};

#endif // WIRE_H
