#include "twoscene.h"
#include "mainwindow.h"
#include <QMainWindow>


twoscene::twoscene(MainWindow *parent) : QGraphicsScene(0,0,1920,1080,parent), mainWindow(parent)

{
    setBackgroundBrush(QBrush(QPixmap(":/imagenes/fondo_car.jpg")));

}
