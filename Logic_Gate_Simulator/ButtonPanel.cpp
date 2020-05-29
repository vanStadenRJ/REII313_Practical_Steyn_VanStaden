#include "ButtonPanel.h"
#include "Simulation.h"

#include <QFont>

extern Simulation * simulation;

ButtonPanel::ButtonPanel()
{
    this->setZValue(0);
    //this->setRect(0,0,300,860);

    QGraphicsTextItem * text = new QGraphicsTextItem(this);
    text->setPlainText("Intput Components");
    QFont seriFont("Times", 12, QFont::Bold);
    text->setDefaultTextColor(QColor(0,0,0));
    text->setFont(seriFont);
    text->setPos(300/2-text->boundingRect().width()/2, 10);
}

void ButtonPanel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QColor(Qt::lightGray));

    QPen pen;
    pen.setWidth(3);
    painter->setPen(pen);
    painter->drawRoundedRect(7, 7, 300, 860, 5, 5);
}
