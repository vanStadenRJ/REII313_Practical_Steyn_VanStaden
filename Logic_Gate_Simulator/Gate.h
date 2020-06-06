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
#include <QTimer>
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
    void setCenterPos();                    // Set Center Position of input and output nodes

    // Public Attributes
    QGraphicsDropShadowEffect * effect;     // Shadow Effect when gate is pressed
    QList<InputCon *> list_Inputs;          // List of Inputs connected to gate
    QList<OutputCon *> list_Outputs;        // List of Outputs connected to gate
    QPointF pos_Gate;                       // QPointF position of gate
    QPointF change;                         // Change in coordinates upon moving gate
    QPixmap rightClick;                     // Pixmap of cursor upon moving gate
    QTimer * highTimer;                     // Timer to aid high time in clocked input gate
    QTimer * lowTimer;                      // Timer to aid low time in clocked input gate
    int gateType;                           // Normal gate, Input or Output gate
    int gate_Nr;                            // Gate number
    int LogicalOutput;                      // Logic of gate
    int highTime;                           // Variable High time to be set by user
    int lowTime;                            // Variable Low time to be set by user
    int input_size;                         // How many inputs does gate have
    bool isMove;                            // Is gate being moved
    bool isNot;                             // Does gate have not output

private:
    // Private Attributes
    QGraphicsRectItem *input_rect;          // Input rect connecting nodes and gates
    QGraphicsRectItem *rect;                // Output rect connecting nodes and gates
    QGraphicsEllipseItem * circle;          // Not circle visual
    OutputCon * out;                        // Output node
    InputCon * in;                          // Input nodes
    uint plus;                              // Value inputrect should be adjusted to
    uint plusB;                             // XNOR / XOR Adjustment in x-direction
    int space;                              // Space between input nodes
    double plusC;                           // Width of not circle aiding in placement of nodes

    // Private Methods
    void setPix();                          // Set Pixmap of gate

    // Logic Functions
    void andLogic();                        // Logic of AND/NAND
    void orLogic();                         // Logic of OR/NOR
    void xorLogic();                        // Logic of XOR/XNOR
    void notLogic();                        // Logic of NOT
    void outputLogic();                     // Logic of OUTPUT

public slots:
    void deleteEffect();                    // Delete effect when deselct gate
    void updateLogic();                     // Updates logic output of gates
    void updateHigh();                      // Timer_1 handling high time of clocked pulse
    void updateLow();                       // Timer_2 handling low time of clocked pulse
};

#endif // GATE_H
