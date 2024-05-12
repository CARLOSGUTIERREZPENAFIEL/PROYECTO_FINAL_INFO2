#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene_uno = new QGraphicsScene();
    ui->graphicsView->setScene(scene_uno);

    QImage carretera("D:/Info 2/Proyecto_Final/fondo_car_dia.jpeg");
    QBrush fondo_scene_uno(carretera);
    ui->graphicsView->setBackgroundBrush(fondo_scene_uno);
    scene_uno->setSceneRect(1920,1080,-1670,100);
    ui->graphicsView->scale(1,1);

    aceleracion = new QTimer(this);
    aceleracion -> start(20);
    connect(aceleracion, SIGNAL(timeout()), this, SLOT(acelerar()));

    QPixmap pixMap("D:/Info 2/Proyecto_Final/carro_jfk.png");
    car = new QGraphicsPixmapItem();
    scene_uno -> addItem(car);
    car -> setPixmap(pixMap);
    car -> setScale(0.25);
    car -> setPos(1138,1330); //limite a la izquierda es 619 en x y a la derecha 1370 en x inicial x 1138
    vel_y = 0;
    vel_x = 0;
    contador_posicion_y=0;


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::acelerar(){
    QPointF currentCarPos = car->pos();
    QPointF currentPos = scene_uno->sceneRect().topLeft();
    if (!keysPressed.contains(Qt::Key_W)) {
        if (vel_y > 0) {
            vel_y--;
        }
    }
    currentPos.setY(currentPos.y() - vel_y);
    scene_uno->setSceneRect(QRectF(currentPos, scene_uno->sceneRect().size()));
    if(car -> pos().x()<619 && vel_x<0){
        vel_x=0;
    }
    else if(car -> pos().x() > 1370 && vel_x>0){
        vel_x=0;
    }
    car->setPos(currentCarPos.x() + vel_x, currentCarPos.y() - vel_y);


}

void MainWindow::keyPressEvent(QKeyEvent *e){
    QPixmap car_der("D:/Info 2/Proyecto_Final/carro_jfk_der.png");
    QPixmap car_izq("D:/Info 2/Proyecto_Final/carro_jfk_izq.png");
    keysPressed.insert(e->key());
    QPointF currentCarPos = car->pos();
    if ((keysPressed.contains(Qt::Key_W) && keysPressed.contains(Qt::Key_A)) || ( keysPressed.contains(Qt::Key_A) && vel_y>0)) {
        vel_x-=4;
        car -> setPixmap(car_izq);
        if(contador_posicion_y==0){
            car->setPos(currentCarPos.x(), currentCarPos.y()+30);
            contador_posicion_y=1;
        }
    }
    if ((keysPressed.contains(Qt::Key_W) && keysPressed.contains(Qt::Key_D)) || (keysPressed.contains(Qt::Key_D) && vel_y>0 )) {
        vel_x+=4;
        car -> setPixmap(car_der);
        if(contador_posicion_y==0){
            car->setPos(currentCarPos.x(), currentCarPos.y()+30);
            contador_posicion_y=1;
        }


    }
    if(keysPressed.contains(Qt::Key_W)){
        if(vel_y<50){
            vel_y++;
        }
    }


}
void MainWindow::keyReleaseEvent(QKeyEvent *e){
    QPixmap pixMap("D:/Info 2/Proyecto_Final/carro_jfk.png");
    QPointF currentCarPos = car->pos();
    keysPressed.remove(e->key());
    if(contador_posicion_y==1){
        car->setPos(currentCarPos.x(), currentCarPos.y()-30);
    }
    car -> setPixmap(pixMap);
    contador_posicion_y=0;
    vel_x = 0;

}



