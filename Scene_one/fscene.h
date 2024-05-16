#ifndef FSCENE_H
#define FSCENE_H

#include <QKeyEvent>
#include <QGraphicsScene>
#include <QTimer>
#include <QSet>
#include "car.h"

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
private:
    QGraphicsPixmapItem *mCarretera;
    Car *car;
    QTimer *aceleracion;

    int vel_y;
    int vel_x;
    int contador_posicion_y;

    QList<car*> obst;
    QSet<int> keysPressed;
    MainWindow *mainWindow;
};

#endif // FSCENE_H
