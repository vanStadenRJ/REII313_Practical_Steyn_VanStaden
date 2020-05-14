#ifndef OUTPUTCON_H
#define OUTPUTCON_H

#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QObject>

#include "Wire.h"

class OutputCon: public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    OutputCon(QGraphicsItem * parent);

    void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
    void mousePressEvent(QGraphicsSceneMouseEvent * event);

    QPointF wire_Pos;
    int parent_Gate;
    bool connected;
    bool test;
    bool test_src;

public slots:
    void InputToOutput();
    void clearNode();
    void conNode();

private:

};

#endif // OUTPUTCON_H
