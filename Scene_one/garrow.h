#ifndef GARROW_H
#define GARROW_H

#include<QGraphicsItem>

class GArrow : public QGraphicsItem
{
public:
    GArrow(QGraphicsItem *parent = nullptr);

    void setSize(double size)
    {
        mSize = size;
    }

    void setColor(const QColor &color)
    {
        mColor = color;
    }

    void setFirstPoint(const QPointF &p)
    {
        mFirstPoint = p;
    }
    void setSecondPoint(const QPointF &q)
    {
        mSecondPoint = q;
    }
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
private:
    double mSize;
    QColor mColor;
    QPointF mFirstPoint;
    QPointF mSecondPoint;
};

#endif // GARROW_H
