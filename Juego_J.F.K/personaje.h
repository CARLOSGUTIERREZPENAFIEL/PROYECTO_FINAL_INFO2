#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QSet>
#include <QPixmap>
#include <QKeyEvent>
#include <QList>

class Personaje : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Personaje(QGraphicsItem *parent = nullptr);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    double posX = -70;
    bool game = false;
    bool colision = false;
    bool inicio = false;
    bool jugar_nivel = true;
    bool win = false;

signals:
    void moveBackground(int dx);

private slots:
    void runPlayer();
    void jumpPlayer();

private:
    QTimer *timer;
    QTimer *timer2;
    QSet<int> keysPressed;
    int lugar_saltoX = 0;
    int lugar_saltoY = 0;
    int cont = 0;
    int distancia = 0;
    bool tocar_arriba = false;
    bool subir = true;
    bool salto = true;
    bool coli = false;
    bool saltando = false;

    void initializePlayer();
    void moveRight();
};

#endif // PERSONAJE_H
