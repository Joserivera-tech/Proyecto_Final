#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QTimer>
#include <QVector>
#include <QKeyEvent>

#include "plataformas.h"
#include "personaje.h"

#define tam 40
#define fil 15
#define col 15

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void movP();

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene, *puntaje;

    QTimer *timeGame;

    Plataformas *P1;
    Personaje *player;

    QVector<Plataformas *> plataf;



    void set_window();
    void Const_Plataforma(int x, int y, int largo, int alto);
    void keyPressEvent(QKeyEvent *i);
};
#endif // MAINWINDOW_H
