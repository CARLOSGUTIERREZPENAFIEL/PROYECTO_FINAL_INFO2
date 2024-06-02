#include "fscene.h"
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsView>
#include <QMainWindow>
#include <QLCDNumber>
#include "mainwindow.h"
#include "gscene.h"

FScene::FScene(MainWindow *parent)
    : QGraphicsScene(117, 0, 1920, 1080, parent),
    vel_y(0),
    vel_x(0),
    contador_posicion_y(0),
    pos_obst(0),
    mainWindow(parent)
{
    setBackgroundBrush(QBrush(QPixmap(":/imagenes/fondo_car.jpg")));

    aceleracion = new QTimer(this);
    connect(aceleracion, &QTimer::timeout, this, &FScene::acelerar);
    aceleracion->start(20);

    car = new Car(":/imagenes/carro_jfk.png");
    addItem(car);
    car->setPos(1138, 800); // límite a la izquierda es 619 en x y a la derecha 1370 en x, inicial x 1138

    obstacleTimer = new QTimer(this); // Timer para generar obstáculos
    connect(obstacleTimer, &QTimer::timeout, this, &FScene::spawnObstacle);
    obstacleTimer->start(2000); // Cada 2 segundos
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
    if (car->pos().x() < 640 && vel_x < 0) {
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

    // Acceder a la escena GScene y actualizar el indicador basado en la velocidad
    if (mainWindow) {
        GScene *gaugeScene = mainWindow->getGScene();
        if (gaugeScene) {
            GSpeedometer *speedometer = gaugeScene->getGSpeedometer();
            if (speedometer) {
                speedometer->updatePositionBasedOnSpeed(vel_y);
            }
        }
    }
    pos_obst = currentPos.y();
}

void FScene::spawnObstacle() {
    Obstacle *obstacle = new Obstacle(":/imagenes/carro_obst.png", pos_obst);
    addItem(obstacle);
    obstacle->startMoving();
}
