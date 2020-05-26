#ifndef BUTTONPANEL_H
#define BUTTONPANEL_H

#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QPainter>

class ButtonPanel: public QGraphicsRectItem
{
public:
    ButtonPanel();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // BUTTONPANEL_H
