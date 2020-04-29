#ifndef GATE_H
#define GATE_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsEffect>
#include "OutputCon.h"
#include "InputCon.h"


class Gate: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Gate(QGraphicsItem * parent = 0);
    QGraphicsRectItem *rect;
    QGraphicsEllipseItem *circle;
    QGraphicsRectItem *input_rect;
    OutputCon * out;
    InputCon * in;

    QGraphicsDropShadowEffect * effect;

    void Output();
    void Input();

    void mousePressEvent(QGraphicsSceneMouseEvent * event);

private:
    int input_size;
    int space;

public slots:
    void deleteEffect();
};

#endif // GATE_H
