#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(string user,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    usr=user;

    inicializar();

    mecanica->setDificultad(dificult-1);
    connect(timeGame,SIGNAL(timeout()),this,SLOT(movP()));
    connect(mecanica->reproductor,&QMediaPlayer::positionChanged,[&](qint64 pos){
        if(pos>punt) punt=pos*100/maxPunt;
        ui->Progresodecancion->setValue(pos);

    });
    connect(mecanica->reproductor,&QMediaPlayer::durationChanged,[&](qint64 dur){
        if(dur>maxPunt) maxPunt=dur;

    });


}

void MainWindow::Iniciar(long p)
{
    punt=0;
    ui->Progresodecancion->setMaximum(100);
    mecanica->setDificultad(dificult);
    mecanica->setPos(0);
    mecanica->IniciarJuego();
    timeGame->start(20);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
    delete player;
    delete timeGame;
    mecanica->~MecanicaPrincipal();
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
    setWindowTitle("InGame");
    setWindowIcon(QPixmap(":/img/logo.png"));

}

void MainWindow::inicializar()
{
    timeGame= new QTimer();
    set_window();
    CrearMapa(1);
    player = new Personaje(300,460, plataf.toList(),Trampo.toList());
    Gameover = new QGraphicsPixmapItem(QPixmap(":/img/gameOver.png").scaledToWidth(600,Qt::SmoothTransformation));
    Victory = new QGraphicsPixmapItem(QPixmap(":/img/Victory.jpeg").scaledToWidth(600,Qt::SmoothTransformation));
    Gameover->setPos(0,300-(Gameover->pixmap().height()/2)+80);
    Victory->setPos(0,300-(Victory->pixmap().height()/2)+80);
    mecanica = new MecanicaPrincipal(scene);
    scene->addItem(player);
}

