#include "personaje.h"
#include <QDebug>

Personaje::Personaje(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    initializePlayer();
    posYorigin = pos().y();

    timer = new QTimer(this);
    timer->start(80);
    connect(timer, &QTimer::timeout, this, &Personaje::runPlayer);

    timer2 = new QTimer(this);
    connect(timer2, &QTimer::timeout, this, &Personaje::jumpPlayer);
}

void Personaje::initializePlayer()
{
    QPixmap pixMap(":/imagenes/jugador1.png");
    setPixmap(pixMap);
    setScale(0.5);
    setPos(-70, 850);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
}

void Personaje::runPlayer()
{
    cont += 1;
    if (cont > 8) {
        cont = 1;
    }
}

void Personaje::jumpPlayer()
{
    QPixmap jump1(":/imagenes/salto1.png");
    QPixmap jump2(":/imagenes/salto2.png");
    QPixmap jump3(":/imagenes/salto3.png");
    QPixmap base(":/imagenes/jugador1.png");

    if (collidesWithItem(parentItem()) && pos().y() < 850) {
        setPixmap(base);
        setPos(lugar_saltoX, lugar_saltoY);
        timer2->stop();
        return;
    }

    if (subir) {
        setPixmap(jump1);
        if (pos().y() <= 850) {
            setPos(pos().x() + 5, pos().y() - 5);
            distancia += 5;
            if (distancia == 90) {
                subir = false;
            }
        }
    } else if (pos().y() <= 850) {
        setPixmap(jump2);
        setPos(pos().x() + 10, pos().y() + 5);
        distancia -= 5;
        if (distancia == 0) {
            setPixmap(jump3);
            subir = true;
            salto = false;
            timer2->stop();
        }
    }
}

void Personaje::keyPressEvent(QKeyEvent *event)
{
    keysPressed.insert(event->key());
    QPixmap play_run1(":/imagenes/jugador2.png");
    QPixmap play_run2(":/imagenes/jugador3.png");
    QPixmap play_run3(":/imagenes/jugador4.png");
    QPixmap play_run4(":/imagenes/jugador5.png");
    QPixmap play_run5(":/imagenes/jugador6.png");
    QPixmap play_run6(":/imagenes/jugador7.png");
    QPixmap play_run7(":/imagenes/jugador8.png");
    QPixmap play_run8(":/imagenes/jugador9.png");

    if (keysPressed.contains(Qt::Key_D)) {
        QPixmap pixmaps[8] = {play_run1, play_run2, play_run3, play_run4, play_run5, play_run6, play_run7, play_run8};
        setPixmap(pixmaps[cont - 1]);
        setPos(pos().x() + 10, pos().y());
    }

    if (keysPressed.contains(Qt::Key_W)) {
        lugar_saltoX = pos().x();
        lugar_saltoY = pos().y();
        timer2->start(18);
    }

    if (keysPressed.contains(Qt::Key_W) && keysPressed.contains(Qt::Key_D)) {
        salto = true;
        timer2->start(18);
    }

    if (keysPressed.contains(Qt::Key_A)) {
        setPixmap(play_run1);
        setPos(pos().x() - 1, pos().y());
        setPixmap(play_run2);
        setPos(pos().x() - 1, pos().y());
        setPixmap(play_run3);
        setPos(pos().x() - 1, pos().y());
        setPixmap(play_run4);
        setPos(pos().x() - 1, pos().y());
        setPixmap(play_run5);
        setPos(pos().x() - 1, pos().y());
        setPixmap(play_run6);
        setPos(pos().x() - 1, pos().y());
        setPixmap(play_run7);
        setPos(pos().x() - 1, pos().y());
        setPixmap(play_run8);
        setPos(pos().x() - 1, pos().y());
    }
}

void Personaje::keyReleaseEvent(QKeyEvent *event)
{
    keysPressed.remove(event->key());
    if (!salto) {
        QPixmap pixMap(":/imagenes/jugador1.png");
        setPixmap(pixMap);
    }
}
