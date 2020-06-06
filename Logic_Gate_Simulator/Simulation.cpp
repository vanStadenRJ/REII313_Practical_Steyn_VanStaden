#include "Simulation.h"
#include "OutputCon.h"
#include "inputbox.h"
#include "Wire.h"

#include <QMainWindow>
#include <QCursor>
#include <QList>

Simulation::Simulation(QWidget * parent)
{
    // Set scene and show on view
    this->setSceneRect(0,0,1800,950);
    this->scene = new QGraphicsScene(this);
    this->scene->setSceneRect(0,0,1800,950);
    this->setScene(scene);
    this->setFixedSize(1800,950);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // View tracks mouse position
    this->setMouseTracking(true);

    // Initialize Panel where all logic gates to be put
    panel = new ButtonPanel();    
    scene->addItem(panel);

    // Set Background to gridded lines
    this->setBackgroundBrush(QBrush(QImage(":/images/pp.jpg")));

    // Initialize global variables
    this->isBuildMode = false;
    this->isMove = false;
    this->wireMode = false;
    this->move_wire = nullptr;
    this->canMove = false;
    this->nr_Gates = 0;
    this->nr_Wires = 0;

    // Print Icons and Labes on ButtonPanel
    this->printIcons();
}

void Simulation::mousePressEvent(QMouseEvent *event)
{
    // Unclick gate to remove graphicseffect
    if(!(gate == nullptr))
    {
        emit un_Select();
    }

    // Unselect wire to remove graphicseffect
    if(!(wire == nullptr))
    {
        emit unWire();
    }

    // Executes when user has selected to place a new gate
    if(isBuildMode)
    {
        // Ensures that user cannot place gate inside ButtonPanel.
        if((event->button() == Qt::LeftButton) && (insidePanel == false))
        {
            // Initialize and create newly placed gates at position of cursor
            if(!(this->typeIcon == 1) && !(this->typeIcon == 2) && !(this->typeIcon == 0))
            {
                if(this->typeIcon == 9 || this->typeIcon == 10)
                {
                    this->initGates(1, event->x(), event->y());
                }
                else
                {
                    // Get mount of variable inputs to gate
                    bool ok;
                    int input_size = QInputDialog::getInt(this, "Logic Gate Input Selector", "Input Count", 2, 2, 5, 1, &ok);
                    if(ok == true)
                    {
                        this->initGates(input_size, event->x(), event->y());
                    }
                }
            }
            else
            {
                this->initGates(0, event->x(), event->y());
            }            
        }

        // Deactivate BuildMode
        this->isBuildMode = false;
        this->setCursor(QCursor(Qt::ArrowCursor));
    }

    // If gate has been right clicked to be moved
    if(isMove)
    {
        if((event->button() == Qt::LeftButton) && (insidePanel == false))
        {
            for(int i = 0; i < list_Gates.size(); i++)
            {
                if(list_Gates.at(i)->gate_Nr == this->moveGate)
                {
                    list_Gates.at(i)->effect->setEnabled(false);
                    list_Gates.at(i)->setPos(event->x()-list_Gates.at(i)->pixmap()
                                             .width()/2, event->y() - list_Gates.at(i)
                                             ->pixmap().height()/2);

                    // Calculate difference in position to be added to position of gate
                    QPointF dif;
                    dif = list_Gates.at(i)->pos() - list_Gates.at(i)->pos_Gate;
                    list_Gates.at(i)->pos_Gate = list_Gates.at(i)->pos();
                    QLineF line;

                    // For each connected wire, setLine with new coordinates
                    for(int j = 0; j < list_Wires.size(); j++)
                    {
                        if(list_Wires.at(j)->src_Gate == this->moveGate)
                        {
                            list_Wires.at(j)->source = list_Wires.at(j)->source + dif;
                            line.setPoints(list_Wires.at(j)->source, list_Wires.at(j)->dest);
                            list_Wires.at(j)->setLine(line);
                        }
                        else
                        {
                            if(list_Wires.at(j)->dest_Gate == this->moveGate)
                            {
                                list_Wires.at(j)->dest = list_Wires.at(j)->dest + dif;
                                line.setPoints(list_Wires.at(j)->source, list_Wires.at(j)->dest);
                                list_Wires.at(j)->setLine(line);
                            }
                        }
                    }
                }
            }
        }

        // Deactivate MoveMode
        this->setCursor(Qt::ArrowCursor);
        this->isMove = false;
    }

    if(wireMode)
    {
        // If clicked to start wire: clicked on output node
        if(move_wire == nullptr)
        {
            // Create a new wire to be tracked upon mousemove event
            this->move_wire = new Wire();
            this->move_wire->source = this->sourceNode;

            // Add move wire to scene
            this->scene->addItem(move_wire);
            this->canMove = true;

            // Show nodes that are available to be connected
            emit Input_Show();
        }
        else
        {
            // If clicked on Input node, meaning wire placed at destination
            if(event->button() == Qt::LeftButton)
            {
                this->wire = new Wire();
                this->wire->source = move_wire->source;
                this->wire->dest = move_wire->dest;
                this->wire->dest = this->destNode;
                this->wire->src_Gate = this->src_Gate;
                this->wire->dest_Gate = this->dest_Gate;
                this->wire->src_NodeNr = this->src_NodeNr;
                this->wire->dest_NodeNr = this->dest_NodeNr;

                QLineF line;
                line.setPoints(wire->source, wire->dest);
                this->wire->setLine(line);
                this->scene->addItem(wire);
                this->list_Wires << wire;
                this->nr_Wires++;
                this->setCursor(Qt::ArrowCursor);

                for(int g = 0; g < list_Gates.size(); g++)
                {
                    if(list_Gates.at(g)->gate_Nr == wire->src_Gate)
                    {
                        if(list_Gates.at(g)->gateType == 0)
                        {
                            this->list_Gates.at(g)->lowTimer->stop();
                            this->list_Gates.at(g)->highTimer->stop();
                            this->list_Gates.at(g)->LogicalOutput = 0;
                            this->list_Gates.at(g)->lowTimer->start(list_Gates.at(g)->lowTime);
                        }
                        else
                        {
                            this->wire->Logic_Wire = list_Gates.at(g)->LogicalOutput;
                                                    }
                        this->updateMWLogic(wire->Logic_Wire, wire->src_Gate);
                        break;
                    }
                }
                emit clear_Node(false, 0, 0);
            }
            else
            {
                emit clear_Node(false, 0, 0);
                this->setCursor(Qt::ArrowCursor);
            }

            // Reset Attributes
            this->canMove = false;
            this->scene->removeItem(move_wire);
            this->move_wire = nullptr;
            this->wireMode = false;

            // Delete temporary wire
            delete move_wire;
        }
    }
    else
    {
        // If user busy creating new wire, but did not place wire at correct location
        if (!(move_wire == nullptr))
        {
            // Reset Attributes
            this->canMove = false;
            this->scene->removeItem(move_wire);
            this->move_wire = nullptr;
            emit clear_Node(false, 0, 0);
            delete move_wire;
            this->wireMode = false;
        }
    }

    // Ensures that GraphicsView defualt event called to ensure user can continue pressing and moving
    QGraphicsView::mousePressEvent(event);
}

