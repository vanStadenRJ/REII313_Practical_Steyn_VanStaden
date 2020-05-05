#include "Gate.h"
#include "Simulation.h"
#include <QDebug>
#include <QInputDialog>
#include <QGraphicsBlurEffect>
#include <QtGui>
#include <QList>

extern Simulation * simulation;

Gate::Gate(uint gateNr)
{
    this->setPixmap(QPixmap(":/images/And_Gate.png"));
    this->gate_Nr = gateNr;

    // set draw output branch
    rect = new QGraphicsRectItem(this);
    rect->setRect(x(), y(), 20, 5);
    rect->setParentItem(this);
    rect->setPos(pixmap().width()-5, pixmap().height()/2 - rect->rect().height()/2);
    out = new OutputCon(rect);
    out->setParentItem(rect);
    out->setPos(rect->rect().width(), rect->rect().height()/2 - out->rect().height()/2);
    out->parent_Gate = gate_Nr;

    input_size = QInputDialog::getInt(simulation, "Logic Gate Input Selector", "Input Count", 2, 2, 5);
    space = (pixmap().height() - input_size*5)/(input_size+1);

    for(int i = 1; i <= input_size; i++)
    {
        input_rect = new QGraphicsRectItem(this);
        input_rect->setRect(x(), y(), 20, 5);
        input_rect->setParentItem(this);
        input_rect->setPos(this->x() - input_rect->rect().width()+3, space*i + input_rect->rect().height()*(i-1));
        in = new InputCon(input_rect);
        in->setParentItem(input_rect);
        in->setPos(-in->rect().width(), - in->rect().height()/2 + input_rect->rect().height()/2);
        in->parent_Gate = gate_Nr;
    }

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
            qDebug() << this->gate_Nr;
        }
    }
}

void Gate::keyPressEvent(QKeyEvent *event)
{
    if(effect->isEnabled() && event->key() == Qt::Key_Delete)
    {
        if(!(simulation->list_Wires.size() == 0))
        {
            for(int i = 0, n = simulation->list_Wires.size(); i < n; ++i)
            {
                if((simulation->list_Wires[i]->src_Gate == this->gate_Nr) || (simulation->list_Wires[i]->dest_Gate == this->gate_Nr))
                {
                    simulation->scene->removeItem(simulation->list_Wires[i]);
                    delete simulation->list_Wires[i];
                    //return;
                }
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
