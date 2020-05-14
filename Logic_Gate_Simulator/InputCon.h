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
    void mousePressEvent(QGraphicsSceneMouseEvent * event);

    QPointF wire_Pos;
    int parent_Gate;
    bool connected;
    bool test;
    int posGate;

    int Logic;

public slots:
    void OutputToInput();
    void clearNode();
    void conNode(int k);

private:
};

#endif // INPUTCON_H
