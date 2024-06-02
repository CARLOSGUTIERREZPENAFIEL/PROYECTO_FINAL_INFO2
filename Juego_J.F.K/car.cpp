#include "car.h"
#include <QGraphicsScene>

Car::Car(const QString &filePath, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent),
    carPixmap(filePath),
    carPixmapLeft(":/imagenes/carro_jfk_izq.png"),
    carPixmapRight(":/imagenes/carro_jfk_der.png")
{
    setPixmap(carPixmap);
    setScale(0.25);
}

void Car::turnLeft() {
    setPixmap(carPixmapLeft);
}

void Car::turnRight() {
    setPixmap(carPixmapRight);
}

void Car::resetPixmap() {
    setPixmap(carPixmap);
}

void Car::updatePosition(qreal vel_x, qreal vel_y) {
    setPos(pos().x() + vel_x, pos().y() - vel_y);
}

Obstacle::Obstacle(const QString &filePath, qreal pos_obst, QGraphicsItem *parent)
    : QObject(),
    QGraphicsPixmapItem(parent),
    obstaclePixmap(filePath),
    moveTimer(new QTimer(this)),
    pos_obsta(pos_obst),
    moveUp(false) // Initialize the flag
{
    setScale(0.18);

    int randomX;
    if (rand() % 2 == 0) { // 50% chance for each range
        randomX = 640 + (rand() % (890 - 640)); // Range 640 to 890
        int randomImageIndex = 1 + (rand() % 6); // Random index between 1 and 6
        obstaclePixmap = QPixmap(QString(":/imagenes/img%1.png").arg(randomImageIndex));
    } else {
        randomX = 1150 + (rand() % (1370 - 1150)); // Range 1150 to 1370
        int randomImageIndex = 7 + (rand() % 6); // Random index between 7 and 12
        obstaclePixmap = QPixmap(QString(":/imagenes/img%1.png").arg(randomImageIndex));
        moveUp = true; // Set the flag to true if in the second range
    }

    setPixmap(obstaclePixmap);
    setPos(randomX, pos_obst - 200); // Start at the top
    connect(moveTimer, &QTimer::timeout, this, &Obstacle::moveDown);
}

void Obstacle::startMoving() {
    moveTimer->start(50); // Move the obstacle every 50 ms
}

void Obstacle::moveDown() {
    if (moveUp) {
        setPos(pos().x(), pos().y() - 10); // Move up
    } else {
        setPos(pos().x(), pos().y() + 10); // Move down
    }

    // Remove the obstacle if it goes off-screen
    if (pos().y() > 1078 + pos_obsta) {
        if (scene()) {
            scene()->removeItem(this);
        }
        delete this;
    }
}
