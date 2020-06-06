#ifndef WIRE_H
#define WIRE_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QGraphicsEffect>
#include <QKeyEvent>
#include <QObject>
#include <QPointF>
#include <QPen>

class Wire: public QObject, public QGraphicsLineItem
{
    Q_OBJECT
public:
    Wire();

    QPointF source;
    QPointF dest;
    int src_Gate;
    int src_NodeNr;
    int dest_Gate;
    int dest_NodeNr;

    int Logic_Wire;

    QGraphicsDropShadowEffect * effect;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void keyPressEvent(QKeyEvent * event);
    bool draw;

public slots:
    void deleteEffect();
    void colorLogic();
};

#endif // WIRE_H
