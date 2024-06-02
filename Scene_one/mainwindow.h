#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qlcdnumber.h"
#include <QMainWindow>
#include <QGraphicsView>
#include <QPushButton>
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}

class GScene;
class FScene;

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    GScene* getGScene() const { return scene_two; }

private slots:
    void onBlueButtonClicked();
    void onRedButtonClicked();
    void onGreenButtonClicked();

private:
    Ui::MainWindow *ui;
    FScene *First_Scene;
    GScene *scene_two;
    QGraphicsView *graphicsView;
    QGraphicsView *View_Velocimetro;
    QLCDNumber *velocimetro;


};

#endif // MAINWINDOW_H
