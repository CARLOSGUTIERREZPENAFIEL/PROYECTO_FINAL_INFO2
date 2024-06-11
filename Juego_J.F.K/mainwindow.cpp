#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gscene.h"
#include "fscene.h"
#include "mscene.h"
#include "tscene.h"
#include <QScreen>
#include <QVBoxLayout>
#include <QPalette>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), First_Scene(nullptr), Vel_FScene(nullptr), Third_Scene(nullptr), View_Velocimetro(nullptr), Menu_Scene(nullptr)
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

    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    menuButton = new QPushButton(this);
    QString buttonStyleM = "QPushButton {"
                           "background-image: url(:/imagenes/boton_start);"
                           "background-repeat: no-repeat;"
                           "background-position: center;"
                           "border: none;"
                           "width: 793px;"
                           "height: 250px;"
                           "}";

    menuButton->setStyleSheet(buttonStyleM);
    connect(menuButton, &QPushButton::clicked, this, &MainWindow::onMenuButtonClicked);

    int buttonWidth = menuButton->width();
    int buttonHeight = menuButton->height();
    int buttonX = ((viewWidth - buttonWidth) / 2) - 396.5;
    int buttonY = ((viewHeight - buttonHeight) / 2) - 125;
    menuButton->setGeometry(0,0,793,250);
    menuButton->move(buttonX, buttonY);

    titulo = new QLabel("J.F.K", this);
    titulo->setStyleSheet("QLabel { color: white; font-size: 200px; }");
    titulo->adjustSize();
    int labelWidth = 396.5-(titulo->width()/2);
    titulo->move(menuButton->x()+labelWidth, menuButton->y() - 250);

    Cred = new QLabel("Juego proyecto final info 2 \n- Creado por Andrés G y Carlos G.", this);
    Cred->setStyleSheet("QLabel { color: white; font-size: 25px; }");
    Cred->adjustSize();
    Cred->move(20, 950);

    initialScene = new QGraphicsScene(this);
    initialScene->setSceneRect(2, 2, viewWidth, viewHeight);
    graphicsView->setScene(initialScene);
    initialScene->setBackgroundBrush(QBrush(QPixmap(":/imagenes/fondo_niv.png").scaled(viewWidth, viewHeight)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete First_Scene;
    delete Vel_FScene;
    delete Menu_Scene;
    delete Third_Scene;
}

void MainWindow::onMenuButtonClicked()
{
    if (!Menu_Scene) {
        Menu_Scene = new MScene(this);
        connect(Menu_Scene, &MScene::levelSelected, this, &MainWindow::onLevelSelected);
    }
    graphicsView->setScene(Menu_Scene);
    menuButton->hide();
    titulo->hide();
}

void MainWindow::onLevelSelected(int level)
{
    qDebug() << "nivel seleccionado:" << level;

    if (First_Scene) {
        qDebug() << "elimando First_Scene";
        delete First_Scene;
        First_Scene = nullptr;
        removeVelocimetroView();

    }
    if (Vel_FScene) {
        qDebug() << "elimando Vel_FScene";
        delete Vel_FScene;
        Vel_FScene = nullptr;
    }
    if (Third_Scene) {
        qDebug() << "elimando Third_Scene";
        delete Third_Scene;
        Third_Scene = nullptr;
    }


    if (level == 1) {
        qDebug() << "Crea First_Scene";
        First_Scene = new FScene(this);
        graphicsView->setScene(First_Scene);

        qDebug() << "Crea Vel_FScene";
        Vel_FScene = new GScene(this);
        View_Velocimetro = new QGraphicsView(this);
        View_Velocimetro->setScene(Vel_FScene);

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
        Cred->hide();

    } else if (level == 2) {
        qDebug() << "Crea Two_Scene para level 2";
        Two_Scene = new twoscene(this);
        graphicsView->setScene(Two_Scene);
        Cred->hide();

    } else if (level == 3) {
        qDebug() << "Crea Third_Scene";
        Third_Scene = new TScene(this);
        graphicsView->setScene(Third_Scene);
        Cred->hide();
    } else if (level == 4) {
        qDebug() << "muestra la initialScene";
        graphicsView->setScene(initialScene);
        menuButton->show();
        titulo->show();
        Cred->show();
        delete Menu_Scene;
        Menu_Scene = nullptr;
    }
}

void MainWindow::removeVelocimetroView()
{
    if (View_Velocimetro) {
        delete View_Velocimetro;
        View_Velocimetro = nullptr;
    }
    if (velocimetro) {
        delete velocimetro;
        velocimetro = nullptr;
    }
}

void MainWindow::showInitialScene()
{
    if (First_Scene) {
        delete First_Scene;
        First_Scene = nullptr;
        removeVelocimetroView();
    }
    if (Vel_FScene) {
        delete Vel_FScene;
        Vel_FScene = nullptr;
    }
    if (Third_Scene) {
        delete Third_Scene;
        Third_Scene = nullptr;
    }

    graphicsView->setScene(initialScene);
    menuButton->show();
    titulo->show();
    Cred->show();
}
