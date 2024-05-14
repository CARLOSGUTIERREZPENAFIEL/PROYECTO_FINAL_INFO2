#include "gindicator.h"
#include "gscene.h"
#include "garrow.h"
#include "gneedle.h"
#include <QPainter>

static QPointF getFirstPoint()
{
    const double sWidth = GScene::sceneWidth();
    const double sHeight = GScene::sceneHeight();
    const double x = sWidth / 2.0;
    const double y = sHeight / 2.0;
    return QPointF(x, y);
}

QPointF GIndicator::sFirstPoint = getFirstPoint();

GIndicator::GIndicator(QGraphicsItem *parent)
    : QGraphicsObject { parent }
{
    mNeedle = new GNeedle(this);
    mArrow = new GArrow(this);
    mPosition = FIRST_POS;
}

void GIndicator::incrementPosition(int steps)
{
    mPosition += steps;
    if(mPosition > TENTH_POS)
    {
        mPosition = TENTH_POS;
    }
}

void GIndicator::decrementPosition(int steps)
{
    mPosition -= steps;
    if (mPosition < FIRST_POS)
    {
        mPosition = FIRST_POS;
    }
}

void GIndicator::updatePositionBasedOnSpeed(int speed)
{
    mPosition = speed / 10; // Divide la velocidad por 10 para determinar la posición
    if (mPosition > TENTH_POS)
    {
        mPosition = TENTH_POS;
    }
    if (mPosition < FIRST_POS)
    {
        mPosition = FIRST_POS;
    }
    update(); // Llama a update para redibujar el indicador
}

void GIndicator::fillCircle(QPainter *painter)
{
    painter->setBrush(Qt::white);
    painter->drawEllipse(sFirstPoint, 20.0, 20.0);
}

QColor GIndicator::getArrowColor()
{
    switch (mPosition)
    {
    case FIRST_POS:
    case SECOND_POS:
    case THIRD_POS:
    case FOURTH_POS:
    case FIFTH_POS:
    case SIXTH_POS:
        return Qt::green;
    case SEVENTH_POS:
        return Qt::yellow;
    case EIGHTH_POS:
        return QColor("#FFA500");
    case NINETH_POS:
    case TENTH_POS:
        return Qt::red;
    }
    return QColor();
}

void GIndicator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    (void) option;
    (void) widget;
    fillCircle(painter);
    QPointF secondPoint = getSecondPoint();
    mNeedle->setWidth(6);
    mNeedle->setColor(Qt::white);
    mNeedle->setFirstPoint(sFirstPoint);
    mNeedle->setSecondPoint(secondPoint);
    mArrow->setSize(20.0);
    mArrow->setColor(getArrowColor());
    mArrow->setFirstPoint(sFirstPoint);
    mArrow->setSecondPoint(secondPoint);
}

QRectF GIndicator::boundingRect() const
{
    return QRectF();
}

QPointF GIndicator::getSecondPoint() const
{
    switch (mPosition)
    {
    case FIRST_POS: return QPointF(63, 185); //185 63
    case SECOND_POS: return QPointF(41, 146);
    case THIRD_POS: return QPointF(41, 102); //83 242
    case FOURTH_POS: return QPointF(63, 63);
    case FIFTH_POS: return QPointF(102, 41);
    case SIXTH_POS: return QPointF(147, 41);
    case SEVENTH_POS: return QPointF(184, 64);
    case EIGHTH_POS: return QPointF(207, 102);
    case NINETH_POS: return QPointF(207, 146);
    case TENTH_POS: return QPointF(184,184);
    }
    return QPointF();
}
