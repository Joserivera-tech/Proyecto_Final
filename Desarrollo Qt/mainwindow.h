#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QTimer>
#include <QVector>
#include <QKeyEvent>
#include <QDir>
#include <QDebug>
#include <fstream>

#include "plataformas.h"
#include "personaje.h"
#include "mecanicaprincipal.h"

#define tam 40
#define fil 15
#define col 15

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void on_Reset_clicked();
private slots:
    void movP();

    void on_Pausa_clicked();
    void on_Guardar_clicked();

    void on_exit_clicked();

public:
    int dificult=1,punt=0;
    MecanicaPrincipal *mecanica;
    Personaje *player;

    MainWindow(string user,QWidget *parent = nullptr);
    void Iniciar(long p);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene, *puntaje;

    QTimer *timeGame;

    QGraphicsPixmapItem *Gameover, *Victory;
    Plataformas *P1;


    QDir direc;

    bool save=false;
    long  maxPunt=0;
    string usr;

    QVector<Plataformas *> plataf;
    QVector<Plataformas *> Trampo;

    void set_window();
    void inicializar();
    void Const_Plataforma(int x, int y, int largo, int alto,bool fondo, int tipo);
    void CrearMapa(int TipoDeNivel);
    string leer(bool modo);
    void modificar_Score(string lineaDatos, string new_score);
    void keyPressEvent(QKeyEvent *i);
};
#endif // MAINWINDOW_H
