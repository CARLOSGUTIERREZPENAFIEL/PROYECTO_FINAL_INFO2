#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gscene.h"
#include "fscene.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , First_Scene(nullptr)
    , scene_two(nullptr)
{
    ui->setupUi(this);

    auto palette = ui->velocimetro->palette();
    palette.setColor(palette.WindowText, Qt::black);
    palette.setColor(palette.Light, Qt::black);
    palette.setColor(palette.Dark, Qt::black);
    ui->velocimetro->setPalette(palette);

    connect(ui->buttonScene1, &QPushButton::clicked, this, &MainWindow::showScene1);
    connect(ui->buttonScene2, &QPushButton::clicked, this, &MainWindow::showScene2);

    // No es necesario crear un nuevo QGraphicsView
    graphicsView = ui->graphicsView;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete First_Scene;
    delete scene_two;
}

void MainWindow::showScene1()
{
    if (First_Scene) {
        delete First_Scene;
        First_Scene = nullptr;
    }

    First_Scene = new FScene(this);
    graphicsView->setScene(First_Scene);

    // Crear y agregar la segunda escena en el QGraphicsView específico para el velocímetro
    if (scene_two) {
        delete scene_two;
        scene_two = nullptr;
    }

    scene_two = new GScene(this);
    ui->veloc->setScene(scene_two);
}

void MainWindow::showScene2()
{
    if (scene_two) {
        delete scene_two;
        scene_two = nullptr;
    }
    if (First_Scene) {
        delete First_Scene;
        First_Scene = nullptr;
    }

    // Cambia la escena actual a otra escena o una nueva si es necesario
    // Por ejemplo, podrías tener una tercera escena o simplemente limpiar el view:
    graphicsView->setScene(nullptr); // O una nueva escena
}
