#include "tscene.h"
#include <QDebug>
#include <cmath>

TScene::TScene(QObject *parent) : QGraphicsScene(parent), backgroundOffsetX(0)
{
    initializeScene();
    QImage imagen_fondo(":/imagenes/escenario.png");
    QBrush fondo_escenario(imagen_fondo);
    setBackgroundBrush(fondo_escenario);

    connect(personaje1, &Personaje::moveBackground, this, &TScene::onMoveBackground);
    timer = new QTimer(this);
    connect(timer,&QTimer:: timeout,this,&TScene:: crear_obs);
    timer-> start(1000);

    obs_timer = new QTimer(this);
    connect(obs_timer,&QTimer::timeout,this,&TScene:: actualizar_obstaculos);
    obs_timer -> start(50);

    coli = new QTimer(this);
    connect(coli,&QTimer:: timeout,this,&TScene::verificar_colision);
    coli-> start(10);



    Police = new QTimer(this);
    connect(Police,&QTimer:: timeout, this,&TScene:: runPolice);
    qDebug()<<"inicio   "<<personaje1-> posX;
    QPixmap pol1(":/imagenes/tanque.png");
    policia = new QGraphicsPixmapItem();
    addItem(policia);
    policia-> setPixmap(pol1);
    policia-> setScale(0.7);
    policia-> setPos(-300,860);
    Police-> start(60);

    fire = new QTimer(this);
    connect(fire,&QTimer:: timeout,this,&TScene::disparo);
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
        if (proyectil-> pos().y()>1000) {
            qDebug()<<"iliminar bala";
            removeItem(proyectil);
            delete proyectil;
            proyectil = nullptr;
            bala = false;
        }
    }





}



void TScene:: runPolice()
{
    if(personaje1->posX >850){

        if(Distancia_tanque<500){
            policia->setPos(policia->pos().x() + 50,policia-> pos().y());
            Distancia_tanque += 50;
        }
        else{
            policia->setPos(policia->pos().x() + 20,policia-> pos().y());
        }


    }
}

void TScene::initializeScene()
{

    setSceneRect(0, 30, 1920, 1080);
    //QPixmap PM(":/imagenes/caja");
    personaje1 = new Personaje();
    addItem(personaje1);
    personaje1->setFocus();


}

void TScene::onMoveBackground(int dx)
{
    backgroundOffsetX += dx;
    setSceneRect(backgroundOffsetX, 30, 1920, 1080);
}
void TScene:: crear_obs()
{
    if(personaje1->posX >850){
        if(personaje1-> game == true){
        QPixmap cj(":/imagenes/caja.png");
        caja= new QGraphicsPixmapItem();
        addItem(caja);
        caja-> setPixmap(cj);
        caja-> setScale(0.2);
        caja-> setPos(personaje1->posX + 800,930);
        obstaculos.append(caja);
        }
    }
}
void TScene:: actualizar_obstaculos(){
    for(int i = 0;i < obstaculos.size(); i++){
        QGraphicsPixmapItem *obstaculo = obstaculos[i];
        if(obstaculo-> pos().x() <backgroundOffsetX-100){
            removeItem(obstaculo);
            obstaculos.removeAt(i);

        }
    }
}
void TScene:: verificar_colision(){
    bool colision_detectada = false;
    for(int i = 0; i< obstaculos.size(); i++){
        if(personaje1 -> collidesWithItem(obstaculos[i])){
            colision_detectada = true;

            break;
        }

        for(int i = 0; i<obstaculos.size();i++){
            if(policia-> collidesWithItem(obstaculos[i])){
                removeItem(obstaculos[i]);
                obstaculos.removeAt(i);
            }
        }
    }
    if(colision_detectada == true){
        personaje1-> colision = true;
    }
    else{
        personaje1-> colision = false;
    }
}
