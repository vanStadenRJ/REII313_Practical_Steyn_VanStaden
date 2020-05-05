#include "Wire.h"
#include "Simulation.h"

#include <QPen>
#include <QDebug>

extern Simulation * simulation;

Wire::Wire()
{
    QPen pen;
    pen.setWidth(5);
    pen.setCapStyle(Qt::RoundCap);
    this->setPen(pen);

    effect = nullptr;
    QObject::connect(simulation, SIGNAL(unWire()), this, SLOT(deleteEffect()));
    this->setFlag(QGraphicsItem::ItemIsFocusable);
}

void Wire::mousePressEvent(QGraphicsSceneMouseEvent *event)
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

            QPen pen;
            pen.setWidth(6);
            pen.setCapStyle(Qt::RoundCap);
            this->setPen(pen);
        }
        qDebug() << this->src_Gate << "->" << this->dest_Gate;
    }
}

void Wire::keyPressEvent(QKeyEvent *event)
{
    if(effect->isEnabled() && event->key() == Qt::Key_Delete)
    {
        delete this;
        return;
    }
}

void Wire::deleteEffect()
{
    if (!(effect == nullptr))
    {
        effect->setEnabled(false);
        this->setGraphicsEffect(effect);
        effect = nullptr;
        this->clearFocus();

        QPen pen;
        pen.setWidth(5);
        pen.setCapStyle(Qt::RoundCap);
        this->setPen(pen);
    }
}
