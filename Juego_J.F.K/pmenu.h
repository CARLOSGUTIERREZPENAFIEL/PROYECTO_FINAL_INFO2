#ifndef PMENU_H
#define PMENU_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGraphicsTextItem>
#include <QGraphicsProxyWidget>
#include <QString>
#include <QKeyEvent>

class PMenu : public QWidget {
    Q_OBJECT

public:
    explicit PMenu(const QString& text, int level, QWidget* parent = nullptr);
    PMenu(const QString& text, int level, bool showResumeButton, QWidget* parent = nullptr);

signals:
    void retry(int level);
    void goToMenu();
    void resume(); // Señal para reanudar el juego

public slots:
    void closeMenu(); // Slot para cerrar el menú

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    int m_level;
    QGraphicsView* view;
    QGraphicsScene* scene;
    QGraphicsTextItem* textItem;
    QPushButton* retryButton;
    QPushButton* menuButton;
    QPushButton* resumeButton;
    void setupWindow();
};

#endif // PMENU_H
