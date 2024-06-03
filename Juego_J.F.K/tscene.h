#ifndef TSCENE_H
#define TSCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include "personaje.h"
#include <QList>


class TScene : public QGraphicsScene
{
    Q_OBJECT

public:
    TScene(QObject *parent = nullptr);




private slots:
    void onMoveBackground(int dx);
    void crear_obs();
    void actualizar_obstaculos();
    void verificar_colision();
    void runPolice();
    void disparo();
    //void moveBullet();

private:
    Personaje *personaje1;
    QTimer *Police;
    int backgroundOffsetX;
    QTimer *timer;
    QGraphicsPixmapItem *caja;
    int pos = 1400;
    void initializeScene();
    QList<QGraphicsPixmapItem*>obstaculos;
    QTimer *obs_timer;
    QTimer *coli;
    QTimer *fire;
    QTimer *bulletTimer;
    QGraphicsPixmapItem *policia;
    QGraphicsPixmapItem *proyectil;
    int pos_bala = 0;
    int cont2=0;
    bool bala = false;
    int Distancia_bala = 0;
    int Distancia_tanque=0;


    int velx = 20;
    float g = 9.81;
    double t = 0.0;
    int angulo = 0;




};

#endif // TSCENE_H
