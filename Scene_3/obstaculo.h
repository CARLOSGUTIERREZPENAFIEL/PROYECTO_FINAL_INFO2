#ifndef OBSTACULO_H
#define OBSTACULO_H
#include <QGraphicsPixmapItem>
#include <QPixmap>
class obstaculo: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    obstaculo();
};

#endif // OBSTACULO_H
