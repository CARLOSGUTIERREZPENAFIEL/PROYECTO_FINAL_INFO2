#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QSet>
#include <QPixmap>
#include <QKeyEvent>


class Personaje : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Personaje(QGraphicsItem *parent = nullptr);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

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
    double posYorigin;
    bool subir = true;
    bool salto = false;
    bool coli = false;

    void initializePlayer();
};

#endif // PERSONAJE_H
