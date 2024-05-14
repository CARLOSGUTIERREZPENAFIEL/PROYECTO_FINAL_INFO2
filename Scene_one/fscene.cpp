#include "fscene.h"
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsView>
#include <QMainWindow>
#include <QLCDNumber>
#include "mainwindow.h"
#include "gscene.h"

FScene::FScene(MainWindow *parent)
    : QGraphicsScene(117.0, 0.0, 1918, 1078, parent),
    vel_y(0),
    vel_x(0),
    contador_posicion_y(0),
    mainWindow(parent)
{
    // Set the background image
    setBackgroundBrush(QBrush(QPixmap(":/fondo_car.jpg")));

    aceleracion = new QTimer(this);
    connect(aceleracion, &QTimer::timeout, this, &FScene::acelerar);
    aceleracion->start(20);

    car = new Car("D:/Info 2/Proyecto_Final/carro_jfk.png");
    addItem(car);
    car->setPos(1138, 800); // límite a la izquierda es 619 en x y a la derecha 1370 en x, inicial x 1138
}

void FScene::keyPressEvent(QKeyEvent *e) {
    keysPressed.insert(e->key());
    QPointF currentCarPos = car->pos();

    if ((keysPressed.contains(Qt::Key_W) && keysPressed.contains(Qt::Key_A)) || (keysPressed.contains(Qt::Key_A) && vel_y > 0)) {
        vel_x -= (vel_y / 4);
        car->turnLeft();
        if (contador_posicion_y == 0) {
            car->setPos(currentCarPos.x(), currentCarPos.y() + 30);
            contador_posicion_y = 1;
        }
    }
    if ((keysPressed.contains(Qt::Key_W) && keysPressed.contains(Qt::Key_D)) || (keysPressed.contains(Qt::Key_D) && vel_y > 0)) {
        vel_x += (vel_y / 4);
        car->turnRight();
        if (contador_posicion_y == 0) {
            car->setPos(currentCarPos.x(), currentCarPos.y() + 30);
            contador_posicion_y = 1;
        }
    }
    if (keysPressed.contains(Qt::Key_W)) {
        if (vel_y < 90) {
            vel_y++;
        }
    } else if (keysPressed.contains(Qt::Key_Space)) {
        if (vel_y > 0) {
            vel_y -= 9;
        }
        if (vel_y < 0) {
            vel_y = 0;
        }
    }
}

void FScene::keyReleaseEvent(QKeyEvent *e) {
    QPointF currentCarPos = car->pos();
    keysPressed.remove(e->key());
    if (contador_posicion_y == 1) {
        car->setPos(currentCarPos.x(), currentCarPos.y() - 30);
    }
    car->resetPixmap();
    contador_posicion_y = 0;
    vel_x = 0;
}

void FScene::acelerar() {
    QPointF currentCarPos = car->pos();
    QPointF currentPos = sceneRect().topLeft();
    if (!keysPressed.contains(Qt::Key_W)) {
        if (vel_y > 0) {
            vel_y--;
        }
    }
    currentPos.setY(currentPos.y() - vel_y);
    setSceneRect(QRectF(currentPos, sceneRect().size()));

    // Controlar los límites del movimiento en el eje x
    if (car->pos().x() < 690 && vel_x < 0) {
        vel_x = 0;
    } else if (car->pos().x() > 1370 && vel_x > 0) {
        vel_x = 0;
    }

    // Actualizar la posición del coche
    car->setPos(currentCarPos.x() + vel_x, currentCarPos.y() - vel_y);

    // Actualizar el velocímetro
    if (mainWindow) {
        QLCDNumber *velocimetro = mainWindow->findChild<QLCDNumber*>("velocimetro");
        if (velocimetro) {
            velocimetro->display(vel_y);
        }
    }
    if (mainWindow)
    {
        QLCDNumber *velocimetro = mainWindow->findChild<QLCDNumber *>("velocimetro");
        if (velocimetro)
        {
            velocimetro->display(vel_y);
        }
    }

    // Acceder a la escena GScene y actualizar el indicador basado en la velocidad
    if (mainWindow)
    {
        GScene *gaugeScene = mainWindow->getGScene();
        if (gaugeScene)
        {
            GIndicator *indicator = gaugeScene->getGIndicator();
            if (indicator)
            {
                indicator->updatePositionBasedOnSpeed(vel_y);
            }
        }
    }



}
