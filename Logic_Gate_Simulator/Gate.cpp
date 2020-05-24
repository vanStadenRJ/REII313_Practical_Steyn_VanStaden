#include "Gate.h"
#include "Simulation.h"

extern Simulation * simulation;

Gate::Gate(uint gateNr, uint typeGate)
{
    qDebug() << simulation->list_Gates.size();
    // Set default values
    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->isMove = false;
    this->effect = nullptr;

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
            this->LogicalOutput = 1;                                    // Set logic of gate
        }
        else                                                            // If type Low Input
        {
            this->setPixmap(QPixmap(":/images/Low_Icon.png"));
            this->LogicalOutput = 0;                                    // Set logic of gate
        }
    }
    else
    {
        this->setPixmap(QPixmap(":/images/And_Gate.png"));
        this->LogicalOutput = 0;

        // For different input size, nr of input nodes need to be configured
        input_size = QInputDialog::getInt(simulation, "Logic Gate Input Selector", "Input Count", 2, 2, 5);
        space = (pixmap().height() - input_size*2)/(input_size+1);
        for(int i = 1; i <= input_size; i++)
        {
            // input_rect is visual connection of node and gate
            input_rect = new QGraphicsRectItem(this);
            input_rect->setRect(x(), y(), 20, 2);
            input_rect->setParentItem(this);
            input_rect->setPos(this->x() - input_rect->rect().width()+3,
                               space*i + input_rect->rect().height()*(i-1));

            QBrush brush;
            brush.setColor(Qt::black);
            brush.setStyle(Qt::SolidPattern);
            input_rect->setBrush(brush);

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
    rect->setRect(x(), y(), 20, 2);
    QBrush brush;
    brush.setColor(Qt::black);
    brush.setStyle(Qt::SolidPattern);
    rect->setBrush(brush);
    rect->setParentItem(this);
    switch (typeGate)
    {
    case 1:
        rect->setPos(pixmap().width()-5, pixmap().height()/2 - rect->rect().height()/2);
        this->updateLogic();
        break;

    case 2:
        rect->setPos(pixmap().width()-2, pixmap().height()/2 - rect->rect().height()/2);
        break;

    case 3:
        rect->setPos(pixmap().width()-2, pixmap().height()/2 - rect->rect().height()/2);
        break;
    }

    // set output nodes and configure
    out = new OutputCon(rect);
    out->setParentItem(rect);
    out->setPos(rect->rect().width(), rect->rect().height()/2 - out->rect().height()/2);
    //out->centerPoint = this->pos() + rect->pos() + out->rect().center();
    this->list_Outputs << out;
    out->parent_Gate = gate_Nr;


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
            QCursor cur = QCursor(QPixmap(":/images/And_Gate.png"));
            simulation->setCursor(cur);
            simulation->isMove = true;
            this->isMove = true;
            simulation->moveGate = this->gate_Nr;
        }
    }

    // Left Button to show effect and make gate ready for delete
    if(effect == nullptr)
    {
        effect = new QGraphicsDropShadowEffect();
        if(event->button() == Qt::LeftButton)
        {
            effect->setEnabled(true);
            effect->setColor(Qt::lightGray);
            effect->setOffset(8);
            this->setGraphicsEffect(effect);
            this->setFocus();
            qDebug() << "Gate " << this->gate_Nr << ": " << this->LogicalOutput;
        }
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
            // Update Logic Before Delete of gate
            emit simulation->clear_Node(true);

            // Delete all wires connected to gate to be deleted
            int i = 0;
            int n = simulation->list_Wires.size();
            while(i < n)
            {
                if((simulation->list_Wires.at(i)->src_Gate == this->gate_Nr) || (simulation->list_Wires.at(i)->dest_Gate == this->gate_Nr))
                {
                    qDebug() << "Toets";
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
        this->setGraphicsEffect(effect);
        effect = nullptr;
        this->clearFocus();
    }
}

// Update Logic of gate when new wires connected and deleted
void Gate::updateLogic()
{
    LogicalOutput = 1;
    for(int i = 0; i < list_Inputs.size(); i++)
    {
        //list_Inputs.at(i)->Logic =
        if(list_Inputs.at(i)->Logic == 0)
        {
            LogicalOutput = 0;
            break;
        }
    }
}

void Gate::setCenterPos()
{
    this->out->centerPoint = this->pos() + this->rect->pos();
    this->out->centerPoint.setX(this->out->centerPoint.x() + this->rect->rect().width() + this->out->rect().width()/2);

    for(int i = 0; i < list_Inputs.size(); i++)
    {


        this->list_Inputs.at(i)->centerPoint = this->pos();
        this->list_Inputs.at(i)->centerPoint.setX(this->list_Inputs.at(i)->centerPoint.x()
                                                  - this->rect->rect().width() - this->out->rect().width()/2);

        this->list_Inputs.at(i)->centerPoint.setY(this->list_Inputs.at(i)->centerPoint.y()
                                                  + (i)*rect->rect().height() + (i+1)*space);

    }
}
