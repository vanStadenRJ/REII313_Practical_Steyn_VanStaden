#ifndef BUILDMODE_H
#define BUILDMODE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QPixmap>
#include <QCursor>

class BuildMode: public QGraphicsPixmapItem
{
public:
    BuildMode(uint typeIcon);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    QCursor cur;
    uint Icon;
};

#endif // BUILDMODE_H