void Simulation::mouseMoveEvent(QMouseEvent *event)
{
    // If wire is busy being drawn and user moves the mouse
    if(canMove == true)
    {        
        this->move_wire->dest = this->mapFromGlobal(QCursor::pos());
        QLineF line;
        line.setPoints(move_wire->source, move_wire->dest);
        this->move_wire->setLine(line);
        this->scene->update();
    }

    // If user has clicked on new gate icon or wants to move existing gate, then gate needs to be placed outside button pannel
    if(isBuildMode || isMove)
    {
        if(this->mapFromGlobal(QCursor::pos()).x() < 300)
        {
            this->insidePanel = true;
        }
        else
        {
            this->insidePanel = false;            
        }
    }

    // Enable default QGraphicsView mousePressEvent()
    QGraphicsView::mousePressEvent(event);
    QGraphicsView::mouseMoveEvent(event);    
}

void Simulation::updateWireLogic()
{    
    // Loop 2 times as to ensure all logic updated
    // Reason being, wires created after other wires, also needs to update if logic of previous wires changed.
    for(int t = 0; t <= 1; t++)
    {
        // Update logic of each wire
        for(int v = 0; v < list_Wires.size(); v++)
        {
            for(int b = 0; b < list_Gates.size(); b++)
            {
                if(list_Gates.at(b)->gate_Nr == list_Wires.at(v)->src_Gate)
                {
                    this->list_Wires.at(v)->Logic_Wire = list_Gates.at(b)->LogicalOutput;
                    emit changeWireColor();
                    this->list_Wires.at(v)->colorLogic();
                    emit changeInputLogic();
                    emit changeGateLogic();
                }
            }
        }

        // Update Logic of all Inputs
        emit changeInputLogic();

        // Update Logic of all gates
        emit changeGateLogic();

        // Only change color logic of wire if there are wires
        if(!(this->list_Wires.size() == 0))
        {
            emit changeWireColor();
        }
    }
}


