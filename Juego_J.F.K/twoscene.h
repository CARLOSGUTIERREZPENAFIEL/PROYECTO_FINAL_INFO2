#ifndef TWOSCENE_H
#define TWOSCENE_H

#include <QGraphicsScene>

class MainWindow;

class twoscene : public QGraphicsScene
{
    Q_OBJECT

public:
    twoscene(MainWindow *parent = nullptr);
private:
    MainWindow *mainWindow;
};

#endif // TWOSCENE_H
