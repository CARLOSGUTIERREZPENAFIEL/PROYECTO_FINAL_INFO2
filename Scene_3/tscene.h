#ifndef TSCENE_H
#define TSCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include "personaje.h"

class TScene : public QGraphicsScene
{
    Q_OBJECT

public:
    TScene(QObject *parent = nullptr);

private:
    Personaje *personaje1;
    QGraphicsPixmapItem *caja;

    void initializeScene();
};

#endif // TSCENE_H
