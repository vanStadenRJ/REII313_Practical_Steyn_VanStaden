#ifndef GATE_H
#define GATE_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsEffect>
#include <QInputDialog>
#include <QKeyEvent>
#include <QObject>
#include <QDebug>
#include <QList>

#include "OutputCon.h"
#include "InputCon.h"

class Gate: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    // Constructors
    Gate(uint gateNr, uint typeGate);

    // Public Methods
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void keyPressEvent(QKeyEvent * event);
    void updateLogic();                     // Updates logic output of gates

    // Public Attributes
    QGraphicsDropShadowEffect * effect;     // Shadow Effect when gate is pressed
    QGraphicsRectItem *input_rect;          // Input rect connecting nodes and gates
    QGraphicsRectItem *rect;                // Output rect connecting nodes and gates
    OutputCon * out;                        // Output node
    InputCon * in;                          // Input nodes

    QList<InputCon *> list_Inputs;          // List of Inputs connected to gate
    QList<OutputCon *> list_Outputs;        // List of Outputs connected to gate

    QPointF pos_Gate;                       // QPointF position of gate
    uint gateType;                          // Normal gate, Input or Output gate
    uint gate_Nr;                           // Gate number

    int LogicalOutput;                      // Logic of gate
    bool isMove;                            // Is gate being moved

private:
    // Private Attributes
    int input_size;                         // How many inputs does gate have
    int space;                              // Space between input nodes

public slots:
    void deleteEffect();                    // Delete effect when deselct gate
};

#endif // GATE_H
