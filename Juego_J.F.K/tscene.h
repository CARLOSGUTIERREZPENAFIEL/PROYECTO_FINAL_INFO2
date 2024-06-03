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

private:
    Personaje *personaje1;

    int backgroundOffsetX;
    QTimer *timer;
    QGraphicsPixmapItem *caja;
    int pos = 1400;
    void initializeScene();
    QList<QGraphicsPixmapItem*>obstaculos;
    QTimer *obs_timer;
    QTimer *coli;


};

#endif // TSCENE_H
