#include "mecanicaprincipal.h"

MecanicaPrincipal::MecanicaPrincipal(QGraphicsScene *scene)
{
    escena = scene;
    TiempoMusica = new QTimer();
    zonasPeligro = new QTimer();
    reproductor = new QMediaPlayer();

    connect(TiempoMusica,SIGNAL(timeout()),this,SLOT(CambiarZonas()));
    reproductor->setMedia(QUrl("qrc:/Canciones/Daft Punk - Around The World.mp3"));

}

MecanicaPrincipal::~MecanicaPrincipal()
{
    delete TiempoMusica;
    delete zonasPeligro;
    delete reproductor;
    for(int zona=0;zona < secciones.size();zona++){
        delete secciones[zona];
    }
}

void MecanicaPrincipal::CrearZonas()
{
    for(unsigned int i=0;i<difs[dificultad][0];i++){
        for(unsigned int c=0;c<difs[dificultad][0];c++){
            secciones.push_back((escena->addRect(i*(600/difs[dificultad][0]),80+c*(600/difs[dificultad][0]),600/difs[dificultad][0],600/difs[dificultad][0],QPen(Qt::red))));
            secciones[c+(i*difs[dificultad][0])]->hide();
        }
    }
}

void MecanicaPrincipal::IniciarJuego(){


    reproductor->setVolume(20);
    tzonas=0;
    tiempo=0;
    Zonas.clear();

    for(int zona=0;zona < secciones.size();zona++){
        escena->removeItem(secciones[zona]);
        delete secciones[zona];
    }
    secciones.clear();
    CrearZonas();

    TiempoMusica->thread()->sleep(1);
    TiempoMusica->start(difs[dificultad][1]);
    reproductor->play();
}

void MecanicaPrincipal::showZonas()
{
    for(int z=0;z<Zonas.size();z++){
        secciones[Zonas[z]]->show();
    }
}

void MecanicaPrincipal::hideZonas()
{
    for(int z=0;z<Zonas.size();z++){
        secciones[Zonas[z]]->hide();
    }
}

void MecanicaPrincipal::setDificultad(unsigned int d)
{
    dificultad=d;
}

void MecanicaPrincipal::setPos(long p)
{
    reproductor->setPosition(p);
}

void MecanicaPrincipal::CambiarZonas()
{
    int x;
    //eleccion de zonas aleatorias
    if(tiempo ==0){
        for(unsigned int i=0;i<(difs[dificultad][0])+(9*(dificultad)+4);i++){
            do{x=aleatorio(0,secciones.size()-1);}
            while(Zonas.count(x)>0);
            Zonas.push_back(x);
        }
        showZonas();
        tiempo++;
        TiempoMusica->start(difs[dificultad][2]);
    }
    else if(tiempo ==1) AcZonasPeligro();
    else{
        tiempo = 0;
        Zonas.clear();
        TiempoMusica->start(1000);
    }
}

void MecanicaPrincipal::AcZonasPeligro()
{
    for(int z =0;z<Zonas.size();z++){
        if(tzonas==0){secciones[Zonas[z]]->setBrush(QBrush(Qt::red,Qt::Dense7Pattern));}
        else if(tzonas==1){secciones[Zonas[z]]->setBrush(QBrush(Qt::red,Qt::Dense6Pattern));}
        else if(tzonas==2) {secciones[Zonas[z]]->setBrush(QBrush(Qt::red,Qt::DiagCrossPattern)); reproductor->setVolume(100);}
        else if(tzonas==3){
            secciones[Zonas[z]]->setBrush(QBrush(Qt::red,Qt::NoBrush));
            reproductor->setVolume(20);
            hideZonas();
        }
    }
    if(tzonas==4){
        tiempo++;
        tzonas=0;

    }
    else tzonas++;
}

int MecanicaPrincipal::aleatorio(int a, int b){
    int num;
    num=a+rand()%((b+1)-a);
    return num;
}

