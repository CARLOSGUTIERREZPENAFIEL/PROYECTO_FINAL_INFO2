#include "tscene.h"
#include <QDebug>

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
    setSceneRect(backgroundOffsetX, 30, 1920, 1080);  // Ajustar la posición del fondo
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
        //posX += 800;
        }
    }
}
void TScene:: actualizar_obstaculos(){
    for(int i = 0;i < obstaculos.size(); i++){
        QGraphicsPixmapItem *obstaculo = obstaculos[i];
        if(obstaculo-> pos().x() <backgroundOffsetX-100){
            removeItem(obstaculo);
            obstaculos.removeAt(i);
            qDebug ()<<"elimina";
        }
    }
}
void TScene:: verificar_colision(){
    bool colision_detectada = false;
    for(int i = 0; i< obstaculos.size(); i++){
        if(personaje1 -> collidesWithItem(obstaculos[i])){
            colision_detectada = true;
            qDebug()<<"colision";
            break;
        }

    }
    if(colision_detectada == true){
        personaje1-> colision = true;
    }
    else{
        personaje1-> colision = false;
    }
}
