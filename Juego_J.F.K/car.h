#ifndef CAR_H
#define CAR_H

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QObject>

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

class Obstacle : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Obstacle(const QString &filePath, qreal pos_obst, QGraphicsItem *parent = nullptr);
    void startMoving();

public slots:
    void moveDown();

private:
    QPixmap obstaclePixmap;
    QTimer *moveTimer;
    int pos_obsta;
    bool moveUp; // Flag to determine the direction of movement
};

#endif // CAR_H
