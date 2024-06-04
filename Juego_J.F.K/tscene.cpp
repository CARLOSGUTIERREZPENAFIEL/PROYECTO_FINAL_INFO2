#include "tscene.h"
#include "PMenu.h" // Asegúrate de incluir el archivo de encabezado del menú
#include <QDebug>
#include "pmenu.h"
#include <cmath>
#include <QKeyEvent>
#include "mainwindow.h"



TScene::TScene(MainWindow *parent) :  mainWindow(parent)
{
    initializeScene();
    QImage imagen_fondo(":/imagenes/escenario.png");
    QBrush fondo_escenario(imagen_fondo);
    setBackgroundBrush(fondo_escenario);
    QPixmap f(":/imagenes/disparo.png");
    fin = new QGraphicsPixmapItem();
    addItem(fin);
    fin ->setPixmap(f);
    fin->setScale(1);
    fin->setPos(1850,870);

    connect(personaje1, &Personaje::moveBackground, this, &TScene::onMoveBackground);
    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&TScene::crear_obs);
    timer->start(1000);

    obs_timer = new QTimer(this);
    connect(obs_timer,&QTimer::timeout,this,&TScene::actualizar_obstaculos);
    obs_timer->start(50);

    coli = new QTimer(this);
    connect(coli,&QTimer::timeout,this,&TScene::verificar_colision);
    coli->start(10);

    Police = new QTimer(this);
    connect(Police,&QTimer::timeout, this,&TScene::runPolice);
    qDebug() << "inicio   " << personaje1->posX;
    QPixmap pol1(":/imagenes/tanque.png");
    policia = new QGraphicsPixmapItem();
    addItem(policia);
    policia->setPixmap(pol1);
    policia->setScale(0.7);
    policia->setPos(-300, 860);
    Police->start(60);

    fire = new QTimer(this);
    connect(fire,&QTimer::timeout,this,&TScene::disparo);
    fire->start(25);
}

void TScene::disparo()
{
    if (personaje1->posX > 850 && !bala) {
        QPixmap b(":/imagenes/disparo.png");
        proyectil = new QGraphicsPixmapItem();
        addItem(proyectil);
        proyectil->setPixmap(b);
        proyectil->setScale(3);
        proyectil->setPos(policia->pos().x() + 200, 870);
        bala = true;
        Distancia_bala = 0;
        t = 0.0;
    } else if (bala) {
        t += 0.025;
        double newX = proyectil->pos().x() + velx;
        double newY = proyectil->pos().y() + 0.5 * g * std::pow(t, 2);
        proyectil->setPos(newX, newY);
        Distancia_bala += velx;
        if( personaje1->collidesWithItem(proyectil)){
            removeItem(proyectil);
            delete proyectil;
            proyectil = nullptr;
            bala = false;
            vida--;
            if(vida<=0){
                jugar=false;
                qDebug()<<"antes  "<<personaje1->jugar_nivel;
                personaje1-> jugar_nivel = false;
                qDebug()<<"despues "<<personaje1-> jugar_nivel;


                Police->stop();
                fire->stop();
                obs_timer->stop();
                coli->stop();
                timer->stop();
                PMenu* menu = new PMenu("Perdiste", 3); // Cambia el texto y nivel según sea necesario
                connect(menu, &PMenu::retry, mainWindow, &MainWindow::onLevelSelected);
                connect(menu, &PMenu::goToMenu, mainWindow, &MainWindow::showInitialScene);
                menu->setParent(mainWindow); // Asegurar que el menú se muestre en la ventana principal
                menu->move(600, 100); // Posicionar el menú en la ventana principal
                menu->show();
            }
        }
        else if (proyectil->pos().y() > 1000) {
            qDebug() << "eliminar bala";
            removeItem(proyectil);
            delete proyectil;
            proyectil = nullptr;
            bala = false;
        }
    }
}

