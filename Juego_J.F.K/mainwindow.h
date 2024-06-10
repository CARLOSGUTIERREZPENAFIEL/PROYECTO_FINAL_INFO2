#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mscene.h"
#include "tscene.h"
#include "twoscene.h"
#include "qlcdnumber.h"
#include <QMainWindow>
#include <QGraphicsView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

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

    GScene* getGScene() const { return Vel_FScene; }

public slots:
    void onMenuButtonClicked();
    void onLevelSelected(int level);
    void removeVelocimetroView();
    void showInitialScene();

private:
    Ui::MainWindow *ui;
    FScene *First_Scene;
    GScene *Vel_FScene;
    TScene *Third_Scene;
    twoscene *Two_Scene;
    MScene *Menu_Scene;
    QGraphicsScene *initialScene;
    QGraphicsView *graphicsView;
    QGraphicsView *View_Velocimetro;
    QLCDNumber *velocimetro;
    QPushButton *menuButton;
    QLabel *Cred;
    QLabel *titulo;
};

#endif // MAINWINDOW_H
