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
    uint dest_Gate;

    QGraphicsDropShadowEffect * effect;

    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void keyPressEvent(QKeyEvent * event);

    bool draw;

public slots:
    void deleteEffect();
};

#endif // WIRE_H
