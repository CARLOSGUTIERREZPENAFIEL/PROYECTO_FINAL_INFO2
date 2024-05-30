#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QDebug>
#include <QKeyEvent>
#include <QGraphicsPixmapItem>
#include <cmath>



QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void UpdateValues(double &xIn, double &yIn, double &tiempoX, double &tiempoY, double &velX, double &velY, double &ang, int &dir, bool &colX, QGraphicsPixmapItem &personaje1);

private slots:
    void run_player();
    void jump_player();

private:
    int lugar_saltoX = 0;
    int lugar_saltoY = 0;
    Ui::MainWindow *ui;
    QGraphicsScene *scene_3;
    QGraphicsPixmapItem *personaje1;
    QTimer *timer;
    QTimer *timer2;
    int cont = 0;
    int contY = 0;
    bool Jump = false;
    QSet<int> keysPressed;
    bool jump;
    double posYorigin;
    QGraphicsPixmapItem *caja;
    int distancia = 0;
    int contador_saltos=0;
    bool salto = false;
    bool subir = true;
    bool coli = false;



protected:
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
};
#endif // MAINWINDOW_H
