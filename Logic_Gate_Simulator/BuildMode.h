#ifndef BUILDMODE_H
#define BUILDMODE_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
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
    // Private Attributes
    QCursor cur;
};

#endif // BUILDMODE_H
