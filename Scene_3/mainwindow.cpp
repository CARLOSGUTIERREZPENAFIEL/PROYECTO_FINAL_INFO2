#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new TScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->scale(0.95, 0.95);


}

MainWindow::~MainWindow()
{
    delete ui;
}