void Simulation::updateMWLogic(int x, int y)
{
    // Updates Gate Input Nodes Logic
    emit connected_Node(x,y);

    // Updates Logic of Wires
    this->updateWireLogic();
}

void Simulation::initGates(int nrIn, int x, int y)
{
    // Initialize new gate
    this->nr_Gates = this->nr_Gates + 1;
    this->gate = new Gate(this->nr_Gates, this->typeIcon, nrIn);
    this->scene->addItem(gate);
    this->gate->setPos(x-gate->pixmap().width()/2, y -
                 gate->pixmap().height()/2);
    this->gate->pos_Gate = gate->pos();

    // Add gate to list of gates
    this->list_Gates << gate;
    for(int j = 0; j < list_Gates.size(); j++)
    {
        this->list_Gates.at(j)->setCenterPos();
    }
}

void Simulation::printIcons()
{
    // Display all icons and descriptions to ButtonPanel
    int y_coordinate = 0;
    int plus = 0;
    for(int i = 0; i <= 10; i++)
    {
        // Add Icon Descriptions to scene
        QGraphicsTextItem * gateDesc = new QGraphicsTextItem();
        QFont seriFont("Times", 8, QFont::Bold);
        gateDesc->setDefaultTextColor(QColor(0,0,0));
        gateDesc->setFont(seriFont);
        switch(i)
        {
        case 0:
            gateDesc->setPlainText("CLOCK Input");
            break;

        case 1:
            gateDesc->setPlainText("LOW Logic");
            break;

        case 2:
            gateDesc->setPlainText("HIGH Logic");
            break;

        case 3:
            gateDesc->setPlainText("AND Gate");
            break;

        case 4:
            gateDesc->setPlainText("NAND Gate");
            break;

        case 5:
            gateDesc->setPlainText("OR Gate");
            break;

        case 6:
            gateDesc->setPlainText("NOR Gate");
            break;

        case 7:
            gateDesc->setPlainText("XOR Gate");
            break;

        case 8:
            gateDesc->setPlainText("XNOR Gate");
            break;

        case 9:
            gateDesc->setPlainText("NOT Gate");
            break;

        case 10:
            gateDesc->setPlainText("Output Gate");
            break;
        }

        // Create new Icon and ad to scene
        andIcon = new BuildMode(i);
        int tet = 100;
        if (i > 2)
        {
            if(i == 10)
            {
                plus = 200;
            }
            else
            {
                plus = 150;
            }
        }
        if(i == 0)
        {
            andIcon->setY(45 + plus + tet);
        }
        else
        {
            andIcon->setY(45 + y_coordinate*tet + plus);
        }

        if(i%2 == 0 && !(i == 10) && !(i == 0))
        {
            andIcon->setX(309 - andIcon->pixmap().width()/2 - 80);
            gateDesc->setPos(309 - 80 - gateDesc->boundingRect().width()/2, andIcon->y()+50);
            y_coordinate++;

        }
        else
        {
            if(i == 9)
            {
                y_coordinate++;
            }
            andIcon->setX(9 + 75 - andIcon->pixmap().width()/2);
            gateDesc->setPos(9 + 75 - gateDesc->boundingRect().width()/2, andIcon->y()+50);
        }

        // Add Icons and descriptions to scene
        scene->addItem(andIcon);
        scene->addItem(gateDesc);
    }
}
