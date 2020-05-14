#ifndef GATE_H
#define GATE_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsEffect>
#include <QKeyEvent>
#include <QList>

#include "OutputCon.h"
#include "InputCon.h"

class Gate: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Gate(uint gateNr, uint typeGate);
    QGraphicsDropShadowEffect * effect;
    QGraphicsRectItem *input_rect;
    QGraphicsRectItem *rect;
    QGraphicsEllipseItem *circle;
    OutputCon * out;
    InputCon * in;
    uint outputGate;
    uint gate_Nr;

    QList<InputCon *> list_Inputs;
    QList<OutputCon *> list_Outputs;
    int arrInput[5];
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void keyPressEvent(QKeyEvent * event);
    void updateLogic();

    int LogicalOutput;
    uint gateType;

private:
    int input_size;
    int space;

public slots:
    void deleteEffect();
    //void updateLogic();
};

#endif // GATE_H