void MainWindow::Const_Plataforma(int x, int y, int largo, int alto, bool fondo, int tipo)
{
    int bloque;

    for(int c=0;c<largo;c++){
        for(int f=0;f<alto;f++){
            if(f==0){
                if(tipo == 6) bloque =2;
                else if(largo ==1) bloque =0;
                else if(c==0&&f==0) bloque=1;
                else if(c+1<largo) bloque = 2;
                else if(c+1==largo) bloque =3;
            }
            else bloque=4;

            P1= new Plataformas();
            P1->tipe=tipo;
            P1->Set_plataforma(tipo,bloque,fondo);
            if(tipo==6) Trampo.push_back(P1);
            else plataf.push_back(P1);
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
    int Nivel1[][6]={
        {160,280,4,1,true,1},
        {0,340,1,4,true,1},
        {560,340,2,4,true,1},
        {80,430,2,1,true,1},
        {280,395,3,1,true,1},
        {0,180,4,1,true,1},
        {340,180,4,1,true,1},
        {200,70,2,1,true,1},
        {520,70,2,1,true,1},

        //trampolines
        {80,390,1,1,false,6},
        {520,460,1,1,false,6},
        {320,360,1,1,false,6},
        {200,240,1,1,false,6},
        {420,140,1,1,false,6}
    };
    for(int p=0;p<4;p++){
        Const_Plataforma(Limites[p][0],Limites[p][1],Limites[p][2],Limites[p][3],Limites[p][4],Nivel1[p][5]);
    }

    int Nplataformas[3]={14,0,0};
    for(int n=0;n<Nplataformas[TipoDeNivel-1];n++){
        if(TipoDeNivel==1) Const_Plataforma(Nivel1[n][0],Nivel1[n][1],Nivel1[n][2],Nivel1[n][3],Nivel1[n][4],Nivel1[n][5]);
    }
}

string MainWindow::leer(bool modo)
{
    string datos;
    fstream text;
    if(modo){
        fstream text("users.txt", fstream::in);
        if(text.is_open()){
            while(!text.eof())datos.push_back(text.get());
            datos.pop_back();
        }
        else cout<<"El archivo no pudo ser abierto"<<endl;
    }
    else{
        text.open("users.txt", fstream::in | fstream::binary | fstream::ate);
        if(text.is_open()){
            text.seekg(0);
            for(unsigned long long i=0; i<tam; i++) datos.push_back(text.get());
        }
        else cout<<"El archivo no pudo ser abierto"<<endl;
    }
    text.close();
    return datos;

}

void MainWindow::modificar_Score(string lineaDatos, string new_linea)
{
    string buscar;      // texto a buscar
    string reemplazar;  // reemplazar por
    string contenido=leer(true);

    buscar=lineaDatos;
    reemplazar=new_linea;


    ifstream fs("users.txt"); //leer de este archivo
    ofstream fstemp("nuevoUsers.txt"); //escribir en este archivo
    if(!fs || !fstemp) //no se pudo abrir alguno de los 2
    {
      cout << "Error al abrir el archivo!" << endl;
    }

    //modificar linea a linea
    while(fs >> contenido)
    {
      if(contenido == buscar){  //se encontro
        contenido = reemplazar; //reemplazar
      }
      fstemp << contenido << endl;
    }

    //reemplazar un archivo por otro
    fs.close();
    fstemp.close();
    remove("users.txt");                    // borrar el original
    rename("nuevoUsers.txt", "users.txt");  // renombrar el temporal
}

void MainWindow::movP()
{
    if(player->vida && punt <100){
        player->getPos(player->collidingItems(),P1->type(), mecanica->secciones[0]->type(), mecanica->tzonas);
    }
    else if(punt==100){
        scene->addItem(Victory);
        timeGame->stop();
        mecanica->reproductor->stop();
        mecanica->TiempoMusica->stop();
        ui->Pausa->setEnabled(false);
    }
    else{
        scene->addItem(Gameover);
        timeGame->stop();
        mecanica->reproductor->stop();
        mecanica->TiempoMusica->stop();
        ui->Pausa->setEnabled(false);
    }

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

void MainWindow::on_Reset_clicked()
{
    player->px=300;
    player->py=460;
    player->vx=0;
    player->vy=0;
    if(!player->vida || scene->items().count(Victory)>0){
        player->vida=true;
        ui->Pausa->setEnabled(true);
        scene->removeItem(Gameover);
        scene->removeItem(Victory);
    }
    Iniciar(0);
}

void MainWindow::on_Pausa_clicked()
{
    if(timeGame->isActive()){
        timeGame->stop();
        mecanica->reproductor->pause();
        mecanica->TiempoMusica->stop();
        ui->Guardar->setEnabled(true);
    }
    else{
        timeGame->start(20);
        mecanica->reproductor->play();
        mecanica->TiempoMusica->start(2000);
        ui->Guardar->setEnabled(false);
    }
}

void MainWindow::on_Guardar_clicked()
{
    string dic="";
    fstream guardado;

    dic=usr+".txt";
    guardado.open(dic, fstream::out);
    cout <<"escribiendo";

    guardado << punt << endl;
    guardado << player->px << endl;
    guardado << player->py << endl;
    guardado << player->vx << endl;
    guardado << player->vy << endl;
    guardado << dificult;
    guardado.close();
}



void MainWindow::on_exit_clicked()
{
    fstream archivo("users.txt");
    string linea, dato, arreglo[3];
    size_t pos;
    int contador =0, fin =0;
    while(getline(archivo,linea)&&fin==0){
        while ((pos = linea.find(",")) != std::string::npos){

            dato = linea.substr(0, pos);
            arreglo[contador]=dato;
            linea.erase(0, pos + 1);
            contador++;
        }
        if (arreglo[0].find(usr, 0) != string::npos){
            fin=1;
        }
        contador=0;
    }
    archivo.close();
    linea="";
    dato="";
    for(int d=0;d<3;d++){
        linea+=arreglo[d]+",";
        if(d<2) dato+=arreglo[d]+",";
        else dato+=to_string(punt*100/maxPunt)+",";
    }
    if(punt*100/maxPunt>stoi(arreglo[2])){
        modificar_Score(linea,dato);
    }
    this->hide();
}
