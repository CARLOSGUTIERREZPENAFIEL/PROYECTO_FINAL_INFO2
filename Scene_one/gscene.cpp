#include "gscene.h"
#include "gindicator.h"
#include <QPainter>

#define XSIZE 248
#define YSIZE 248

double GScene::sWidth = XSIZE;
double GScene::sHeight = YSIZE;
GScene *GScene::gaugeScene = nullptr;

GScene::GScene(QObject *parent)
    : QGraphicsScene(0.0, 0.0, XSIZE, YSIZE, parent)
{
    mGauge = addPixmap(QPixmap(":/velocimetro.png"));
    mIndicator = new GIndicator;
    addItem(mIndicator);

    // Asignar la instancia de la escena a la variable estática
    gaugeScene = this;
}
