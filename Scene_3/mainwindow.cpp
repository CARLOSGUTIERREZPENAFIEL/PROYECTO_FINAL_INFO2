#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene_3 = new QGraphicsScene();
    ui -> graphicsView-> setScene(scene_3);

    QImage imagen_fondo(":/escenario.png");
    QBrush fondo_escenario(imagen_fondo);
    ui -> graphicsView -> setBackgroundBrush(fondo_escenario);
    scene_3->setSceneRect(0,30,1920,1080);
    ui-> graphicsView->scale(0.95,0.95);

    QPixmap PM(":/caja");
    caja = new QGraphicsPixmapItem();
    scene_3 -> addItem(caja);
    caja -> setPixmap(PM);
    caja -> setScale(0.2);
    caja-> setPos(1400,930);


    QPixmap pixMap (":/jugador1.png");
    personaje1 = new QGraphicsPixmapItem();
    scene_3 -> addItem(personaje1);
    personaje1 -> setPixmap(pixMap);
    personaje1 -> setScale(0.5);
    personaje1 -> setPos (-70,850);
    timer = new QTimer(this);
    timer-> start(80);
    connect(timer,SIGNAL(timeout()),this,SLOT(run_player()));
    posYorigin = personaje1 -> pos().y();

    timer2 = new QTimer(this);
    connect(timer2,SIGNAL(timeout()),this,SLOT(jump_player()));



}
void MainWindow :: run_player(){
    cont += 1;
    if(cont > 8){
        cont = 1;
    }
}

void MainWindow :: jump_player(){
    QPointF currentPos = scene_3 -> sceneRect().topLeft();
    QPointF subjectPos = personaje1 -> pos();
    QPixmap jump1(":/salto1.png");
    QPixmap jump2(":/salto2.png");
    QPixmap jump3(":/salto3.png");
    if(salto = true){
        if(subir){
            personaje1 -> setPixmap(jump1);
            personaje1 -> setPos(personaje1 -> pos().x()+5, personaje1-> pos().y()-5);
            currentPos.setX(currentPos.x()+5);
            scene_3->setSceneRect(QRectF(currentPos, scene_3->sceneRect().size()));
            distancia+= 5;
            //contador_saltos += 1;
            if(distancia == 90){
                subir = false;
            }
        }
        else{

            //for(int i = 1; i<contador_saltos; i++){
                personaje1 -> setPixmap(jump2);
                personaje1 -> setPos(personaje1 -> pos().x()+10, personaje1-> pos().y()+5);
                currentPos.setX(currentPos.x()+10);
                scene_3->setSceneRect(QRectF(currentPos, scene_3->sceneRect().size()));

            //}
            contador_saltos = 0;
                distancia -= 5;
            if (distancia ==0){
                    personaje1->setPixmap(jump3);

                    subir = true;
                    timer2->stop();
                }
        }
    }
}


