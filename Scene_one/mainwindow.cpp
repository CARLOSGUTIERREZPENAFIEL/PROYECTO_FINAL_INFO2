#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gscene.h"
#include "fscene.h"
#include <QScreen>
#include <QVBoxLayout>
#include <QPalette>
#include <QPushButton>
#include <QGraphicsProxyWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), First_Scene(nullptr), scene_two(nullptr), View_Velocimetro(nullptr)
{
    ui->setupUi(this);

    graphicsView = new QGraphicsView(this);
    setCentralWidget(graphicsView);

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    int frameHeight = frameGeometry().height() - geometry().height();

    int viewWidth = screenWidth;
    int viewHeight = screenHeight - frameHeight;

    graphicsView->setFixedSize(viewWidth, viewHeight);

    QGraphicsScene *initialScene = new QGraphicsScene(this);
    graphicsView->setScene(initialScene);
    initialScene->setBackgroundBrush(QBrush(QPixmap(":/imagenes/fondo_niv.png")));
    QPushButton *button1 = new QPushButton("Nivel 1");
    QPushButton *button2 = new QPushButton("Botón 2");
    QPushButton *button3 = new QPushButton("Botón 3");
    QString buttonStyle1 = "QPushButton {"
                           "background-image: url(:/imagenes/n1_on);"
                           "background-repeat: no-repeat;"
                           "background-position: center;"
                           "border: none;"
                           "width: 100px;"
                           "height: 30px;"
                           "}";

    QString buttonStyle2 = "QPushButton {"
                           "background-image: url(:/imagenes/n2_off);"
                           "background-repeat: no-repeat;"
                           "background-position: center;"
                           "border: none;"
                           "width: 100px;"
                           "height: 30px;"
                           "}";

    QString buttonStyle3 = "QPushButton {"
                           "background-image: url(:/imagenes/n2_off);"
                           "background-repeat: no-repeat;"
                           "background-position: center;"
                           "border: none;"
                           "width: 100px;"
                           "height: 30px;"
                           "}";

    button1->setStyleSheet(buttonStyle1);
    button2->setStyleSheet(buttonStyle2);
    button3->setStyleSheet(buttonStyle3);
    // Añadir los botones a la escena a través de QGraphicsProxyWidget
    initialScene->addWidget(button1);
    initialScene->addWidget(button2);
    initialScene->addWidget(button3);

    connect(button1, &QPushButton::clicked, this, &MainWindow::onBlueButtonClicked);
    connect(button2, &QPushButton::clicked, this, &MainWindow::onRedButtonClicked);
    connect(button3, &QPushButton::clicked, this, &MainWindow::onGreenButtonClicked);


    // Posicionar los botones en la escena

    button1->setGeometry(-450, 0, 400, 400);
    button2->setGeometry(0, 0, 400, 400);
    button3->setGeometry(450, 0, 400, 400);
    // Establecer la escena en el QGraphicsView
}

MainWindow::~MainWindow()
{
    delete ui;
    delete First_Scene;
    delete scene_two;
}

void MainWindow::onBlueButtonClicked()
{

    First_Scene = new FScene(this);
    graphicsView->setScene(First_Scene);

    scene_two = new GScene(this);
    View_Velocimetro = new QGraphicsView(this);
    View_Velocimetro->setScene(scene_two);

    View_Velocimetro->setGeometry(1665, 808, 250, 250);
    View_Velocimetro->show();

    velocimetro = new QLCDNumber(this);
    velocimetro->setObjectName("velocimetro");
    velocimetro->setGeometry(1750, 995, 64, 23);

    QPalette palette = velocimetro->palette();
    velocimetro->setFrameStyle(QFrame::NoFrame);
    palette.setColor(QPalette::WindowText, Qt::black);
    palette.setColor(QPalette::Light, Qt::black);
    palette.setColor(QPalette::Dark, Qt::black);
    velocimetro->setPalette(palette);
    velocimetro->show();
}

void MainWindow::onRedButtonClicked()
{


    First_Scene = new FScene(this);
    graphicsView->setScene(First_Scene);
}

void MainWindow::onGreenButtonClicked()
{


    First_Scene = new FScene(this);
    graphicsView->setScene(First_Scene);
}
