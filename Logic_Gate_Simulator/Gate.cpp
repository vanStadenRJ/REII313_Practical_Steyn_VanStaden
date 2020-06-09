#include "Gate.h"
#include "Simulation.h"
#include "inputbox.h"

extern Simulation * simulation;

Gate::Gate(int gateNr, int typeGate, int amnt)
{
    // Change z value as to ensure that gate on top of wire
    this->setZValue(1);

    // Item can accept keyboard events
    this->setFlag(QGraphicsItem::ItemIsFocusable);

    // Set default values
    this->isMove = false;
    this->isNot = false;

    // Apply QGraphicsEffect
    this->effect = new QGraphicsDropShadowEffect();
    this->effect->setColor(Qt::lightGray);
    this->effect->setOffset(8);
    this->setGraphicsEffect(effect);

    // Connect Signal and Slots
    QObject::connect(simulation, SIGNAL(un_Select()), this, SLOT(deleteEffect()));
    QObject::connect(simulation, SIGNAL(changeGateLogic()), this, SLOT(updateLogic()));

    // Initialize type of gate
    this->gateType = typeGate;

    // Initialize Clocked Input Gate
    this->lowTime = 0;
    this->highTime = 0;
    if(gateType == 0)
    {
        lowTimer = new QTimer();
        highTimer = new QTimer();
        QObject::connect(lowTimer, SIGNAL(timeout()), this, SLOT(updateLow()));
        QObject::connect(highTimer, SIGNAL(timeout()), this, SLOT(updateHigh()));
        lowTime = 500;
        highTime = 1000;
        lowTimer->start(lowTime);
    }

    // Upon icon clicked, type of gate needs to be identified and correct gate placed
    this->gate_Nr = gateNr;
    this->setPix();
    this->LogicalOutput = 0;
    if(gateType == 2 || gateType == 0)
    {
        this->LogicalOutput = 1;
    }

    // For different input size, nr of input nodes need to be configured
    input_size = amnt;
    space = (pixmap().height() - input_size*2)/(input_size+1);
    for(int i = 1; i <= input_size; i++)
    {
        // input_rect is visual connection of node and gate
        input_rect = new QGraphicsRectItem(this);

        // If OR, NOR, XOR, XNOR, position of lines need adjusting
        this->plus = 0;
        this->plusB = 0;
        if(gateType == 5 || gateType == 6)
        {
            plus = 16;
        }
        else
        {
            if(gateType == 7 || gateType == 8)
            {
                plusB = 15;
                plus = 31;
            }
        }
        input_rect->setRect(x(), y(), 20 + plusB, 2);
        input_rect->setParentItem(this);
        input_rect->setPos(this->x() - input_rect->rect().width() + plus,
                           space*i + input_rect->rect().height()*(i-1));

        input_rect->setBrush(QColor(0,0,0));

        // in is of InputCon node
        in = new InputCon(input_rect);
        in->setParentItem(input_rect);
        in->setPos(-in->rect().width(), - in->rect().height()/2 +
                   input_rect->rect().height()/2);
        in->posGate = i;
        in->parent_Gate = gate_Nr;                                  // Set parent as gate, to be moved and deleted
        list_Inputs << in;                                          // Add input nodes to list
    }

    // Draw output branch and node of the gate
    rect = new QGraphicsRectItem(this);
    rect->setRect(x(), y(), 20, 2);
    this->plusC = 0;
    if(isNot == true)
    {
        // If gate is a NOT related gate, the circle at the end of gate must be drawn
        circle = new QGraphicsEllipseItem(this);
        circle->setRect(0,0,10,10);
        circle->setParentItem(this);
        circle->setPos(pixmap().width(), pixmap().height()/2 - circle->rect().height()/2);
        circle->setBrush(QColor(255,255,255));

        QPen pen;
        pen.setWidth(2);
        circle->setPen(pen);
        this->plusC = circle->rect().width();
    }
    rect->setBrush(QColor(0,0,0));
    rect->setParentItem(this);
    rect->setX(pixmap().width() + this->plusC);
    rect->setY(pixmap().height()/2 - rect->rect().height()/2);
    if(gateType == 10)
    {
        rect->hide();
    }
    this->updateLogic();

    // set output nodes and configure
    out = new OutputCon(rect);
    out->setParentItem(rect);
    out->setPos(rect->rect().width(), rect->rect().height()/2 - out->rect().height()/2);
    out->parent_Gate = gate_Nr;
    if(gateType == 10)
    {
        out->hide();
    }
}

// MousePressEvent to handle effects and movement of gates
void Gate::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // Right Button to move gate
    if(event->button() == Qt::RightButton)
    {
        if (simulation->isMove == false)
        {
            simulation->setCursor(this->rightClick);
            simulation->isMove = true;
            this->isMove = true;
            simulation->moveGate = this->gate_Nr;
        }
    }
    else
    {
        this->prepareGeometryChange();
        this->effect->setEnabled(true);
    }
    this->setCenterPos();
}

