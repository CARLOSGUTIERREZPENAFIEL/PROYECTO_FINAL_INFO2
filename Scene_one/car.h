#ifndef CAR_H
#define CAR_H

#include <QGraphicsPixmapItem>

class Car : public QGraphicsPixmapItem
{
public:
    Car(const QString &filePath, QGraphicsItem *parent = nullptr);
    void turnLeft();
    void turnRight();
    void resetPixmap();
    void updatePosition(qreal vel_x, qreal vel_y);

private:
    QPixmap carPixmap;
    QPixmap carPixmapLeft;
    QPixmap carPixmapRight;
};

#endif // CAR_H
