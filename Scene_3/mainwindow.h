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
    void run_player();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene_3;
    QGraphicsPixmapItem *personaje1;
    QTimer *timer;
    int cont = 0;


protected:
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
    void simularCaminar();
};
#endif // MAINWINDOW_H