void MainWindow:: keyPressEvent(QKeyEvent *e){
    keysPressed.insert(e->key());
    QPointF currentPos = scene_3 -> sceneRect().topLeft();
    QPointF subjectPos = personaje1 -> pos();

    QPixmap play_run1(":/jugador2.png");
    QPixmap play_run2(":/jugador3.png");
    QPixmap play_run3(":/jugador4.png");
    QPixmap play_run4(":/jugador5.png");
    QPixmap play_run5(":/jugador6.png");
    QPixmap play_run6(":/jugador7.png");
    QPixmap play_run7(":/jugador8.png");
    QPixmap play_run8(":/jugador9.png");
    if(personaje1-> collidesWithItem(caja)){
        coli = true;
    }
    else{
        coli = false;
    }

        if(keysPressed.contains(Qt::Key_D) && coli == false){

            if(cont == 1){
                personaje1 -> setPixmap(play_run1);
                personaje1 -> setPos(personaje1 -> pos().x(),personaje1-> pos().y() );
                personaje1 -> setPos(personaje1 -> pos().x()+10,personaje1-> pos().y() );
            }
            else if(cont == 2){
                personaje1 -> setPixmap(play_run2);
                personaje1 -> setPos(personaje1 -> pos().x(),personaje1-> pos().y() );
                personaje1 -> setPos(personaje1 -> pos().x()+10,personaje1-> pos().y() );
            }
            else if (cont == 3){
                personaje1 -> setPixmap(play_run3);
                personaje1 -> setPos(personaje1 -> pos().x(),personaje1-> pos().y() );
                personaje1 -> setPos(personaje1 -> pos().x()+10,personaje1-> pos().y() );

            }
            else if(cont == 4){
                personaje1 -> setPixmap(play_run4);
                personaje1 -> setPos(personaje1 -> pos().x(),personaje1-> pos().y() );
                personaje1 -> setPos(personaje1 -> pos().x()+10,personaje1-> pos().y() );
                    }
            else if(cont == 5){
                personaje1 -> setPixmap(play_run5);
                personaje1 -> setPos(personaje1 -> pos().x(),personaje1-> pos().y() );
                personaje1 -> setPos(personaje1 -> pos().x()+10,personaje1-> pos().y() );
            }
            else if(cont == 6){
                personaje1 -> setPixmap(play_run6);
                personaje1 -> setPos(personaje1 -> pos().x(),personaje1-> pos().y() );
                personaje1 -> setPos(personaje1 -> pos().x()+10,personaje1-> pos().y() );
            }
            else if(cont == 7){
                personaje1 -> setPixmap(play_run7);
                personaje1 -> setPos(personaje1 -> pos().x(),personaje1-> pos().y() );
                personaje1 -> setPos(personaje1 -> pos().x()+10,personaje1-> pos().y() );
            }
            else if(cont == 8){
                personaje1 -> setPixmap(play_run8);
                personaje1 -> setPos(personaje1 -> pos().x(),personaje1-> pos().y() );
                personaje1 -> setPos(personaje1 -> pos().x()+10,personaje1-> pos().y() );
            }
            if(subjectPos.x()>850){
                currentPos.setX(currentPos.x()+10);
                scene_3->setSceneRect(QRectF(currentPos, scene_3->sceneRect().size()));
            }


    }
        if(keysPressed.contains(Qt::Key_W)){
        salto = true;
            timer2-> start(18);
    }
        if(keysPressed.contains(Qt::Key_W) && keysPressed.contains(Qt::Key_D)){
            salto = true;
            timer2-> start(18);


    }



        else if (keysPressed.contains(Qt::Key_A)){
            personaje1 -> setPixmap(play_run1);
            personaje1 -> setPos(personaje1 -> pos().x()-1,personaje1-> pos().y() );
            personaje1 -> setPixmap(play_run2);
            personaje1 -> setPos(personaje1 -> pos().x()-1,personaje1-> pos().y() );
            personaje1 -> setPixmap(play_run3);
            personaje1 -> setPos(personaje1 -> pos().x()-1,personaje1-> pos().y() );
            personaje1 -> setPixmap(play_run4);
            personaje1 -> setPos(personaje1 -> pos().x()-1,personaje1-> pos().y() );
            personaje1 -> setPixmap(play_run5);
            personaje1 -> setPos(personaje1 -> pos().x()-1,personaje1-> pos().y() );
            personaje1 -> setPixmap(play_run6);
            personaje1 -> setPos(personaje1 -> pos().x()-1,personaje1-> pos().y() );
            personaje1 -> setPixmap(play_run7);
            personaje1 -> setPos(personaje1 -> pos().x()-1,personaje1-> pos().y() );
            personaje1 -> setPixmap(play_run8);
            personaje1 -> setPos(personaje1 -> pos().x()-1,personaje1-> pos().y() );

        }

}

void MainWindow:: keyReleaseEvent(QKeyEvent *e){
    keysPressed.remove(e-> key());
    if(salto = false){
    QPixmap pixMap("C:/Users/JuanM/OneDrive/Desktop/PROYECTO_FINAL_INFO2/Scene_3/jugador1.png" );
    personaje1 -> setPixmap(pixMap);
    }


}



MainWindow::~MainWindow()
{
    delete ui;
}