// KeyPressEvent as gate needs to be deleted
void Gate::keyPressEvent(QKeyEvent *event)
{
    // SPACE pressed on clocked input gate lets user change time high and time low
    if(effect->isEnabled() && event->key() == Qt::Key_Space && this->gateType == 0)
    {
        // Input Box to ask user input for time high and low
        bool ok;
        QList<int> list = InputBox::getValues(simulation, &ok);
        if (ok)
        {
            this->lowTime = list[0];
            this->highTime = list[1];
            this->lowTimer->stop();
            this->highTimer->stop();
            this->lowTimer->start(lowTime);
        }
    }

    // DELETE pressed, deletes gate and connected wires
    if(effect->isEnabled() && event->key() == Qt::Key_Delete)
    {
        if(!(simulation->nr_Wires == 0))
        {
            // Delete all wires connected to gate to be deleted
            int i = 0;
            int n = simulation->list_Wires.size();
            while(i < n)
            {
                if((simulation->list_Wires.at(i)->src_Gate == this->gate_Nr) || (simulation->list_Wires.at(i)->dest_Gate == this->gate_Nr))
                {
                    if(!(simulation->list_Wires.at(i)->dest_Gate == this->gate_Nr))
                    {
                        emit simulation->clear_Node(true, simulation->list_Wires.at(i)->src_Gate , simulation->list_Wires.at(i)->dest_NodeNr);
                    }
                    delete simulation->list_Wires.takeAt(i);
                    i--;
                    n--;
                    simulation->nr_Wires = simulation->nr_Wires - 1;
                }
                i++;
            }
        }

        // Upon Wires Deleted, Remove Gate from list
        for(int g = 0; g < simulation->list_Gates.size(); g++)
        {
            if(this->gate_Nr == simulation->list_Gates.at(g)->gate_Nr)
            {
                simulation->list_Gates.takeAt(g);
                break;
            }
        }

        // Update logic of all other gates
        emit simulation->updateWireLogic();

        // Set effect to nullptr before deleting gate
        this->prepareGeometryChange();
        this->effect = nullptr;

        // Delete the gate
        delete this;
        return;
    }
}

// Delete Effect of gate to be reset
void Gate::deleteEffect()
{
    this->prepareGeometryChange();
    this->effect->setEnabled(false);
}

// Update Logic of gate when new wires connected and deleted
void Gate::updateLogic()
{
    switch(this->gateType)
    {
    // AND-NAND Gate Logic Called
    case 3:
    case 4:
        this->andLogic();
        break;

    // OR-NOR Gate Logic Called
    case 5:
    case 6:
        this->orLogic();
        break;

    // XOR-XNOR Gate Logic Called
    case 7:
    case 8:
        this->xorLogic();
        break;

    // NOT GATE LOGIC
    case 9:
        this->notLogic();
        break;

    // CHANGE PIXMAP UPON LOGIC OF OUTPUT GATE
    case 10:
        this->outputLogic();
        break;
    }
}

// SLOT called when High Timer timeout
void Gate::updateLow()
{
    this->lowTimer->stop();
    this->LogicalOutput = 1;
    simulation->updateWireLogic();

    // After low timer timeout, start high timer
    this->highTimer->start(highTime);
}

// SLOT called when Low Timer timeout
void Gate::updateHigh()
{
    this->highTimer->stop();
    this->LogicalOutput = 0;
    simulation->updateWireLogic();

    // After high timer timeout, start low timer
    this->lowTimer->start(lowTime);
}

// Function to center output and input nodes to better wire placement upon click
void Gate::setCenterPos()
{
    // User can click anywhere inside output node, but the wire start QPointF value is the center of the node
    this->out->centerPoint = this->pos() + this->rect->pos();
    this->out->centerPoint.setX(this->out->centerPoint.x() + this->rect->rect().width() + this->out->rect().width()/2);

    // User can click anywhere inside input node, but the wire destination QPointF value is the center of the node
    for(int i = 0; i < list_Inputs.size(); i++)
    {
        this->list_Inputs.at(i)->centerPoint = this->pos();
        this->list_Inputs.at(i)->centerPoint.setX(this->list_Inputs.at(i)->centerPoint.x() + this->plus - plusB
                                                  - this->rect->rect().width() - this->out->rect().width()/2);
        this->list_Inputs.at(i)->centerPoint.setY(this->list_Inputs.at(i)->centerPoint.y()
                                                  + (i)*rect->rect().height() + (i+1)*space);
    }
}

