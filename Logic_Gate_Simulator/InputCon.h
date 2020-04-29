#ifndef INPUTCON_H
#define INPUTCON_H

#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QObject>

class InputCon: public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    InputCon(QGraphicsItem * parent);
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);

    QPointF source;

public slots:
    //void changeColor();

private:
};

#endif // INPUTCON_H
