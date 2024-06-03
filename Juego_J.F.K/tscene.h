#ifndef TSCENE_H
#define TSCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include "personaje.h"
#include "PMenu.h" // Incluye el archivo de encabezado del menú
#include <QList>

class MainWindow;

class TScene : public QGraphicsScene
{
    Q_OBJECT

public:
    TScene(MainWindow *parent = nullptr);




protected:
    void keyPressEvent(QKeyEvent *event) override; // Sobrescribe keyPressEvent

private slots:
    void onMoveBackground(int dx);
    void crear_obs();
    void actualizar_obstaculos();
    void verificar_colision();
    void runPolice();
    void disparo();
    //void moveBullet();

private:
    void showPauseMenu(); // Declaración de la nueva función

    Personaje *personaje1;
    QTimer *Police;
    QTimer *obs_timer;
    QTimer *coli;
    QTimer *fire;
    QTimer *bulletTimer;
    QTimer *timer;
    qreal tanque_actual;
    QGraphicsPixmapItem *caja;
    QGraphicsPixmapItem *policia;
    QGraphicsPixmapItem *proyectil;
    QList<QGraphicsPixmapItem*>obstaculos;

    int pos = 1400;
    int backgroundOffsetX;
    int pos_bala = 0;
    int cont2=0;
    int Distancia_bala = 0;
    int Distancia_tanque=0;
    int velx = 20;
    int angulo = 0;
    int vida = 30;
    void initializeScene();
    bool animacion_final = false;
    bool bala = false;
    bool jugar = true;
    float g = 9.81;
    double t = 0.0;

    MainWindow *mainWindow;
};

#endif // TSCENE_H
