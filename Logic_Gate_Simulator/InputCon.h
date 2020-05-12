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
    uint parent_Gate;
    bool connected;
    bool test;
    int posGate;

public slots:
    void OutputToInput();
    void clearNode();
    void conNode();

private:
};

#endif // INPUTCON_H
