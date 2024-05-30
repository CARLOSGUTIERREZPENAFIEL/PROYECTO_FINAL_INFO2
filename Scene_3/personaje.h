#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Personaje : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Personaje(QObject *parent = nullptr);
    void run();
    void jump();

private:
    QTimer *timer;
    int cont;
    bool salto;
    bool subir;
    int distancia;

signals:

};

#endif // PERSONAJE_H
