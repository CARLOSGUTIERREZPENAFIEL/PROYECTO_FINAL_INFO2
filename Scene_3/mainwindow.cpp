#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene_3 = new QGraphicsScene();
    ui -> graphicsView-> setScene(scene_3);

    QImage imagen_fondo("C:/Users/JuanM/OneDrive/Desktop/PROYECTO_FINAL_INFO2/Scene_3/escenario.png");
    QBrush fondo_escenario(imagen_fondo);
    ui -> graphicsView -> setBackgroundBrush(fondo_escenario);
    scene_3->setSceneRect(0,30,1920,1080);
    ui-> graphicsView->scale(0.95,0.95);


    QPixmap pixMap ("C:/Users/JuanM/OneDrive/Desktop/PROYECTO_FINAL_INFO2/Scene_3/jugador1.png");
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
    timer2 -> start(200);
    connect(timer2,SIGNAL(timeout()),this,SLOT(jump_player()));

}
void MainWindow :: run_player(){
    cont += 1;
    if(cont > 8){
        cont = 1;
    }
}
void MainWindow :: jump_player(){
    contY += 1;
    if(contY>3){
        contY= 1;
    }
}


void MainWindow:: keyPressEvent(QKeyEvent *e){
    keysPressed.insert(e->key());
    QPointF currentPos = scene_3 -> sceneRect().topLeft();
    QPointF subjectPos = personaje1 -> pos();
    QPixmap jump1("C:/Users/JuanM/OneDrive/Desktop/PROYECTO_FINAL_INFO2/Scene_3/salto1.png");
    QPixmap jump2("C:/Users/JuanM/OneDrive/Desktop/PROYECTO_FINAL_INFO2/Scene_3/salto2.png");
    QPixmap jump3("C:/Users/JuanM/OneDrive/Desktop/PROYECTO_FINAL_INFO2/Scene_3/salto3.png");
    QPixmap play_run1("C:/Users/JuanM/OneDrive/Desktop/PROYECTO_FINAL_INFO2/Scene_3/jugador2.png");
    QPixmap play_run2("C:/Users/JuanM/OneDrive/Desktop/PROYECTO_FINAL_INFO2/Scene_3/jugador3.png");
    QPixmap play_run3("C:/Users/JuanM/OneDrive/Desktop/PROYECTO_FINAL_INFO2/Scene_3/jugador4.png");
    QPixmap play_run4("C:/Users/JuanM/OneDrive/Desktop/PROYECTO_FINAL_INFO2/Scene_3/jugador5.png");
    QPixmap play_run5("C:/Users/JuanM/OneDrive/Desktop/PROYECTO_FINAL_INFO2/Scene_3/jugador6.png");
    QPixmap play_run6("C:/Users/JuanM/OneDrive/Desktop/PROYECTO_FINAL_INFO2/Scene_3/jugador7.png");
    QPixmap play_run7("C:/Users/JuanM/OneDrive/Desktop/PROYECTO_FINAL_INFO2/Scene_3/jugador8.png");
    QPixmap play_run8("C:/Users/JuanM/OneDrive/Desktop/PROYECTO_FINAL_INFO2/Scene_3/jugador9.png");

        if(keysPressed.contains(Qt::Key_D)){

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

        else if(keysPressed.contains(Qt::Key_W)){

            if(contY == 1){
                personaje1 -> setPixmap(jump1);
                personaje1 -> setPos(personaje1 -> pos().x(), personaje1-> pos().y()-1);
            }
            else if(contY == 2){
                personaje1 -> setPixmap(jump2);
                personaje1 -> setPos(personaje1 -> pos().x(), personaje1-> pos().y()-1);
            }
            else if(contY == 3){
                personaje1 -> setPixmap(jump3);
                personaje1 -> setPos(personaje1 -> pos().x(), personaje1-> pos().y()-1);
            }

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
    QPixmap pixMap("C:/Users/JuanM/OneDrive/Desktop/PROYECTO_FINAL_INFO2/Scene_3/jugador1.png" );
    personaje1 -> setPixmap(pixMap);



}

MainWindow::~MainWindow()
{
    delete ui;
}
