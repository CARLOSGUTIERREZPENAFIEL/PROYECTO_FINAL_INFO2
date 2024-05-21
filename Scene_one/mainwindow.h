#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QTimer>

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
    void showScene1();
    void showScene2();
private:
    Ui::MainWindow *ui;
    FScene *First_Scene;
    GScene *scene_two;
    QGraphicsView *graphicsView;  // Un solo QGraphicsView
};

#endif // MAINWINDOW_H
