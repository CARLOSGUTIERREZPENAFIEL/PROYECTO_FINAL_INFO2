#ifndef FSCENE_H
#define FSCENE_H

#include <QKeyEvent>
#include <QGraphicsScene>
#include <QTimer>
#include <QSet>
#include "car.h"
#include "pmenu.h"

class MainWindow;

class FScene : public QGraphicsScene
{
    Q_OBJECT
public:
    FScene(MainWindow *parent = nullptr);
protected:
    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;
private slots:
    void acelerar();
    void spawnObstacle();
private:
    QGraphicsPixmapItem *mCarretera;
    QGraphicsPixmapItem *collisionImage;
    Car *car;
    QTimer *aceleracion;
    QTimer *obstacleTimer; // Timer para los obstáculos

    int vel_y;
    int vel_x;
    int contador_posicion_y;
    int pos_obst;
    int cant_obst = 2000;
    int vel_obst = 50;

    bool jugar = true;
    bool humoCreado = false; // Humo 1 vez

    QSet<int> keysPressed;
    MainWindow *mainWindow;
};

#endif // FSCENE_H
