#ifndef GATE_H
#define GATE_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsEffect>
#include <QKeyEvent>
#include "OutputCon.h"
#include "InputCon.h"


class Gate: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Gate(uint gateNr);
    QGraphicsRectItem *input_rect;
    QGraphicsRectItem *rect;

    QGraphicsEllipseItem *circle;

    OutputCon * out;
    InputCon * in;

    uint gate_Nr;

    QGraphicsDropShadowEffect * effect;

    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void keyPressEvent(QKeyEvent * event);

private:
    int input_size;
    int space;


public slots:
    void deleteEffect();
};

#endif // GATE_H
