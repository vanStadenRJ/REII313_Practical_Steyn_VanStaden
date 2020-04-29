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
    OutputCon();

    void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
    //void mouseMoveEvent(QMouseEvent * event);

    //QGraphicsLineItem * wire;
    QPointF source;

public slots:
    void changeColor();

private:

};

#endif // OUTPUTCON_H
