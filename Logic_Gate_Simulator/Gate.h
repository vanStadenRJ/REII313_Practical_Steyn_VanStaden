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

//Yeet

class Gate: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Gate(uint gateNr);
    QGraphicsDropShadowEffect * effect;
    QGraphicsRectItem *input_rect;
    QGraphicsRectItem *rect;
    QGraphicsEllipseItem *circle;
    OutputCon * out;
    InputCon * in;
    uint outputGate;
    uint gate_Nr;

    int stringiu;

    int arrInput[5];
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void keyPressEvent(QKeyEvent * event);

private:
    int input_size;
    int space;

public slots:
    void deleteEffect();
};

#endif // GATE_H
