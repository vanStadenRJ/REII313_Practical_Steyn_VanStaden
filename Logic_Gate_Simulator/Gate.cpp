#include "Gate.h"
#include "Simulation.h"
#include "Highlight.h"
#include <QDebug>
#include <QInputDialog>
#include <QGraphicsBlurEffect>
#include <QtGui>

extern Simulation * simulation;

Gate::Gate(QGraphicsItem *parent)
{
    this->setPixmap(QPixmap(":/images/And_Gate.png"));

    // set draw output branch
    rect = new QGraphicsRectItem(this);
    rect->setRect(x(), y(), 20, 5);
    rect->setPos(pixmap().width()-5, pixmap().height()/2 - rect->rect().height()/2);

    input_size = QInputDialog::getInt(simulation, "Logic Gate Input Selector", "Input Count", 2, 2, 5);
    space = (pixmap().height() - input_size*5)/(input_size+1);

    for(int i = 1; i <= input_size; i++)
    {
        input_rect = new QGraphicsRectItem(this);
        input_rect->setRect(x(), y(), 20, 5);
        input_rect->setPos(this->x() - input_rect->rect().width()+3, space*i + input_rect->rect().height()*(i-1));
    }

    effect = nullptr;
    QObject::connect(simulation, SIGNAL(un_Select()), this, SLOT(deleteEffect()));
}

void Gate::Output()
{
    out = new OutputCon();
    out->setPos(x()+ pixmap().width()-5 + rect->rect().width(),y() + pixmap().height()/2 - rect->rect().height()/2 +
                rect->rect().height()/2 - out->rect().height()/2);
    simulation->scene->addItem(out);
    out->source = simulation->mapFromGlobal(QCursor::pos());
}

void Gate::Input()
{
    for(int i = 1; i <= input_size; i++)
    {
        //input_rect = new QGraphicsRectItem(this);
        in = new InputCon();
        in->setPos(x() - input_rect->rect().width()+3 - in->rect().width(),
                   y() + space*i + input_rect->rect().height()*(i-1) - in->rect().height()/2 + input_rect->rect().height()/2);
        simulation->scene->addItem(in);
    }
}

void Gate::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    effect = new QGraphicsDropShadowEffect();
    if(event->button() == Qt::LeftButton)
    {
        effect->setEnabled(true);
        effect->setColor(Qt::lightGray);
        effect->setOffset(8);
        this->setGraphicsEffect(effect);
    }
}

void Gate::deleteEffect()
{
    if (!(effect == nullptr))
    {
        effect->setEnabled(false);
        this->setGraphicsEffect(effect);
        effect = nullptr;
    }
}
