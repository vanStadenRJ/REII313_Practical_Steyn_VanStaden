#include "Gate.h"
#include "Simulation.h"

extern Simulation * simulation;

Gate::Gate(int gateNr, int typeGate, int amnt)
{
    qDebug() << simulation->list_Gates.size();

    // Change z value as to ensure that gate on top of wire
    this->setZValue(1);

    // Item can accept keyboard events
    this->setFlag(QGraphicsItem::ItemIsFocusable);

    // Set default values
    this->isMove = false;
    this->effect = nullptr;
    this->isNot = false;

    // Connect Signal and Slots
    QObject::connect(simulation, SIGNAL(un_Select()), this, SLOT(deleteEffect()));
    QObject::connect(simulation, SIGNAL(changeGateLogic()), this, SLOT(updateLogic()));

    // Upon icon clicked, type of gate needs to be identified and correct gate placed
    this->gate_Nr = gateNr;
    gateType = typeGate;
    if(typeGate == 2 || typeGate == 3)                                  // If gate is of input type!
    {
        if(typeGate == 2)                                               // If type High Input
        {
            this->setPixmap(QPixmap(":/images/High_Icon.png"));
            this->rightClick = QPixmap(":/images/High_Icon.png");
            this->LogicalOutput = 1;                                    // Set logic of gate
        }
        else                                                            // If type Low Input
        {
            this->setPixmap(QPixmap(":/images/Low_Icon.png"));
            this->rightClick = QPixmap(":/images/Low_Icon.png");
            this->LogicalOutput = 0;                                    // Set logic of gate
        }
    }
    else
    {
        switch(gateType)
        {
        case 1:
            this->setPixmap(QPixmap(":/images/And_Gate_View.png"));
            this->rightClick = QPixmap(":/images/And_Gate.png");
            break;

        case 4:
            this->setPixmap(QPixmap(":/images/And_Gate_View.png"));
            this->rightClick = QPixmap(":/images/Nand_Gate.png");
            this->isNot = true;
            break;

        case 5:
            this->setPixmap(QPixmap(":/images/Or_Gate_View.png"));
            this->rightClick = QPixmap(":/images/Or_Gate.png");
            break;

        case 6:
            this->setPixmap(QPixmap(":/images/Or_Gate_View.png"));
            this->rightClick = QPixmap(":/images/Nor_Gate.png");
            this->isNot = true;
            break;

        case 7:
            this->setPixmap(QPixmap(":/images/XOR_Gate_View.png"));
            this->rightClick = QPixmap(":/images/XOR_Gate.png");
            break;
        }
        this->LogicalOutput = 0;

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
                if(gateType == 7)
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
    }

    // set draw output branch
    rect = new QGraphicsRectItem(this);
    if(gateType == 7 || gateType == 8)
    {
        rect->setRect(x(), y(), 20, 2);
    }
    else
    {
        rect->setRect(x(), y(), 20, 2);
    }

    if(isNot == true)
    {
        circle = new QGraphicsEllipseItem(this);
        circle->setRect(0,0,10,10);
        circle->setParentItem(this);
        this->plusC = 0;
        if(gateType == 6)
        {
            this->plusC = 2;
        }
        circle->setPos(pixmap().width() - plusC, pixmap().height()/2 - circle->rect().height()/2);
        circle->setBrush(QColor(255,255,255));

        QPen pen;
        pen.setWidth(2);
        circle->setPen(pen);
    }

    rect->setBrush(QColor(0,0,0));
    rect->setParentItem(this);
    switch (typeGate)
    {
    case 1:
        rect->setPos(pixmap().width(), pixmap().height()/2 - rect->rect().height()/2);
        this->updateLogic();
        break;

    case 2:
        rect->setPos(pixmap().width(), pixmap().height()/2 - rect->rect().height()/2);
        break;

    case 3:
        rect->setPos(pixmap().width(), pixmap().height()/2 - rect->rect().height()/2);
        break;

    case 4:
        rect->setPos(pixmap().width() + circle->rect().width(), pixmap().height()/2 - rect->rect().height()/2);
        this->updateLogic();
        break;

    case 5:
        rect->setPos(pixmap().width() - 2, pixmap().height()/2 - rect->rect().height()/2);
        this->updateLogic();
        break;

    case 6:
        rect->setPos(pixmap().width() - plusC + circle->rect().width(), pixmap().height()/2 - rect->rect().height()/2);
        this->updateLogic();
        break;

    case 7:
        rect->setPos(pixmap().width() - 2, pixmap().height()/2 - rect->rect().height()/2);
        this->updateLogic();
        break;
    }

    // set output nodes and configure
    out = new OutputCon(rect);
    out->setParentItem(rect);
    out->setPos(rect->rect().width(), rect->rect().height()/2 - out->rect().height()/2);
    out->parent_Gate = gate_Nr;
    this->list_Outputs << out;    
}

