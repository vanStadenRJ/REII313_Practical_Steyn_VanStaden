#include "Wire.h"
#include "Simulation.h"

extern Simulation * simulation;

Wire::Wire()
{
    // Set ZValue to 0 to enable wire to be under the input nodes
    setZValue(0);

    // Set visual of wire to be moved and placed
    QPen pen;
    pen.setWidth(5);
    pen.setCapStyle(Qt::RoundCap);
    pen.setColor(Qt::magenta);
    this->setPen(pen);

    // Set effect to nullptr, needs to be clicked on to create new effect
    this->effect = nullptr;

    // Connect Signals and Slots
    QObject::connect(simulation, SIGNAL(unWire()), this, SLOT(deleteEffect()));
    QObject::connect(simulation, SIGNAL(changeWireColor()), this, SLOT(colorLogic()));

    // Item can respond to keypress event
    this->setFlag(QGraphicsItem::ItemIsFocusable);
}

void Wire::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Complemented each wire with visual appealing look
    QPainterPath outline;
    outline.moveTo(line().p1());
    outline.lineTo(line().p2());
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    QPen pen1;
    pen1.setColor(QColor(0,0,0));
    pen1.setWidth(4 + pen().width());
    pen1.setCapStyle(Qt::RoundCap);
    painter->strokePath(outline, pen1);
    painter->setPen(pen());
    pen().setCapStyle(Qt::RoundCap);
    painter->drawLine(line());
    painter->restore();
}

void Wire::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // Wire needs to be selected to be able to be deleted
    this->setFocus();
    if(effect == nullptr)
    {
        this->effect = new QGraphicsDropShadowEffect();
        if(event->button() == Qt::LeftButton)
        {
            this->effect->setEnabled(true);
            this->effect->setColor(Qt::lightGray);
            this->effect->setOffset(8);
        }        
    }
    else
    {
        this->effect->setEnabled(true);
    }
    this->setFocus();
    this->setGraphicsEffect(effect);
}

void Wire::keyPressEvent(QKeyEvent *event)
{
    // Wire needs to be selected before it can be removed and deleted
    if(effect->isEnabled() && event->key() == Qt::Key_Delete)
    {
        simulation->nr_Wires = simulation->nr_Wires - 1;
        bool bFound = false;
        int i = 0;

        // Loop until specific wire found in list, and then remove from list
        while(bFound == false)
        {
            //int n = simulation->list_Gates.at(i)->list_Inputs.size();
            if(simulation->list_Gates.at(i)->gate_Nr == this->dest_Gate)
            {
                for(int j = 0; j < simulation->list_Gates.at(i)->list_Inputs.size(); j++)
                {
                    if(simulation->list_Gates.at(i)->list_Inputs.at(j)->posGate == this->dest_NodeNr)
                    {
                        bFound = true;
                        simulation->list_Gates.at(i)->list_Inputs.at(j)->connected = false;
                        simulation->list_Gates.at(i)->list_Inputs.at(j)->setBrush(QBrush(QColor(255,255,255)));
                        simulation->list_Gates.at(i)->list_Inputs.at(j)->Logic = 0;
                    }
                }
            }
            i++;
        }

        // Upon Delete of Wire, Remove Wire from list of wires
        for(int v = 0; v < simulation->list_Wires.size(); v++)
        {
            if(simulation->list_Wires.at(v)->source == this->source && simulation->list_Wires.at(v)->dest == this->dest)
            {
                simulation->list_Wires.takeAt(v);
                break;
            }
        }

        // Update Logic of whole schematic
        simulation->updateWireLogic();

        // Set effect to nullptr before wire deleted
        this->prepareGeometryChange();
        this->effect = nullptr;

        // Delete wire
        delete this;
        return;
    }
}

void Wire::deleteEffect()
{
    // Disable effect if user clicks anywhere else after clicked on wire
    this->prepareGeometryChange();
    if (!(effect == nullptr))
    {
        effect->setEnabled(false);
    }
}

void Wire::colorLogic()
{
    // If wire has high(1) logic: Color = blue
    // If wire has low(0) logic: Color = white
    if(this->Logic_Wire == 1)
    {
        QPen pen;
        pen.setColor(QColor(0,75,200));
        pen.setWidth(5);
        pen.setCapStyle(Qt::RoundCap);
        this->setPen(pen);
    }
    else
    {
        QPen pen;
        pen.setColor(QColor(255,255,255));
        pen.setWidth(5);
        pen.setCapStyle(Qt::RoundCap);
        this->setPen(pen);
    }
}
