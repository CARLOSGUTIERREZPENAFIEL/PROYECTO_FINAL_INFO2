#include "tscene.h"

TScene::TScene(QObject *parent) : QGraphicsScene(parent)
{
    initializeScene();
    QImage imagen_fondo(":/imagenes/escenario.png");
    QBrush fondo_escenario(imagen_fondo);
    setBackgroundBrush(fondo_escenario);
}

void TScene::initializeScene()
{
    setSceneRect(0, 30, 1920, 1080);
    QPixmap PM(":/imagenes/caja");
    personaje1 = new Personaje();
    addItem(personaje1);
    personaje1->setFocus();
}