// MousePressEvent to handle effects and movement of gates
void Gate::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setFocus();
    // Right Button to move gate
    if(event->button() == Qt::RightButton)
    {
        if (simulation->isMove == false)
        {
            simulation->setCursor(this->rightClick);
            simulation->isMove = true;
            this->isMove = true;
            simulation->moveGate = this->gate_Nr;
            this->deleteEffect();
        }
    }
    else
    {
        // Left Button to show effect and make gate ready for delet
        if(effect == nullptr)
        {
            effect = new QGraphicsDropShadowEffect();
            effect->setColor(Qt::lightGray);
            effect->setOffset(8);
        }
        else
        {
            effect->setEnabled(true);
        }
        this->setGraphicsEffect(effect);
        this->setFocus();
    }

    this->setCenterPos();
}

// KeyPressEvent as gate needs to be deleted
void Gate::keyPressEvent(QKeyEvent *event)
{
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

        // Upon Gate Delete, Remove Gate from list
        for(int g = 0; g < simulation->list_Gates.size(); g++)
        {
            if(this->gate_Nr == simulation->list_Gates.at(g)->gate_Nr)
            {
                simulation->list_Gates.takeAt(g);
                break;
            }
        }

        //Update logic of all other gates
        emit simulation->updateWireLogic();

        delete this;
        return;
    }
}

// Delete Effect of gate to be reset
void Gate::deleteEffect()
{
    if (!(effect == nullptr))
    {
        effect->setEnabled(false);
        this->clearFocus();
    }
}

// Update Logic of gate when new wires connected and deleted
void Gate::updateLogic()
{
    switch(this->gateType)
    {
    case 1:
        this->andLogic();
        break;

    case 4:
        this->andLogic();
        break;

    case 5:
        this->orLogic();
        break;

    case 6:
        this->orLogic();
        break;

    case 7:
        this->xorLogic();
        break;

    case 8:
        this->xorLogic();
        break;
    }
}

// Function to center gate upon moving
void Gate::setCenterPos()
{
    this->out->centerPoint = this->pos() + this->rect->pos();
    this->out->centerPoint.setX(this->out->centerPoint.x() + this->rect->rect().width() + this->out->rect().width()/2);

    for(int i = 0; i < list_Inputs.size(); i++)
    {
        this->list_Inputs.at(i)->centerPoint = this->pos();
        this->list_Inputs.at(i)->centerPoint.setX(this->list_Inputs.at(i)->centerPoint.x() + this->plus - plusB
                                                  - this->rect->rect().width() - this->out->rect().width()/2);

        this->list_Inputs.at(i)->centerPoint.setY(this->list_Inputs.at(i)->centerPoint.y()
                                                  + (i)*rect->rect().height() + (i+1)*space);
    }
}

// Function handling AND logic of gate
void Gate::andLogic()
{
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
    LogicalOutput = def;
    for(int i = 0; i < list_Inputs.size(); i++)
    {
        if(list_Inputs.at(i)->Logic == 0)
        {
            LogicalOutput = change;
            return;
        }
    }
}

void Gate::orLogic()
{
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
    LogicalOutput = def;
    for(int i = 0; i < list_Inputs.size(); i++)
    {
        if(list_Inputs.at(i)->Logic == 1)
        {
            LogicalOutput = change;
            return;
        }
    }
}

void Gate::xorLogic()
{
    int change = list_Inputs.at(0)->Logic;
    bool bCheck = true;
    for(int i = 0; i < list_Inputs.size(); i++)
    {
        if(!(change == list_Inputs.at(i)->Logic))
        {
            bCheck = false;
            break;
        }
    }
    if(bCheck == false)
    {
        LogicalOutput = 1;
        if(this->isNot == true)
        {
            LogicalOutput = 0;
        }
    }
    else
    {
        LogicalOutput = 0;
        if(this->isNot == true)
        {
            LogicalOutput = 1;
        }
    }
}
