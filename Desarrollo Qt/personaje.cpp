#include "personaje.h"

Personaje::Personaje(int x, int y, QList<Plataformas *> P , QList<Plataformas *> tromp)
{
    Default = QPixmap(":/img/Mov_Personaje.png");
    setPixmap(Default.copy(0,0,14,12).scaled(30,30));
    setPos(x,y);
    px=x;
    py=y;

    Plat=P;
    PTramp=tromp;
}

void Personaje::getPos(QList<QGraphicsItem *> objetos , int tipeP, int tipeD, int time)
{
    int Pox,Poy, gravedad=9; // Po: posicion del objeto
    float tiempoS = 0.2; // Tiempo de simulacion
    QRect pies,cabeza,derecha,izquierdo, bloque;

    if(objetos.size()==0) suelo=false;
    else{
        for(int i =0;i<objetos.size();i++){
            //rectangulos limitantes con el personaje
            pies=QRect(px+8,py+28,15,1);
            cabeza=QRect(px+8,py,15,1);
            izquierdo=QRect(px,py+7,1,10);
            derecha=QRect(px+29,py+7,1,10);

            //colisiones con plataformas
            if(objetos[i]->type()==tipeP){
                Pox=objetos[i]->x(), Poy=objetos[i]->y();
                bloque=QRect(Pox,Poy,40,40);//rectangulo del bloque con el que colisiona

                //comprueba en que parte esta colisionando
                if(ComprobarCollision(bloque,pies)){
                    vy=0;
                    for(unsigned int p =0; p<PTramp.size();p++){
                        if(ComprobarCollision(QRect(PTramp[p]->x(),PTramp[p]->y(),40,40),pies)){
                            vy+=45;
                        }
                    }


                    py=Poy-29;
                    suelo = true;
                }
                if(ComprobarCollision(izquierdo,bloque)){
                    vx=0;
                    px=Pox+40;
                }
                if(ComprobarCollision(bloque,cabeza)){
                    vy=0;
                    py=Poy+40;
                }
                if(ComprobarCollision(derecha,bloque)){
                    vx=0;
                    px=Pox-30;
                }
            }

            else if(objetos[i]->type()==tipeD && time>2){
                vida=false;
                break;
            }
            else{
                suelo=false;
            }

        }
    }

    //friccion
    if(vx>0 && suelo) ax=-0.9*5;
    else if(vx<0 && suelo) ax=0.9*5;

    // limites de velocidad en x
    if(vx<-24) vx=-24;
    else if(vx>24) vx=24;


    if(Salto){   
         vy = 35, Salto=false;
    }
    vx= vx +tiempoS*ax;
    vy= vy +(ay-gravedad)*tiempoS;
    py = py-vy*tiempoS;  //simulacion de pos en y
    px = px+vx*tiempoS; //simulacion de pos en x
    setPos(px,py); //cambio en la pos del personaje
    setImage();
    ax=0;

}

void Personaje::setImage()
{
    if(suelo){
        if(vx==0) setPixmap(Default.copy(0,0,14,12).scaled(30,30));
        else if(vx>0) setPixmap(Default.copy(14,0,14,12).scaled(30,30));
        else if(vx<0){
            setPixmap(Default.copy(14,0,14,12).transformed(QTransform().inverted()).scaled(30,30));
        }
    }
    else if(vy!=0) setPixmap(Default.copy(70,0,14,12).scaled(30,30));

}
bool Personaje::ComprobarCollision(QRect rect1,QRect rect2){
    if ( rect1.x() > rect2.x()+rect2.width())  return false;
    if ( rect1.x()+rect1.width() < rect2.x())  return false;
    if ( rect1.y() > rect2.y()+rect2.height()) return false;
    if ( rect1.y()+rect1.height() < rect2.y()) return false;
    else return true;
}

