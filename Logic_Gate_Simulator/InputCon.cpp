#include "InputCon.h"
#include "Simulation.h"

extern Simulation * simulation;

InputCon::InputCon(QGraphicsItem *parent): QGraphicsEllipseItem (parent)
{
    // Set z-value to ensure wire placed underneath node
    this->setZValue(2);

    // Set width of node outline
    QPen pen;
    pen.setWidth(2);
    this->setPen(pen);

    // White fill look of the node
    QBrush brush;
    brush.setColor(QColor(255,255,255));
    brush.setStyle(Qt::SolidPattern);
    this->setBrush(brush);

    // Node is a circle with radius = 6
    this->setRect(0,0,12,12);

    // Initialize 0 logic to the node, if not connected, node has 0 logic
    this->posGate = 0;
    this->Logic = 0;
    this->connected = false;
    this->test = false;

    // ALLOW RESPONDING TO HOVER EVENTS
    this->setAcceptHoverEvents(true);

    // Connect Signals and Slots
    QObject::connect(simulation, SIGNAL(Input_Show()), this, SLOT(OutputToInput()));
    QObject::connect(simulation, SIGNAL(clear_Node(bool, int, int)), this, SLOT(clearNode(bool, int, int)));
    QObject::connect(simulation,SIGNAL(connected_Node(int, int)), this, SLOT(conNode(int, int)));
    QObject::connect(simulation, SIGNAL(changeInputLogic()), this, SLOT(getWireLogic()));
}

void InputCon::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    // Only accept hoverEnterEvents if user is busy drawing wire, and node is disconnected, and not connecting output to same gates input
    if((this->connected == false) && !(simulation->move_wire == nullptr) && !(simulation->src_Gate == this->parent_Gate))
    {
        //Change color and appearance to fill node and color black
        QBrush brush;
        brush.setColor(Qt::black);
        brush.setStyle(Qt::SolidPattern);
        this->setBrush(brush);

        // If user clicks, then the program knows not to make node available again, node is already connected
        this->test = true;                                  // Used in the conNode() slot

        // More visual clues that user can click on node
        simulation->setCursor(Qt::CrossCursor);

        // If user clicks, the program knows that the node can be connected
        simulation->wireMode = true;
        simulation->dest_Gate = this->parent_Gate;
        simulation->dest_NodeNr = this->posGate;
        simulation->destNode = this->centerPoint;
    }
}

void InputCon::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    // Only accept hoverLeaveEvents if user is busy drawing wire, and node is disconnected, and not connecting output to same gates input
    if((connected == false) && !(simulation->move_wire == nullptr) && !(simulation->src_Gate == this->parent_Gate))
    {
        // If user clicks, node is not connected
        this->test = false;

        // Change color back to green to show user node is available to be connected
        QBrush brush;
        brush.setColor(Qt::darkGreen);
        brush.setStyle(Qt::SolidPattern);
        this->setBrush(brush);

        // Set variables to defualt and change cursor
        simulation->setCursor(Qt::ArrowCursor);
        simulation->wireMode = false;
        simulation->src_NodeNr = 0;
    }
}

void InputCon::OutputToInput()
{
    // If user connects nodes, the nodes that are not connected, must be reset
    if(!(simulation->src_Gate == this->parent_Gate) && (this->connected == false))
    {
        QBrush brush;
        brush.setColor(Qt::darkGreen);
        brush.setStyle(Qt::SolidPattern);
        this->setBrush(brush);
    }
}

void InputCon::clearNode(bool gate, int g, int h)
{
    // Function is called when wire or gate is deleted.
    // If node was connected, logic must be reset
    if(gate == true)
    {
        if(g == conGate && h == posGate)
        {
            this->setBrush(QColor(255,255,255));
            this->Logic = 0;
            this->connected = false;
        }
    }
    else
    {
        if(this->connected == false)
        {
            this->setBrush(QColor(255,255,255));
            this->Logic = 0;
            this->connected = false;
        }
    }
}

void InputCon::getWireLogic()
{
    // Function called when logic of whole simulation is updated
    if(this->connected == true)
    {
        for(int i = 0; i < simulation->list_Wires.size(); i++)
        {
            if(simulation->list_Wires.at(i)->dest_NodeNr == this->posGate && this->parent_Gate == simulation->list_Wires.at(i)->dest_Gate)
            {
                this->Logic = simulation->list_Wires.at(i)->Logic_Wire;
                return;
            }
        }
    }
    else
    {
        this->Logic = 0;
        return;
    }
}

void InputCon::conNode(int k, int h)
{
    // Upon connection of new wire, the node gets the logic of the wire.
    if(simulation->dest_Gate == this->parent_Gate || simulation->src_Gate == this->parent_Gate)
    {
        if(test == true)
        {
            // Change Visual of node
            this->connected = true;
            QBrush brush;
            brush.setColor(Qt::white);
            brush.setStyle(Qt::SolidPattern);
            this->setBrush(brush);

            // Set node attributes
            this->Logic = k;
            this->conGate = h;

            // Reset test, as when wire gets deleted, the node needs to be connected again
            this->test = false;
        }
    }
}
