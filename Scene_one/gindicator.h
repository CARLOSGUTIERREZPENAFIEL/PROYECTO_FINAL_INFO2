#ifndef GINDICATOR_H
#define GINDICATOR_H

#include <QGraphicsObject>

class GArrow;
class GNeedle;

class GIndicator : public QGraphicsObject
{
    Q_OBJECT
public:
    enum Position
    {
        FIRST_POS,
        SECOND_POS,
        THIRD_POS,
        FOURTH_POS,
        FIFTH_POS,
        SIXTH_POS,
        SEVENTH_POS,
        EIGHTH_POS,
        NINETH_POS,
        TENTH_POS
    };

    GIndicator(QGraphicsItem *parent = nullptr);

    void incrementPosition(int steps = 1);
    void decrementPosition(int steps = 1);
    void updatePositionBasedOnSpeed(int speed);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;

private:
    int mPosition;
    GArrow *mArrow;
    GNeedle *mNeedle;

    QColor getArrowColor();
    QPointF getSecondPoint() const;
    void fillCircle(QPainter *painter);

    static QPointF sFirstPoint;
};

#endif // GINDICATOR_H
