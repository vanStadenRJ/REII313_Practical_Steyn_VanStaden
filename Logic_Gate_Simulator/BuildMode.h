#ifndef BUILDMODE_H
#define BUILDMODE_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QPixmap>
#include <QCursor>

class BuildMode: public QGraphicsPixmapItem
{
public:
    // Constructors
    BuildMode(int typeIcon);

    // Public Methods
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    // Public Attributes
    int Icon;

private:
    // Private Methods
    QCursor cur;
};

#endif // BUILDMODE_H
