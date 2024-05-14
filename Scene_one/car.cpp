#include "car.h"

Car::Car(const QString &filePath, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent),
    carPixmap(filePath),
    carPixmapLeft("D:/Info 2/Proyecto_Final/carro_jfk_izq.png"),
    carPixmapRight("D:/Info 2/Proyecto_Final/carro_jfk_der.png")
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
