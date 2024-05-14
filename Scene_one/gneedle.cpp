#include "gneedle.h"
#include <QPainter>

GNeedle::GNeedle(QGraphicsItem *parent)
    : QGraphicsItem { parent }
{
    mWidth = 0;
}
void GNeedle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    (void) option;
    (void) widget;
    QPen pen(mColor);
    pen.setWidth(mWidth);
    painter->setPen(pen);
    painter->drawLine(mFirstPoint, mSecondPoint);
}

QRectF GNeedle::boundingRect() const
{
    return QRectF();
}

