#ifndef WIRE_H
#define WIRE_H

#include <QGraphicsLineItem>
#include <QObject>
#include <QPointF>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsEffect>
#include <QKeyEvent>

class Wire: public QObject, public QGraphicsLineItem
{
    Q_OBJECT
public:
    Wire();

    QPointF source;
    QPointF dest;
    uint src_Gate;
    uint src_NodeNr;
    uint dest_Gate;
    uint dest_NodeNr;

    int Logic_Wire;

    QGraphicsDropShadowEffect * effect;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void keyPressEvent(QKeyEvent * event);
    bool draw;

public slots:
    void deleteEffect();
    void colorLogic();
};

#endif // WIRE_H
