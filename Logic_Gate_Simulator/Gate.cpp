#include "Gate.h"
#include "Simulation.h"
#include <QDebug>
#include <QInputDialog>
#include <QGraphicsBlurEffect>
#include <QtGui>


extern Simulation * simulation;

Gate::Gate(uint gateNr)
{
    this->setPixmap(QPixmap(":/images/And_Gate.png"));
    this->gate_Nr = gateNr;
    this->outputGate = 0;
    this->LogicalOutput = 0;

    // set draw output branch
    rect = new QGraphicsRectItem(this);
    rect->setRect(x(), y(), 20, 5);
    rect->setParentItem(this);
    rect->setPos(pixmap().width()-5, pixmap().height()/2 - rect->rect().height()/2);
    out = new OutputCon(rect);
    out->setParentItem(rect);
    out->setPos(rect->rect().width(), rect->rect().height()/2 - out->rect().height()/2);
    this->list_Outputs << out;
    out->parent_Gate = gate_Nr;

    input_size = QInputDialog::getInt(simulation, "Logic Gate Input Selector", "Input Count", 2, 2, 5);
    space = (pixmap().height() - input_size*5)/(input_size+1);

    for(int i = 0; i < 5; i++)
    {
        arrInput[i] = 0;
    }

    for(int i = 1; i <= input_size; i++)
    {
        input_rect = new QGraphicsRectItem(this);
        input_rect->setRect(x(), y(), 20, 5);
        input_rect->setParentItem(this);
        input_rect->setPos(this->x() - input_rect->rect().width()+3, space*i + input_rect->rect().height()*(i-1));
        in = new InputCon(input_rect);
        in->setParentItem(input_rect);
        in->setPos(-in->rect().width(), - in->rect().height()/2 + input_rect->rect().height()/2);
        in->posGate = i;
        in->parent_Gate = gate_Nr;
        list_Inputs << in;
    }
    this->updateLogic();

    effect = nullptr;
    QObject::connect(simulation, SIGNAL(un_Select()), this, SLOT(deleteEffect()));

    this->setFlag(QGraphicsItem::ItemIsFocusable);
}

void Gate::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
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
}

void Gate::keyPressEvent(QKeyEvent *event)
{
    if(effect->isEnabled() && event->key() == Qt::Key_Delete)
    {
        if(!(simulation->nr_Wires == 0))
        {
            int i = 0;
            int n = simulation->list_Wires.size();
            while(i < n)
            {
                if((simulation->list_Wires.at(i)->src_Gate == this->gate_Nr) || (simulation->list_Wires.at(i)->dest_Gate == this->gate_Nr))
                {
                    delete simulation->list_Wires.takeAt(i);
                    i--;
                    n--;
                    simulation->nr_Wires = simulation->nr_Wires - 1;
                }
                i++;
            }
        }
        delete this;
        return;
    }
}

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

void Gate::updateLogic()
{
    LogicalOutput = 1;
    for(int i = 0; i < list_Inputs.size(); i++)
    {
        if(list_Inputs.at(i)->Logic == 0)
        {
            LogicalOutput = 0;
            break;
        }
        qDebug() << list_Inputs.at(i)->Logic;
    }
}
