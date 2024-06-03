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
    obstacleTimer->start(cant_obst); // Cada 2 segundos
}

void FScene::keyPressEvent(QKeyEvent *e) {
    keysPressed.insert(e->key());
    QPointF currentCarPos = car->pos();
    if(jugar == true){
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
    } else {
        keysPressed.remove(e->key());
    }

    // Manejar la tecla P para pausar
    if (keysPressed.contains(Qt::Key_P)) {
        PMenu* menu = new PMenu("Pausa", 1, true); // Texto "Pausa" y mostrar botón "Reanudar"
        connect(menu, &PMenu::retry, mainWindow, &MainWindow::onLevelSelected);
        connect(menu, &PMenu::goToMenu, mainWindow, &MainWindow::showInitialScene);
        connect(menu, &PMenu::resume, this, [this]() {
            jugar = true;
            aceleracion->start();
            obstacleTimer->start();
        });
        menu->setParent(mainWindow);
        menu->move(600, 100);
        menu->show();
        jugar = false;
        aceleracion->stop();
        obstacleTimer->stop();
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
    } else if (jugar == false) {
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

    // Verificar colisión con obstáculos
    if(!humoCreado){
        foreach (QGraphicsItem *item, items()) {
            if (item->type() == QGraphicsPixmapItem::Type && item != car) {
                if (car->collidesWithItem(item)) {
                    // Si hay colisión, ajusta las velocidades
                    vel_y = (vel_y + 50) / 2;
                    vel_x = 0;
                    vel_obst = (vel_y + 50) / 2;
                    jugar = false;
                    obstacleTimer->stop(); // ya no se crean más obstáculos

                    // Actualizar la velocidad del obstáculo colisionado
                    Obstacle *obstacle = dynamic_cast<Obstacle*>(item);
                    if (obstacle) {
                        obstacle->updateVelocity(vel_obst);
                    }

                    // Crear imagen de humo solo una vez
                    collisionImage = new QGraphicsPixmapItem(QPixmap(":/imagenes/humo.png"));
                    addItem(collisionImage);
                    humoCreado = true;

                    // Salir del bucle de verificación de colisión
                    break;
                }
            }
        }
    }
    // Actualizar la posición del humo si ha sido creado
    if (humoCreado) {
        collisionImage->setPos(currentCarPos.x() + 80, currentCarPos.y() - 34);
        if (vel_y == 0) {
            PMenu* menu = new PMenu("Perdiste", 1); // Cambia el texto y nivel según sea necesario
            connect(menu, &PMenu::retry, mainWindow, &MainWindow::onLevelSelected);
            connect(menu, &PMenu::goToMenu, mainWindow, &MainWindow::showInitialScene);
            menu->setParent(mainWindow); // Asegurar que el menú se muestre en la ventana principal
            menu->move(600, 100); // Posicionar el menú en la ventana principal
            menu->show();
            aceleracion->stop();
        }
    }

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

    cant_obst = (-((vel_y / 90) - 1) * 1500) + 500;
    pos_obst = currentPos.y();
}

void FScene::spawnObstacle() {
    QPointF currentCarPos = car->pos();
    if(jugar == true){
        Obstacle *obstacle = new Obstacle(":/imagenes/carro_obst.png", pos_obst, vel_obst, currentCarPos.y());
        addItem(obstacle);
        obstacle->startMoving();
    }
}




//            collisionImage->setPos(currentCarPos.x() + 80, currentCarPos.y() - 34);

