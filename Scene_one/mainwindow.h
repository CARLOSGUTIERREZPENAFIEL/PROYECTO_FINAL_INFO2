#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QDebug>
#include <QKeyEvent>
#include <QGraphicsPixmapItem>

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

private slots:
    void acelerar();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene_uno;
    QGraphicsPixmapItem *car;
    QTimer *aceleracion;
    int vel_y;
    int vel_x;
    int contador_posicion_y;
    QSet<int> keysPressed;

protected:
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);

};
#endif // MAINWINDOW_H
