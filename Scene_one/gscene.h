#ifndef GSCENE_H
#define GSCENE_H

#include "gindicator.h"
#include <QGraphicsScene>

class GScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GScene(QObject *parent = nullptr);

    static double sceneWidth()
    {
        return sWidth;
    }
    static double sceneHeight()
    {
        return sHeight;
    }

    GIndicator *getGIndicator() const { return mIndicator; }
    static GScene *getGaugeScene() { return gaugeScene; }

private:
    QGraphicsPixmapItem *mGauge;
    GIndicator *mIndicator;

    static double sWidth;
    static double sHeight;
    static GScene *gaugeScene;
};

#endif // GSCENE_H
