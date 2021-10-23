#include "personaje.h"

Personaje::Personaje(int x, int y)
{
    Default = QPixmap(":/img/Mov_Personaje.png");
    setPixmap(Default.copy(0,0,14,12).scaled(30,30));
    setPos(x,y);
    px=x;
    py=y;
}

void Personaje::getPos(QList<QGraphicsItem *> objetos, int tipe)
{
    int Pox,Poy, gravedad=5; // Po: posicion del objeto
    ax=0;

    // limites de velocidad en x
    if(vx<-24) vx=-18;
    else if(vx>24) vx=18;

    px = px+vx*0.2; //simulacion de pos en x

    if(!suelo)py = py-vy*0.2+0.5*gravedad*(0.2)*(0.2);
    setPos(px,py); //cambio en la pos del personnaje

    if(objetos.size()==0) suelo=false;
    for(int i =0;i<objetos.size();i++){
        Pox=objetos[i]->type();
        if(objetos[i]->type()==tipe){
            Pox=objetos[i]->x(), Poy=objetos[i]->y();

            if(py+30>=Poy){
                vy=0;
                gravedad=0;
                py=Poy-30;
                setPos(px,py);
                suelo = true;
                dobleSalto=true;
                break;
            }
            else suelo = false;
        }
    }
    if(vx>0 && suelo) ax=-0.9*2;
    else if(vx<0 && suelo) ax=0.9*2;
    vx= vx +0.2*ax;
    vy= vy -0.2*gravedad;
    ax=0;
}

