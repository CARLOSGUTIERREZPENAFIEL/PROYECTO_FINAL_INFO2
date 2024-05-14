#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gscene.h"
#include "fscene.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    First_Scene = new FScene(this);
    ui->graphicsView->setScene(First_Scene);

    scene_two = new GScene(this);
    ui->veloc->setScene(scene_two);

    auto palette = ui->velocimetro->palette();
    palette.setColor(palette.WindowText, Qt::black);
    palette.setColor(palette.Light, Qt::black);
    palette.setColor(palette.Dark, Qt::black);
    ui->velocimetro->setPalette(palette);
}

MainWindow::~MainWindow()
{
    delete ui;
}


