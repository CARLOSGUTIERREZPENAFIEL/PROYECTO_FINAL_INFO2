#ifndef GNEEDLE_H
#define GNEEDLE_H

#include <QGraphicsItem>

class GNeedle : public QGraphicsItem
{
public:
    GNeedle(QGraphicsItem *parent = nullptr);

    void setWidth(int width)
    {
        mWidth = width;
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
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *style, QWidget *widget) override;
    QRectF boundingRect() const override;
private:
    int mWidth;
    QColor mColor;
    QPointF mFirstPoint;
    QPointF mSecondPoint;
};

#endif // GNEEDLE_H
