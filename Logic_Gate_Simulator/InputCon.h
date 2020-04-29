#ifndef INPUTCON_H
#define INPUTCON_H

#include <QGraphicsItem>
#include <QObject>
#include <QGraphicsEllipseItem>

class InputCon: public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    InputCon(QGraphicsItem * parent = 0);
};

#endif // INPUTCON_H
