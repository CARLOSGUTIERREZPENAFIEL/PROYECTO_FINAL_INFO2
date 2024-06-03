#include "PMenu.h"
#include <QFont>
#include <QGraphicsProxyWidget>

PMenu::PMenu(const QString& text, int level, QWidget* parent)
    : PMenu(text, level, false, parent)
{
}

PMenu::PMenu(const QString& text, int level, bool showResumeButton, QWidget* parent)
    : QWidget(parent), m_level(level) {
    setupWindow();

    setFixedSize(800, 900);


    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    view->setFixedSize(800, 900);
    view->setSceneRect(0, 0, 800, 900);

    // Crear el texto y añadirlo a la escena
    textItem = new QGraphicsTextItem(text);
    QFont font = textItem->font();
    font.setPointSize(24);
    textItem->setFont(font);
    textItem->setPos(400 - textItem->boundingRect().width() / 2, 50); // Centrado horizontalmente
    scene->addItem(textItem);

    // Crear los botones
    retryButton = new QPushButton("Volver a intentar");
    menuButton = new QPushButton("Ir al menú");
    resumeButton = new QPushButton("Reanudar");

    // Crear un layout vertical para los botones
    QVBoxLayout* buttonLayout = new QVBoxLayout;
    if (showResumeButton) {
        buttonLayout->addWidget(resumeButton);
    }
    buttonLayout->addWidget(retryButton);
    buttonLayout->addWidget(menuButton);

    // Crear un widget para los botones y establecer el layout
    QWidget* buttonWidget = new QWidget;
    buttonWidget->setLayout(buttonLayout);

    // Crear un proxy widget para añadir el widget de botones a la escena
    QGraphicsProxyWidget* proxyWidget = scene->addWidget(buttonWidget);
    proxyWidget->setPos(400 - buttonWidget->width() / 2, 450); // Centramos el widget de botones horizontalmente

    // Conectar los botones a las funciones correspondientes
    connect(retryButton, &QPushButton::clicked, this, [this]() {
        emit retry(m_level);
        closeMenu();  // Cierra el menu de pausa pa que quede bien
    });
    connect(menuButton, &QPushButton::clicked, this, [this]() {
        emit goToMenu();
        closeMenu();
    });
    if (showResumeButton) {
        connect(resumeButton, &QPushButton::clicked, this, [this]() {
            emit resume();
            closeMenu();
        });
    }


    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(view);
    setLayout(mainLayout);
}

void PMenu::setupWindow() {
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setWindowModality(Qt::ApplicationModal);
}

void PMenu::closeMenu() {
    this->close();
}

void PMenu::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_P) {
        emit resume();
        closeMenu();
    }
    QWidget::keyPressEvent(event); // Llamar a la implementación base
}
