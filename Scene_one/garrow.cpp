#include "garrow.h"
#include <QPainter>
#include <QtMath>

GArrow::GArrow(QGraphicsItem * parent)
    : QGraphicsItem { parent }
{
    mSize = 0.0;
}

void GArrow::paint(QPainter * painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    (void) option;
    (void) widget;
    const double x1 = mFirstPoint.x();
    const double y1 = mFirstPoint.y();
    const double x2 = mSecondPoint.x();
    const double y2 = mSecondPoint.y();
    const double alpha = qAtan2(y2-y1, x2-x1);
    const double distance =qSqrt(qPow(x2-x1, 2.0)+qPow(y2-y1, 2.0));
    const double dx = distance * qCos(alpha);
    const double dy = distance* qSin(alpha);
    double theta = qAcos(dx / distance);
    if (dy >= 0.0)
    {
        theta = (M_PI * 2.0) - theta;
    }
    QPointF arrowP1= mSecondPoint - QPointF(qSin(theta + M_PI/3.0) * mSize, qCos(theta + M_PI/3.0) * mSize);
    QPointF arrowP2 = mSecondPoint - QPointF(qSin(theta + M_PI - M_PI/3.0) *mSize, qCos(theta + M_PI - M_PI/3.0) * mSize);
    QPolygonF arrow;
    arrow << mSecondPoint << arrowP1 << arrowP2;
    painter->setPen(mColor);
    painter->setBrush(mColor);
    painter->drawPolygon(arrow);
}

QRectF GArrow::boundingRect() const
{
    return QRectF();
}