// Function called to set working QPixmap
void Gate::setPix()
{
    switch(this->gateType)
    {
    case 0:     // 0 = PULSE
        this->setPixmap(QPixmap(":/images/Pulse_Icon.png"));
        this->rightClick = this->pixmap();
        this->isNot = false;
        break;

    case 1:     // 1 = Low Input
        this->setPixmap(QPixmap(":/images/Low_Icon.png"));
        this->rightClick = this->pixmap();
        this->isNot = false;
        break;

    case 2:     // 2 = High Input
        this->setPixmap(QPixmap(":/images/High_Icon.png"));
        this->rightClick = this->pixmap();
        this->isNot = false;
        break;

    case 3:     // 3 = AND Gate
        this->setPixmap(QPixmap(":/images/And_Gate_View.png"));
        this->rightClick = QPixmap(":/images/And_Gate.png");
        this->isNot = false;
        break;

    case 4:     // 4 = NAND Gate
        this->setPixmap(QPixmap(":/images/And_Gate_View.png"));
        this->rightClick = QPixmap(":/images/Nand_Gate.png");
        this->isNot = true;
        break;

    case 5:     // 5 = OR Gate
        this->setPixmap(QPixmap(":/images/Or_Gate_View.png"));
        this->rightClick = QPixmap(":/images/Or_Gate.png");
        this->isNot = false;
        break;

    case 6:     // 6 = NOR Gate
        this->setPixmap(QPixmap(":/images/Or_Gate_View.png"));
        this->rightClick = QPixmap(":/images/Nor_Gate.png");
        this->isNot = true;
        break;

    case 7:     // 7 = XOR Gate
        this->setPixmap(QPixmap(":/images/XOR_Gate_View.png"));
        this->rightClick = QPixmap(":/images/XOR_Gate.png");
        this->isNot = false;
        break;

    case 8:     // 8 = XNOR Gate
        this->setPixmap(QPixmap(":/images/XOR_Gate_View.png"));
        this->rightClick = QPixmap(":/images/XNOR_Gate.png");
        this->isNot = true;
        break;

    case 9:     // 9 = NOT Gate
        this->setPixmap(QPixmap(":/images/NOT_Gate_View.png"));
        this->rightClick = QPixmap(":/images/NOT_Gate.png");
        this->isNot = true;
        break;

    case 10:     // 10 = OUTPUT
        this->setPixmap(QPixmap(":/images/output_Gate.png"));
        this->rightClick = QPixmap(":/images/output_Gate.png");
        this->isNot = false;
        break;
    }
}

// Function handling AND logic of gate
void Gate::andLogic()
{
    // A Default logic is assigned, if one of the input nodes has logic 0, the logic is changed
    int def;
    int change;
    if(isNot == false)
    {
        def = 1;
        change = 0;
    }
    else
    {
        def = 0;
        change = 1;
    }
    this->LogicalOutput = def;
    for(int i = 0; i < list_Inputs.size(); i++)
    {
        if(list_Inputs.at(i)->Logic == 0)
        {
            this->LogicalOutput = change;
            return;
        }
    }
}

void Gate::orLogic()
{
    // A Default logic is assigned, if one of the input nodes has logic 1, the logic is changed
    int def;
    int change;
    if(isNot == false)
    {
        def = 0;
        change = 1;
    }
    else
    {
        def = 1;
        change = 0;
    }
    this->LogicalOutput = def;
    for(int i = 0; i < list_Inputs.size(); i++)
    {
        if(this->list_Inputs.at(i)->Logic == 1)
        {
            this->LogicalOutput = change;
            return;
        }
    }
}

void Gate::xorLogic()
{
    // XOR: For 2 inputs - If all input nodes have same logic, the output logic will be low
    // XOR: For >2 inputs - HIGH if nr of high inputs is odd

    // XNOR: For 2 inputs - If all inputs have same logic, output will be high
    // XNOR: For >2 inputs - HIGH if nr of high inputs is even

    int nrHigh = 0;

    for(int i = 0; i < this->list_Inputs.size(); i++)
    {
        if(list_Inputs.at(i)->Logic == 1)
        {
            nrHigh++;
        }
    }
    if(this->isNot == true)
    {
        if(nrHigh % 2 == 0)
        {
            this->LogicalOutput = 1;
        }
        else
        {
            this->LogicalOutput = 0;
        }
    }
    else
    {
        if(nrHigh % 2 == 0)
        {
            this->LogicalOutput = 0;
        }
        else
        {
            this->LogicalOutput = 1;
        }
    }
}

void Gate::notLogic()
{
    // Toggle input logic to deliver inversed output logic
    if(in->Logic == 0)
    {
        this->LogicalOutput = 1;
    }
    else
    {
        this->LogicalOutput = 0;
    }
}

void Gate::outputLogic()
{
    // Logic 1: Blue Smiley output
    // Logic 0: White Frowny output
    if(in->Logic == 1)
    {
        this->setPixmap(QPixmap(":/images/outputSmile.png"));
    }
    else
    {
        this->setPixmap(QPixmap(":/images/outputFrown.png"));
    }
}
