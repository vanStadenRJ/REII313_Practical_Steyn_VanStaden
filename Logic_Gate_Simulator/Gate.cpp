#include "Gate.h"
#include "Simulation.h"
#include <QDebug>
#include <QInputDialog>

extern Simulation * simulation;

Gate::Gate(QGraphicsItem *parent)
{
    this->setPixmap(QPixmap(":/images/And_Gate.png"));
    //rect = new QGraphicsRectItem(this);
    //rect->setRect(x()+50, y()+50, 50, 50);

    // set draw output branch
    rect = new QGraphicsRectItem(this);
    rect->setRect(x(), y(), 20, 5);
    rect->setPos(pixmap().width()-5, pixmap().height()/2 - rect->rect().height()/2);

//    circle = new QGraphicsEllipseItem(rect);
//    circle->setRect(x(), y(), 10, 10);
//    circle->setPos(rect->rect().width(),rect->rect().height()/2 - circle->rect().height()/2);

//    ye = new InputSize();
//    ye->show();
//    input_size = ye->size;
//    //ye->close();
//    qDebug() << input_size;
    qDebug() << pixmap().height();

    input_size = QInputDialog::getInt(simulation, "Logic Gate Input Selector", "Input Count", 2, 2, 5);
    space = (pixmap().height() - input_size*5)/(input_size+1);

    for(int i = 1; i <= input_size; i++)
    {
        input_rect = new QGraphicsRectItem(this);
        input_rect->setRect(x(), y(), 20, 5);
        input_rect->setPos(this->x() - input_rect->rect().width()+3, space*i + input_rect->rect().height()*(i-1));
    }
}

void Gate::Output()
{
    out = new OutputCon();
    out->setPos(x()+ pixmap().width()-5 + rect->rect().width(),y() + pixmap().height()/2 - rect->rect().height()/2 +
                rect->rect().height()/2 - out->rect().height()/2);
    simulation->scene->addItem(out);
    out->source = simulation->mapFromGlobal(QCursor::pos());
}
