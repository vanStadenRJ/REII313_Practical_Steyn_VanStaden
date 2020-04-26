#ifndef BUILDMODE_H
#define BUILDMODE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QPixmap>

class BuildMode: public QGraphicsPixmapItem
{
public:
    BuildMode(QGraphicsItem * parent=0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // BUILDMODE_H
