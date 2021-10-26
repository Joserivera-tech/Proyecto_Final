#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timeGame= new QTimer();
    player = new Personaje(300,460);

    set_window();
    CrearMapa(1);



    //scene->addItem()
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

void MainWindow::Const_Plataforma(int x, int y, int largo, int alto, bool fondo)
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
            P1->Set_plataforma(tipo,bloque,fondo);
            plataf.push_back(P1);
            P1->setPos(x+(c*40),y+(f*40)+80);
            scene->addItem(P1);
        }
    }
}

void MainWindow::CrearMapa(int TipoDeNivel)
{
    int Limites[4][5]{
        {0,500,15,3,true},//limite inferior
        {-40,0,1,15,true},//limite izquierdo
        {600,0,1,15,true},//limite derecho
        {0,-40,15,1,true} //limite superior
    };
    int Nivel1[][5]={
        {200,280,3,1,true},
        {40,340,1,4,true},
        {400,340,2,4,true},
        {80,430,2,1,true},
        {280,395,3,1,true}
    };
    for(int p=0;p<4;p++){
        Const_Plataforma(Limites[p][0],Limites[p][1],Limites[p][2],Limites[p][3],Limites[p][4]);
    }

    int Nplataformas[3]={5,0,0};
    for(int n=0;n<Nplataformas[TipoDeNivel-1];n++){
        if(TipoDeNivel==1) Const_Plataforma(Nivel1[n][0],Nivel1[n][1],Nivel1[n][2],Nivel1[n][3],Nivel1[n][4]);
    }
}

void MainWindow::movP()
{
    player->getPos(player->collidingItems(),P1->type());
}

void MainWindow::on_Reset_clicked()
{
    player->px=300;
    player->py=460;
}

void MainWindow::keyPressEvent(QKeyEvent *i)
{
    if(i->key()==Qt::Key_A){
        player->vx-=10;
    }
    else if(i->key()==Qt::Key_D){
        player->vx+=10;
    }
    else if(i->key()==Qt::Key_W && player->suelo && !player->Salto){
        player->Salto=true;
    }

}
