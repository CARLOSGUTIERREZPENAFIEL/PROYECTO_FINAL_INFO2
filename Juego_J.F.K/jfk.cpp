#include "jfk.h"
#include <QGraphicsScene>

jfk::jfk(QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent), direccionActual(""), velocidad(5), tiempoPotenciador(0)
{
    setPixmap(QPixmap(":/imagenes/carroDER2"));
}

void jfk::establecerDireccion(const QString &direccion)
{
    if (direccionActual != direccion) {
        direccionActual = direccion;
        if (direccionActual == "izquierda") {
            setPixmap(QPixmap(":/imagenes/carroIZQ2"));
        } else if (direccionActual == "derecha") {
            setPixmap(QPixmap(":/imagenes/carroDER2"));
        } else if (direccionActual == "izquierda_p") {
            setPixmap(QPixmap(":/imagenes/carroIZQ2p"));
        } else if (direccionActual == "derecha_p") {
            setPixmap(QPixmap(":/imagenes/carroDER2p"));
        }
    }
}

void jfk::establecerVelocidad(int nuevaVelocidad)
{
    velocidad = nuevaVelocidad;
}

void jfk::establecerTiempoPotenciador(int nuevoTiempoPotenciador)
{
    tiempoPotenciador = nuevoTiempoPotenciador;
}

int jfk::obtenerVelocidad() const
{
    return velocidad;
}

int jfk::obtenerTiempoPotenciador() const
{
    return tiempoPotenciador;
}

void jfk::actualizarPosicion()
{
    if (direccionActual == "izquierda" || direccionActual == "izquierda_p") {
        setPos(qMax(0.0, x() - velocidad), y());
    } else if (direccionActual == "derecha" || direccionActual == "derecha_p") {
        setPos(qMin(1850.0, x() + velocidad), y());
    }
}

void jfk::reiniciarImagen()
{
    if (direccionActual == "izquierda_p") {
        setPixmap(QPixmap(":/imagenes/carroIZQ2"));
    } else if (direccionActual == "derecha_p") {
        setPixmap(QPixmap(":/imagenes/carroDER2"));
    }
}

void jfk::advance(int phase)
{
    if (!phase) return;

    if (tiempoPotenciador > 0) {
        tiempoPotenciador--;
        if (tiempoPotenciador == 0) {
            velocidad = 5;
            reiniciarImagen();
        }
    }
}