void TScene::runPolice()
{
    if (personaje1->posX > 850) {
        if (Distancia_tanque < 500) {
            policia->setPos(policia->pos().x() + 50, policia->pos().y());
            Distancia_tanque += 50;
        } else {
            policia->setPos(policia->pos().x() + 20, policia->pos().y());
        }
    }
    if(personaje1->jugar_nivel == false){
        Police->stop();
        fire ->stop();

    }
    if(jugar==true){
        if( personaje1->collidesWithItem(policia)){
            tanque_actual = policia->pos().x();
            if(proyectil){
                removeItem(proyectil);
                delete proyectil;
            }
            proyectil = nullptr;
            bala = false;
            vida=0;
            jugar=false;
            personaje1->jugar_nivel=false;
            fire->stop();


        }
    }
    if((jugar==false) && (policia->pos().x() > tanque_actual+600) && (animacion_final==false)){
        Police->stop();
        obs_timer->stop();
        coli->stop();
        timer->stop();
        animacion_final=true;
        PMenu* menu = new PMenu("Perdiste", 3); // Cambia el texto y nivel según sea necesario
        connect(menu, &PMenu::retry, mainWindow, &MainWindow::onLevelSelected);
        connect(menu, &PMenu::goToMenu, mainWindow, &MainWindow::showInitialScene);
        menu->setParent(mainWindow); // Asegurar que el menú se muestre en la ventana principal
        menu->move(600, 100); // Posicionar el menú en la ventana principal
        menu->show();
    }
}

void TScene::initializeScene()
{
    setSceneRect(0, 30, 1920, 1080);
    personaje1 = new Personaje();
    addItem(personaje1);
    personaje1->setFocus();
}

void TScene::onMoveBackground(int dx)
{
    backgroundOffsetX += dx;
    setSceneRect(backgroundOffsetX, 30, 1920, 1080);
}

void TScene::crear_obs()
{
    if (personaje1->posX > 850) {
        if (personaje1->game == true) {
            QPixmap cj(":/imagenes/caja.png");
            caja = new QGraphicsPixmapItem();
            addItem(caja);
            caja->setPixmap(cj);
            caja->setScale(0.2);
            caja->setPos(personaje1->posX + 800, 930);
            obstaculos.append(caja);
        }
    }
}

void TScene::actualizar_obstaculos()
{
    for (int i = 0; i < obstaculos.size(); i++) {
        QGraphicsPixmapItem *obstaculo = obstaculos[i];
        if (obstaculo->pos().x() < backgroundOffsetX - 100) {
            removeItem(obstaculo);
            obstaculos.removeAt(i);
        }
    }
}

void TScene::verificar_colision()
{

    if(personaje1-> win == true){
        Police->stop();
        obs_timer->stop();
        coli->stop();
        timer->stop();
        fire->stop();
        PMenu* menu = new PMenu("GANASTE", 3); // Cambia el texto y nivel según sea necesario
        connect(menu, &PMenu::retry, mainWindow, &MainWindow::onLevelSelected);
        connect(menu, &PMenu::goToMenu, mainWindow, &MainWindow::showInitialScene);
        menu->setParent(mainWindow); // Asegurar que el menú se muestre en la ventana principal
        menu->move(600, 100); // Posicionar el menú en la ventana principal
        menu->show();
    }
    bool colision_detectada = false;
    for (int i = 0; i < obstaculos.size(); i++) {
        if (personaje1->collidesWithItem(obstaculos[i])) {
            colision_detectada = true;
            break;
        }

        for (int i = 0; i < obstaculos.size(); i++) {
            if (policia->collidesWithItem(obstaculos[i])) {
                removeItem(obstaculos[i]);
                obstaculos.removeAt(i);
            }
        }
    }
    if (colision_detectada) {
        personaje1->colision = true;
    } else {
        personaje1->colision = false;
    }

}

void TScene::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_P) {
        showPauseMenu();
    } else {
        QGraphicsScene::keyPressEvent(event); // Llama a la implementación base
    }
}

void TScene::showPauseMenu()
{
    PMenu* menu = new PMenu("Pausa", 3, true);
    jugar=false;
    Police->stop();
    fire->stop();
    obs_timer->stop();
    coli->stop();
    timer->stop();
    connect(menu, &PMenu::retry, mainWindow, &MainWindow::onLevelSelected);
    connect(menu, &PMenu::goToMenu, mainWindow, &MainWindow::showInitialScene);
    connect(menu, &PMenu::resume, this, [this]() {
        jugar = true;
        obs_timer->start();
        coli->start();
        timer->start();
        Police->start();
        fire->start();
    });
    menu->show();
}
