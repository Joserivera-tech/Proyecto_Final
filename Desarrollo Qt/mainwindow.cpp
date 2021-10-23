#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timeGame= new QTimer();
    player = new Personaje(300,200);

    set_window();
    Const_Plataforma(0,550,15,3);
    Const_Plataforma(0,480,4,1);

    scene->addItem(player);
    connect(timeGame,SIGNAL(timeout()),this,SLOT(movP()));
    timeGame->start(30);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
    delete player;
    delete timeGame;
}

void MainWindow::set_window()
{
    scene = new QGraphicsScene;
    puntaje = new QGraphicsScene;

    scene->setBackgroundBrush(QPixmap(":/img/BackGround.png").scaled(1100,650).copy(250,0,650,650));
    puntaje->setBackgroundBrush(QColor(43,47,51));
    ui->graphicsView->setGeometry(0,tam*2,tam*col+2,tam*fil+4);
    ui->graphicsView_puntaje->setGeometry(0,0,tam*2*col,tam*2);

    scene->setSceneRect(0,tam*2,tam*col,tam*fil);//tamanio de la escena
    puntaje->setSceneRect(0,0,tam*col-2,tam*2-2);
    ui->graphicsView->setScene(scene);
    ui->graphicsView_puntaje->setScene(puntaje);
    setFixedSize(tam*col+4,tam*(fil+2));
    setWindowTitle("Titulo");
}

void MainWindow::Const_Plataforma(int x, int y, int largo, int alto)
{
    int tipo=1, bloque;

    for(int c=0;c<largo;c++){
        for(int f=0;f<alto;f++){
            if(f==0){
                if(c==0&&f==0) bloque=1;
                else if(c+1<largo) bloque = 2;
                else if(c+1==largo) bloque =3;
            }
            else bloque=4;


            P1= new Plataformas(0.3);
            P1->Set_plataforma(tipo,bloque);
            plataf.push_back(P1);
            P1->setPos(x+(c*40),y+(f*40)+80);
            scene->addItem(P1);
        }
    }
}

void MainWindow::movP()
{
    player->getPos(player->collidingItems(),P1->type());
}

void MainWindow::keyPressEvent(QKeyEvent *i)
{
    if(i->key()==Qt::Key_A){
        player->vx-=5;
    }
    else if(i->key()==Qt::Key_D){
        player->vx+=5;
    }
    else if(i->key()==Qt::Key_W && player->suelo){
        player->vy=30;
        if(player->suelo) player->suelo=false;
        //else if(player->dobleSalto) player->dobleSalto=false;
    }

}
