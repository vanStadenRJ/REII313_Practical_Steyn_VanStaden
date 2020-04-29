#ifndef GATE_H
#define GATE_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include "OutputCon.h"


class Gate: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Gate(QGraphicsItem * parent = 0);
    QGraphicsRectItem *rect;
    QGraphicsEllipseItem *circle;
    QGraphicsRectItem *input_rect;
    OutputCon * out;

    void Output();

private:
    int input_size;
    int space;

public slots:

};

#endif // GATE_H
