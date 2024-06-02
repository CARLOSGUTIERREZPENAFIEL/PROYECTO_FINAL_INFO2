#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gscene.h"
#include "fscene.h"
#include "mscene.h"
#include "tscene.h" // Asegúrate de tener esta línea si tienes una clase TScene.
#include <QScreen>
#include <QVBoxLayout>
#include <QPalette>
#include <QPushButton>
#include <QGraphicsProxyWidget>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), First_Scene(nullptr), Vel_FScene(nullptr), Third_Scene(nullptr), View_Velocimetro(nullptr)
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

    // Crear el botón para cambiar a la escena de menú
    menuButton = new QPushButton(this);
    QString buttonStyleM = "QPushButton {"
                           "background-image: url(:/imagenes/boton_start);"
                           "background-repeat: no-repeat;"
                           "background-position: center;"
                           "border: none;"
                           "width: 793px;"  // Ancho deseado del botón
                           "height: 250px;"
                           "}";

    menuButton->setStyleSheet(buttonStyleM);
    connect(menuButton, &QPushButton::clicked, this, &MainWindow::onMenuButtonClicked);

    // Calcular la posición central del botón
    int buttonWidth = menuButton->width();
    int buttonHeight = menuButton->height();
    int buttonX = ((viewWidth - buttonWidth) / 2) - 396.5;
    int buttonY = ((viewHeight - buttonHeight) / 2) - 125;
    menuButton->setGeometry(0,0,793,250);
    menuButton->move(buttonX, buttonY);



    // Agregar mensaje "J.F.K"
    titulo = new QLabel("J.F.K", this);
    titulo->setStyleSheet("QLabel { color: white; font-size: 200px; }");
    titulo->adjustSize();
    int labelWidth = 396.5-(titulo->width()/2);
    titulo->move(menuButton->x()+labelWidth, menuButton->y() - 250);

    //los creditos pai
    Cred = new QLabel("Juego proyecto final info 2 \n- Creado por Andrés G y Carlos P.", this);
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
    Menu_Scene = new MScene(this);
    graphicsView->setScene(Menu_Scene);
    menuButton->hide();
    titulo->hide();
    connect(Menu_Scene, &MScene::levelSelected, this, &MainWindow::onLevelSelected);

}

void MainWindow::onLevelSelected(int level)
{

    if (level == 1) {
        First_Scene = new FScene(this);
        graphicsView->setScene(First_Scene);

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
        First_Scene = new FScene(this);  // Puedes cambiar esto según el nivel seleccionado
        graphicsView->setScene(First_Scene);
        Cred->hide();

    } else if (level == 3) {
        Third_Scene = new TScene(this);  // Puedes cambiar esto según el nivel seleccionado
        graphicsView->setScene(Third_Scene);
        Cred->hide();
    } else if (level == 4) {
        graphicsView->setScene(initialScene);
        menuButton->show();
        titulo->show();
        delete Menu_Scene;
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
