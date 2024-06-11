#ifndef TWOSCENE_H
#define TWOSCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include <QKeyEvent>
#include "jfk.h"

class MainWindow;

class Bala : public QGraphicsPixmapItem
{
public:
    Bala(bool especial, QGraphicsItem *parent = nullptr);

    void advance(int phase) override;
    bool esEspecial() const;

private:
    bool especial;
    double angulo;
    double velocidad;
    double gravedad;
};

class Potenciador : public QGraphicsPixmapItem
{
public:
    Potenciador(QGraphicsItem *parent = nullptr);
};

class twoscene : public QGraphicsScene
{
    Q_OBJECT

public:
    twoscene(MainWindow *parent = nullptr);
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void generarBala();
    void generarBalaEspecial();
    void generarPotenciador();
    void actualizarJuego();
    void eliminarPotenciador();
    void terminarPotenciador();

private:
    void comprobarColisiones();

    MainWindow *mainWindow;
    jfk *carro;
    QTimer *temporizadorBala;
    QTimer *temporizadorBalaEspecial;
    QTimer *temporizadorPotenciador;
    QTimer *temporizadorJuego;
    QTimer *temporizadorEliminarPotenciador;
    QTimer *temporizadorTerminarPotenciador;
    int vidas;
    int puntuacion;
    bool juegoPausado;
    int tiempoTranscurrido;
    bool potenciadorActivo;
};

#endif // TWOSCENE_H
