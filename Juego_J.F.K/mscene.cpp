#include "mscene.h"
#include <QGraphicsProxyWidget>
#include <QGraphicsPixmapItem>
#include <QLabel>

MScene::MScene(QObject *parent) : QGraphicsScene(parent)
{
    QGraphicsPixmapItem *backgroundItem = new QGraphicsPixmapItem(QPixmap(":/imagenes/fondo_niv.png"));
    addItem(backgroundItem);
    backgroundItem->setPos(-960, -540); // La mitad de 1920 y 1080 para centrar

    // Crear botones
    button1 = new QPushButton();
    button2 = new QPushButton();
    button3 = new QPushButton();
    back_menu = new QPushButton();

    // Estilos de los botones
    QString buttonStyle1 = "QPushButton {"
                           "background-image: url(:/imagenes/n1_on);"
                           "background-repeat: no-repeat;"
                           "background-position: center;"
                           "border: 5px solid #FFD700;"
                           "width: 400px;"
                           "height: 400px;"
                           "}";

    QString buttonStyle2 = "QPushButton {"
                           "background-image: url(:/imagenes/n2_on);"
                           "background-repeat: no-repeat;"
                           "background-position: center;"
                           "border: 5px solid #C0C0C0;"
                           "width: 400px;"
                           "height: 400px;"
                           "}";

    QString buttonStyle3 = "QPushButton {"
                           "background-image: url(:/imagenes/n3_on);"
                           "background-repeat: no-repeat;"
                           "background-position: center;"
                           "border: 5px solid #FFD700;"
                           "width: 400px;"
                           "height: 400px;"
                           "}";
    QString buttonStyleB = "QPushButton {"
                           "background-color: transparent;"
                           "background-image: url(:/imagenes/back);"
                           "background-repeat: no-repeat;"
                           "background-position: center;"
                           "border: none;"
                           "width: 70px;"
                           "height: 84px;"
                           "}";


    button1->setStyleSheet(buttonStyle1);
    button2->setStyleSheet(buttonStyle2);
    button3->setStyleSheet(buttonStyle3);
    back_menu->setStyleSheet(buttonStyleB);

    QLabel *label1 = new QLabel("Nivel 1", button1);
    QLabel *label2 = new QLabel("Nivel 2", button2);
    QLabel *label3 = new QLabel("Nivel 3", button3);

    QString labelStyle = "QLabel { color: black; font-size: 24px; }";
    label1->setStyleSheet(labelStyle);
    label2->setStyleSheet(labelStyle);
    label3->setStyleSheet(labelStyle);

    label1->move(290, 10);
    label2->move(290, 10);
    label3->move(290, 10);

    QGraphicsProxyWidget *proxy1 = addWidget(button1);
    QGraphicsProxyWidget *proxy2 = addWidget(button2);
    QGraphicsProxyWidget *proxy3 = addWidget(button3);
    QGraphicsProxyWidget *proxy4 = addWidget(back_menu);

    setSceneRect(-960, -540, 1920, 1080);

    proxy1->setPos(-650, -200);
    proxy2->setPos(-200, -200);
    proxy3->setPos(250, -200);
    proxy4->setPos(-900, -480);

    connect(button1, &QPushButton::clicked, this, &MScene::onButton1Clicked);
    connect(button2, &QPushButton::clicked, this, &MScene::onButton2Clicked);
    connect(button3, &QPushButton::clicked, this, &MScene::onButton3Clicked);
    connect(back_menu, &QPushButton::clicked, this, &MScene::onExitClicked);
}

void MScene::onButton1Clicked()
{
    emit levelSelected(1);
}

void MScene::onButton2Clicked()
{
    if(nivel_total>=2){
        emit levelSelected(2);
    }
}

void MScene::onButton3Clicked()
{
    if(nivel_total>=3){
        emit levelSelected(3);
    }
}
void MScene::onExitClicked()
{

    emit levelSelected(4);

}
