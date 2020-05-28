#ifndef GATE_H
#define GATE_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsEllipseItem>
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
    Gate(int gateNr, int typeGate, int amnt);

    // Public Methods
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void keyPressEvent(QKeyEvent * event);
    void setCenterPos();

    // Logic Functions
    void andLogic();
    void orLogic();
    void xorLogic();

    // Public Attributes
    QGraphicsDropShadowEffect * effect;     // Shadow Effect when gate is pressed
    QGraphicsRectItem *input_rect;          // Input rect connecting nodes and gates
    QGraphicsRectItem *rect;                // Output rect connecting nodes and gates
    QGraphicsEllipseItem * circle;          // Not circle visual
    OutputCon * out;                        // Output node
    InputCon * in;                          // Input nodes

    QList<InputCon *> list_Inputs;          // List of Inputs connected to gate
    QList<OutputCon *> list_Outputs;        // List of Outputs connected to gate

    QPointF pos_Gate;                       // QPointF position of gate
    QPointF change;
    QPixmap rightClick;
    QPixmap gateBuild;
    int gateType;                          // Normal gate, Input or Output gate
    int gate_Nr;                           // Gate number

    int LogicalOutput;                      // Logic of gate
    uint plus;                              // Value inputrect should be adjusted to
    bool isMove;                            // Is gate being moved
    bool isNot;                             // Does gate have not output

private:
    // Private Attributes
    int input_size;                         // How many inputs does gate have
    int space;                              // Space between input nodes

public slots:
    void deleteEffect();                    // Delete effect when deselct gate
    void updateLogic();                     // Updates logic output of gates
};

#endif // GATE_H
