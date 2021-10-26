#include "personaje.h"

Personaje::Personaje(int x, int y)
{
    Default = QPixmap(":/img/Mov_Personaje.png");
    setPixmap(Default.copy(0,0,14,12).scaled(30,30));
    setPos(x,y);
    px=x;
    py=y;
    pies = new QRect(5,0,10,2);
}

void Personaje::getPos(QList<QGraphicsItem *> objetos, int tipe)
{
    int Pox,Poy, gravedad=5; // Po: posicion del objeto
    QRect pies,cabeza,derecha,izquierdo, bloque;
    pies=QRect(px+10,py+25,10,1);
    izquierdo=QRect(px,py+5,1,10);
    cabeza=QRect(px+5,py,10,1);
    derecha=QRect(px+28,py+5,1,10);


    if(objetos.size()==0) suelo=false;
    else{
        for(int i =0;i<objetos.size();i++){
            if(objetos[i]->type()==tipe){
                Pox=objetos[i]->x(), Poy=objetos[i]->y();
                bloque=QRect(Pox,Poy,40,40);
                if(ComprobarCollision(bloque,pies)){
                    vy=0;
                    py=Poy-29;
                    suelo = true;
                    setPos(px,py);

                }
                if(ComprobarCollision(izquierdo,bloque)){
                    vx=0;
                    px=Pox+40;
                    setPos(px,py);
                }
                if(ComprobarCollision(bloque,cabeza)){
                    vy=0;
                    py=Poy+40;
                    setPos(px,py);
                }
                if(ComprobarCollision(derecha,bloque)){
                    vx=0;
                    px=Pox-30;
                    setPos(px,py);
                }

                break;
            }
        }
    }
    if(vx>0 && suelo) ax=-0.9*2;
    else if(vx<0 && suelo) ax=0.9*2;
    ax=0;

    // limites de velocidad en x
    if(vx<-24) vx=-18;
    else if(vx>24) vx=18;


    if(Salto){
         vy += 25, Salto=false;
    }
    py = py-vy*0.2+0.5*gravedad*(0.2)*(0.2);


    px = px+vx*0.2; //simulacion de pos en x
    setPos(px,py); //cambio en la pos del personaje
    vx= vx +0.2*ax;
    vy= vy -0.2*gravedad;
    ax=0;

}
bool Personaje::ComprobarCollision(QRect rect1,QRect rect2){
    //bool colision = false;
    if ( rect1.x() > rect2.x()+rect2.width())  return false;
    if ( rect1.x()+rect1.width() < rect2.x())  return false;
    if ( rect1.y() > rect2.y()+rect2.height()) return false;
    if ( rect1.y()+rect1.height() < rect2.y()) return false;
    else return true;
    //return colision;
}

