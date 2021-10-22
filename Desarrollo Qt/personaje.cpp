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

    px = px+vx*0.5;
    if(!suelo)py = py-vy*0.5+0.5*gravedad*(0.5)*(0.5);
    setPos(px,py);
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
                break;
            }
            else suelo = false;
        }
    }
    vx= vx +0.5*ax;
    vy= vy -0.5*gravedad;
}

