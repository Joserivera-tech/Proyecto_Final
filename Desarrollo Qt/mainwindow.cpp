#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    set_window();

    P1 = new Plataformas(3,1);
    P1->setPos(30,30);
    scene->addItem(P1);


}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
}

void MainWindow::set_window()
{
    scene = new QGraphicsScene;
    puntaje = new QGraphicsScene;

    scene->setBackgroundBrush(QPixmap(":/img/BackGround.png").scaled(1100,650).copy(250,0,650,650));
    puntaje->setBackgroundBrush(QColor(23,16,60));
    ui->graphicsView->setGeometry(0,tam*2,tam*col+2,tam*fil+4);
    ui->graphicsView_puntaje->setGeometry(0,0,tam*2*col,tam*2);

    scene->setSceneRect(0,tam*2,tam*col,tam*fil);//tamanio de la escena
    puntaje->setSceneRect(0,0,tam*2*col-2,tam*2-2);
    ui->graphicsView->setScene(scene);
    ui->graphicsView_puntaje->setScene(puntaje);
    setFixedSize(tam*col+4,tam*(fil+2));
    setWindowTitle("Titulo");
}

