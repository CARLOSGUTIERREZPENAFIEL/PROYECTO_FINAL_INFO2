#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene_3 = new QGraphicsScene();
    ui -> graphicsView-> setScene(scene_3);

    QImage imagen_fondo("C:/Users/JuanM/OneDrive/Desktop/Carlos/Proyecto info2/PROYECTO_INFO2/escenario.png");
    QBrush fondo_escenario(imagen_fondo);
    ui -> graphicsView -> setBackgroundBrush(fondo_escenario);
    scene_3->setSceneRect(1400,550,-200,30);
    ui-> graphicsView->scale(0.23,0.49);


    QPixmap pixMap ("C:/Users/JuanM/OneDrive/Desktop/Carlos/Proyecto info2/PROYECTO_INFO2/jugador6.png");
    personaje1 = new QGraphicsPixmapItem();
    scene_3 -> addItem(personaje1);
    personaje1 -> setPixmap(pixMap);
    personaje1 -> setScale(2.5);
    personaje1 -> setPos (-70,850);

}

void MainWindow:: keyPressEvent(QKeyEvent *e){
    QPixmap play_run("C:/Users/JuanM/OneDrive/Desktop/Carlos/Proyecto info2/PROYECTO_INFO2/jugador1.png");

        if (e-> key() == Qt:: Key_D){
        personaje1 -> setPixmap(play_run);
            personaje1 -> setPos(personaje1 -> pos().x()+30,personaje1-> pos().y() );



    }

}
void MainWindow:: keyReleaseEvent(QKeyEvent *e){
    QPixmap pixMap("C:/Users/JuanM/OneDrive/Desktop/Carlos/Proyecto info2/PROYECTO_INFO2/jugador6.png" );
    personaje1 -> setPixmap(pixMap);
}

MainWindow::~MainWindow()
{
    delete ui;
}
