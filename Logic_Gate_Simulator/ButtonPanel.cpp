#include "ButtonPanel.h"
#include "Simulation.h"

#include <QFont>

extern Simulation * simulation;

ButtonPanel::ButtonPanel()
{
    this->setZValue(0);
    //this->setRect(0,0,300,860);

    QGraphicsTextItem * input = new QGraphicsTextItem(this);
    input->setPlainText("INPUT COMPONENTS");
    QFont seriFont("Times", 12, QFont::Bold);
    input->setDefaultTextColor(QColor(0,0,0));
    input->setFont(seriFont);
    input->setPos(300/2-input->boundingRect().width()/2, 10);


    QGraphicsTextItem * logic = new QGraphicsTextItem(this);
    logic->setPlainText("LOGIC GATES");
    logic->setDefaultTextColor(QColor(0,0,0));
    logic->setFont(seriFont);
    logic->setPos(300/2-logic->boundingRect().width()/2, 250);

    QGraphicsTextItem *output = new QGraphicsTextItem(this);
    output->setPlainText("OUTPUT COMPONENTS");
    output->setDefaultTextColor(QColor(0,0,0));
    output->setFont(seriFont);
    output->setPos(300/2-output->boundingRect().width()/2, 700);
    //output->setPos(20, 600);
}

void ButtonPanel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QColor(Qt::lightGray));

    QPen pen;
    pen.setWidth(3);
    painter->setPen(pen);
    painter->drawRoundedRect(7, 7, 300, 860, 5, 5);
}
