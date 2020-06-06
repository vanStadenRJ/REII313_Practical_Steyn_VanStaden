#ifndef SIMULATION_H
#define SIMULATION_H

#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QJsonDocument>
#include <QGraphicsView>
#include <QJsonObject>
#include <QMouseEvent>
#include <QJsonArray>
#include <QString>
#include <QObject>

#include "Gate.h"
#include "BuildMode.h"
#include "ButtonPanel.h"

class Simulation: public QGraphicsView
{
    Q_OBJECT
public:
    // Constructors
    Simulation(QWidget * parent);

    //Public Methods
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void updateWireLogic();                     // Updates all Logic of all gates and wires upon change
    void updateMWLogic(int x, int y);           // Function called from inputting gates from open file

    //Public Attributes
    QGraphicsScene * scene;                     // Scene to house all items
    Gate * gate;                                // Logic gates, input gates and output gate
    Wire * wire;                                // Wire connecting gates
    Wire * move_wire;                           // Temporary wire created when user decides which nodes to connect
    ButtonPanel * panel;                        // Panel that houses all icons to be selected
    BuildMode * andIcon;                        // Icons representing gates

    bool isBuildMode;                           // When user clicked on icon to be placed -> enter BuildMode
    bool isMove;                                // When user wants to move a gate -> enter MoveMode
    bool insidePanel;                           // Objects can only be placed outside of the icon housing panel
    bool wireMode;                              // When user clicked on output node -> enter WireMode
    bool canMove;                               // Temporary Wire moves upon mouse move event

    int moveGate;                               // Gate number of gate that needs to be moved
    int nr_Gates;                               // Amount of gates placed on schematic
    int nr_Wires;                               // Nr of wires placed on schematic
    int src_Gate;                               // Source Gate of a new wire placed
    int dest_Gate;                              // Destination gate of new wire placed
    int typeIcon;                               // Type of gate to be created
    int src_NodeNr;                             // Source Node number of new wire to be placed
    int dest_NodeNr;                            // Destination Node Number

    QList<Wire *> list_Wires;                   // List of Wires placed on scene
    QList<Gate *> list_Gates;                   // List of gates placed on scene

    QPointF sourceNode;                         // Mouse position of sourceNode of new wire
    QPointF destNode;                           // Mouse position of destNode of new Wire

private:
    void initGates(int nrIn, int x, int y);     // Initialize and create new gate
    void printIcons();                          // Print icons and descriptions on ButtonPanel

signals:
    void un_Select();                           // Delete QGraphicsEffect of gate when clicked after gate has been selected
    void unWire();                              // Delete QGraphicsEffect of wire when clicked after wire has been selected
    void Input_Show();                          // Upon click on output node, all available input nodes must light up
    void clear_Node(bool, int, int);            // Clear lit up nodes if not connected
    void connected_Node(int, int);              // Connect node if wire has been placed on it
    void changeInputLogic();                    // Update logic of all input nodes
    void changeGateLogic();                     // Update logic of all gates
    void changeWireColor();                     // Upon wire logic updated, color of wire must change
};

#endif // SIMULATION_H
