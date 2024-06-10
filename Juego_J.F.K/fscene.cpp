#include "fscene.h"
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsView>
#include <QMainWindow>
#include <QLCDNumber>
#include "mainwindow.h"
#include "gscene.h"
#include <QDebug>

FScene::FScene(MainWindow *parent)
    : QGraphicsScene(117, 0, 1920, 1080, parent),
    vel_y(0),
    vel_x(0),
    contador_posicion_y(0),
    pos_obst(0),
    mainWindow(parent)
{
    setBackgroundBrush(QBrush(QPixmap(":/imagenes/fondo_car.jpg")));
    QPixmap av(":/imagenes/avion.png");
    Avion = new QGraphicsPixmapItem();
    addItem(Avion);
    Avion->setPixmap(av);
    Avion->setScale(1);
    Avion->setPos(1050, -80000);



    aceleracion = new QTimer(this);
    connect(aceleracion, &QTimer::timeout, this, &FScene::acelerar);

    startG = new QTimer(this);
    connect(startG, &QTimer::timeout, this, &FScene::startgame);
    startG->start(20);

    car = new Car(":/imagenes/carro_jfk.png");
    addItem(car);
    car->setPos(1138, 1100); // límite a la izquierda es 619 en x y a la derecha 1370 en x, inicial x 1138

    obstacleTimer = new QTimer(this);
    connect(obstacleTimer, &QTimer::timeout, this, &FScene::spawnObstacle);

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
        progressBar->hide();
        progressLabel->hide();
        PMenu* menu = new PMenu("Pausa", 1, true);
        connect(menu, &PMenu::retry, mainWindow, &MainWindow::onLevelSelected);
        connect(menu, &PMenu::goToMenu, mainWindow, &MainWindow::showInitialScene);
        connect(menu, &PMenu::resume, this, [this]() {
            jugar = true;
            aceleracion->start();
            obstacleTimer->start();
            progressBar->show();
            progressLabel->show();
        });
        menu->setParent(mainWindow);
        menu->move(672, 100);
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
    progreso = -(currentCarPos.y()-800) * 100 / 79028;
    progressBar->setValue(progreso);
    progressLabel->setText(QString::number(progreso) + "%");
    if (!keysPressed.contains(Qt::Key_W)) {
        if (vel_y > 0) {
            vel_y--;

        } else if (vel_y<0) {
            vel_y++;
        }

    }
    else if (jugar == false) {
        if (vel_y > 0) {
            vel_y--;
        } else if (vel_y<0) {
            vel_y++;
        }
    }
    if(win==true){
        vel_y=10;
        if(car->collidesWithItem(Avion)){
            PMenu* menu = new PMenu("GANASTE", 1);
            connect(menu, &PMenu::retry, mainWindow, &MainWindow::onLevelSelected);
            connect(menu, &PMenu::goToMenu, mainWindow, &MainWindow::showInitialScene);
            menu->setParent(mainWindow);
            menu->move(672, 100);
            menu->show();
            aceleracion->stop();

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
    if(!humoCreado && win==false){
        foreach (QGraphicsItem *item, items()) {
            if (item->type() == QGraphicsPixmapItem::Type && item != car) {
                if (car->collidesWithItem(item)) {
                    vel_x = 0;
                    jugar = false;
                    if((item->pos().x()>=1150) && (item->pos().x()<=1370)){ //1150 a 1370
                        // Si hay colisión, ajusta las velocidades
                        vel_y = (vel_y + 50) / 2;
                        vel_obst = (vel_y + 50) / 2;
                        obstacleTimer->stop(); // ya no se crean más obstáculos

                        // Actualizar la velocidad del obstáculo colisionado
                        carro_choque = dynamic_cast<Obstacle*>(item);
                        if (carro_choque) {
                            carro_choque->updateVelocity(vel_obst);
                        }
                    }
                    else{
                        if(vel_y>50){
                            divisor = ((vel_y-50)/5);
                        }
                        new_vel_choque=(-vel_y)/divisor;
                        carro_choque = dynamic_cast<Obstacle*>(item);
                        if (carro_choque) {
                            carro_choque->updateVelocity(new_vel_choque);
                        }
                        vel_y = (-50)/2;
                        choque = new QTimer(this);
                        connect(obstacleTimer, &QTimer::timeout, this, &FScene::vel_choque);
                        choque->start(20);
                        obstacleTimer->stop();


                    }

                    collisionImage = new QGraphicsPixmapItem(QPixmap(":/imagenes/humo.png"));
                    addItem(collisionImage);
                    humoCreado = true;             
                    break;
                }
            }
        }
    }

    if (humoCreado) {
        collisionImage->setPos(currentCarPos.x() + 80, currentCarPos.y() - 34);
        if (vel_y == 0) {
            progressBar->hide();
            progressLabel->hide();
            PMenu* menu = new PMenu("Perdiste", 1);
            connect(menu, &PMenu::retry, mainWindow, &MainWindow::onLevelSelected);
            connect(menu, &PMenu::goToMenu, mainWindow, &MainWindow::showInitialScene);
            menu->setParent(mainWindow);
            menu->move(672, 100);
            menu->show();
            aceleracion->stop();
            obstacleTimer->stop();
        }
    }
    if(jugar == true){
        distanciaY += vel_y;
        if(distanciaY>=79028){
            progressBar->hide();
            progressLabel->hide();
            jugar = false;
            win = true;
            qDebug() << currentCarPos;
            vel_y=15;
            obstacleTimer->stop();
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

void FScene::startgame(){
    QPointF currentCarPos = car->pos();
    car->setPos(currentCarPos.x(), currentCarPos.y() - 20);
    if(currentCarPos.y()<=800){
        progressBar = new QProgressBar();
        progressBar->setRange(0, 100);
        progressBar->setValue(0);
        progressBar->setGeometry(QRect(860, 10, 200, 30));
        progressBar->setParent(mainWindow);
        progressBar->setStyleSheet("QProgressBar {"
                                   "border: 2px solid grey; "
                                   "border-radius: 10px; "
                                   "background-color: #E0E0E0; "
                                   "}"
                                   "QProgressBar::chunk {"
                                   "background-color: blue; "
                                   "border-radius: 8px; "
                                   "}");

        progressBar->setFormat("");
        progressBar->show();

        progressLabel = new QLabel("0%");
        progressLabel->setParent(mainWindow);
        progressLabel->setGeometry(progressBar->geometry().x() + progressBar->width() + 10,
                                   progressBar->geometry().y(),
                                   50, 30);
        progressLabel->show();
        jugar=true;
        aceleracion->start(15);
        obstacleTimer->start(cant_obst); // con una regla de 3 cambio la velocidad de la aparicion de obstaculos para que se vea mas fluido
        startG->stop();
    }


}

void FScene::vel_choque(){
    new_vel_choque--;
    carro_choque->updateVelocity(new_vel_choque);
    if(new_vel_choque>=0){
        carro_choque->updateVelocity(new_vel_choque);
        choque->stop();
    }

}


//            collisionImage->setPos(currentCarPos.x() + 80, currentCarPos.y() - 34);

