#ifndef MSCENE_H
#define MSCENE_H

#include <QGraphicsScene>
#include <QPushButton>

class MainWindow;

class MScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit MScene(QObject *parent = nullptr);

signals:
    void levelSelected(int level);

private slots:
    void onButton1Clicked();
    void onButton2Clicked();
    void onButton3Clicked();
    void onExitClicked();
private:
    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;
    QPushButton *back_menu;

    int nivel_total=1;
};

#endif // MSCENE_H
