#ifndef WIRE_H
#define WIRE_H

#include <QGraphicsLineItem>
#include <QObject>
#include <QPointF>

class Wire: public QObject, public QGraphicsLineItem
{
public:
    Wire(QGraphicsItem * parent = 0);

    QPointF source;
    QPointF dest;

    bool draw;
};

#endif // WIRE_H
